#include "Cinemas.h"

/**
 * @brief Crea un nuevo objeto Cinema.
 * 
 * @param room La sala asociada a este cine.
 * @return Cinema* El cine recién creado.
 */
static Cinema* Cinema_New(Room* room)
{
    Cinema* c = (Cinema*)malloc(sizeof(Cinema));
    if (c != NULL)
    {
        c->room = room;
        c->next = NULL;
        c->prev = NULL;
    }
    return c;
}
/**
 * @brief Crea un nuevo objeto Cinemas.
 * 
 * @return Cinemas* El objeto Cinemas recién creado.
 */
Cinemas* Cinemas_New()
{
    Cinemas* list = (Cinemas*)malloc(sizeof(Cinemas));
    if (list)
    {
        list->first = list->last = list->cursor = NULL;
        list->len = 0;
    }

    return list;
}
/**
 * @brief Elimina un objeto Cinemas.
 * 
 * @param this Un doble puntero al objeto Cinemas que se va a eliminar.
 */
void Cinemas_Delete(Cinemas** this)
{
    assert(this && *this);
    
    Cinemas_MakeEmpty(*this);
    
    free(*this);
    *this = NULL;
}
/**
 * @brief Inserta una nueva sala al inicio de la lista de cines.
 * 
 * @param this Un puntero al objeto Cinemas.
 * @param room La sala que se va a insertar.
 */
void Cinemas_Push_front(Cinemas* this, Room* room)
{
    assert(this);

    Cinema* c = Cinema_New(room);
    assert(c);
    if (Cinemas_IsEmpty(this))
    {
        this->first = this->cursor = this->last = c;
    }
    else
    {
        c->next = this->first;
        this->first->prev = c;
        this->first = c;
    }
    ++this->len;
}
/**
 * @brief Inserta una nueva sala al final de la lista de cines.
 * 
 * @param this Un puntero al objeto Cinemas.
 * @param room La sala que se va a insertar.
 */
void Cinemas_Push_back(Cinemas* this, Room* room)
{
    assert(this);

    Cinema* c = Cinema_New(room);
    assert(c);
    if (Cinemas_IsEmpty(this))
    {
        this->first = this->cursor = this->last = c;
    }
    else
    {
        this->last->next = c;
        c->prev = this->last;
        this->last = c;
    }
    ++this->len;
}
/**
 * @brief Inserta una sala en la posición del cursor dentro de la lista de cines.
 * 
 * @param this Un puntero al objeto Cinemas.
 * @param room La sala que se va a insertar.
 */
void Cinemas_Insert(Cinemas* this, Room* room)
{
    assert(this);

    if (Cinemas_IsEmpty(this) || this->cursor == this->first)
    {
        Cinemas_Push_front(this, room);
    }
    else if (this->cursor == this->last)
    {
        Cinemas_Push_back(this, room);
    }
    else
    {
        Cinema* c = Cinema_New(room);
        assert(c);
        
        c->next = this->cursor->next;
        this->cursor->next->prev = c;
        c->prev = this->cursor;
        this->cursor->next = c;
        this->cursor = c;
        if (this->cursor == this->last)
        {
            this->last = c;
        }
        ++this->len;
    }
}
/**
 * @brief Elimina la primera sala de la lista de cines.
 * 
 * @param this Un puntero al objeto Cinemas.
 */
void Cinemas_Pop_front(Cinemas* this)
{
    assert(this && this->len > 0);

    Cinema* tmp = this->first;
    this->first = this->first->next;

    if (this->cursor == tmp)
    {
        this->cursor = this->first;
    }

    if (this->last == tmp)
    {
        this->last = this->first;
    }

    free(tmp);
    --this->len;
}
/**
 * @brief Elimina la última sala de la lista de cines.
 * 
 * @param this Un puntero al objeto Cinemas.
 */
void Cinemas_Pop_back(Cinemas* this)
{
    assert(this && this->len > 0);

    if (this->last == this->first)
    {
        free(this->first);
        this->first = this->last = this->cursor = NULL;
    }
    else
    {
        Cinema* tmp = this->last->prev;
        
        if (this->cursor == this->last)
        {
            this->cursor = tmp;
        }
        
        free(this->last);
        this->last = tmp;
        this->last->next = NULL;
    }

    --this->len;
}
/**
 * @brief Vacía la lista de cines.
 * 
 * @param this Un puntero al objeto Cinemas.
 */
void Cinemas_MakeEmpty(Cinemas* this)
{
    assert(this);
    assert(this->len > 0);

    while(!Cinemas_IsEmpty(this))
    {
        Cinemas_Pop_front(this);
    }
}
/**
 * @brief Obtiene la sala asociada al objeto en la posición del cursor.
 * 
 * @param this Un puntero constante al objeto Cinemas.
 * @return Room* La sala asociada al objeto en la posición del cursor.
 */
Room* Cinemas_Cursor_Get(const Cinemas* this)
{
    assert(this && this->cursor);

    return this->cursor->room;
}
/**
 * @brief Posiciona el cursor al inicio de la lista de cines.
 * 
 * @param this Un puntero al objeto Cinemas.
 */
void Cinemas_Cursor_front(Cinemas* this)
{
    assert(this);
    assert(this->len > 0);

    this->cursor = this->first;
}
/**
 * @brief Posiciona el cursor al final de la lista de cines.
 * 
 * @param this Un puntero al objeto Cinemas.
 */
void Cinemas_Cursor_back(Cinemas* this)
{
    assert(this);
    assert(this->len > 0);

    this->cursor = this->last;
}
/**
 * @brief Mueve el cursor a la siguiente sala en la lista de cines.
 * 
 * @param this Un puntero al objeto Cinemas.
 */
void Cinemas_Cursor_next(Cinemas* this)
{
    assert(this);
    assert(this->cursor);

    this->cursor = this->cursor->next;
}
/**
 * @brief Mueve el cursor a la sala anterior en la lista de cines.
 * 
 * @param this Un puntero al objeto Cinemas.
 */
void Cinemas_Cursor_prev(Cinemas* this)
{
    assert(this);
    assert(this->cursor);

    this->cursor = this->cursor->prev;
}
/**
 * @brief Verifica si el cursor ha alcanzado el final de la lista de cines.
 * 
 * @param this Un puntero al objeto Cinemas.
 * @return bool Devuelve true si el cursor ha alcanzado el final de la lista, de lo contrario, devuelve false.
 */
bool Cinemas_Cursor_end(Cinemas* this)
{
    assert(this);

    return this->cursor == NULL;
}
/**
 * @brief Verifica si la lista de cines está vacía.
 * 
 * @param this Un puntero constante al objeto Cinemas.
 * @return bool Devuelve true si la lista de cines está vacía, de lo contrario, devuelve false.
 */
bool Cinemas_IsEmpty(const Cinemas* this)
{
    assert(this);

    return this->len == 0;
}
/**
 * @brief Obtiene la longitud de la lista de cines.
 * 
 * @param this Un puntero constante al objeto Cinemas.
 * @return size_t La longitud de la lista de cines.
 */
size_t Cinemas_Len(const Cinemas* this)
{
    assert(this);

    return this->len;
}
/**
 * @brief Imprime los tickets de las salas de cine.
 * 
 * @param this Un puntero constante al objeto Cinemas.
 */
void Cinemas_PrintTickets(const Cinemas* this) 
{
    Cinema* current = this->first;
    while (current != NULL) 
    {
        Room_PrintTicket(current->room);
        current = current->next;
    }
}