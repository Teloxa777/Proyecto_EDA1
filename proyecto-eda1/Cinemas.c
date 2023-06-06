#include "Cinemas.h"
/**
 * @brief Crea una nueva Sala.
 *
 * @param x Información del ticket de la sala.
 * @return Un puntero a la nueva Sala.
 */
static Cinema* Cinema_New( Ticket x ) //Crea una nueva Sala
{
    Cinema* c = (Cinema*) malloc( sizeof( Cinema ) );
    if( c != NULL )
    {
        c->info = x;
        c->next = NULL;
        c->prev = NULL;
    }

   return c;
}
/**
 * @brief Crea una lista de Salas.
 *
 * @return Un puntero a la nueva lista de Salas.
 */
Cinemas* Cinemas_New() //Crea una lista de Salas
{
    Cinemas* list = (Cinemas*) malloc( sizeof( Cinemas ) );
    if( list )
    {
        list->first = list->last = list->cursor = NULL;
        list->len = 0;
    }
    
    return list;
}
/**
 * @brief Borra una lista de Salas.
 *
 * @param this Un puntero al puntero de la lista de Salas.
 */
void Cinemas_Delete( Cinemas** this ) // Borra una lista de Salas
{
    assert( *this );
    while( Cinemas_Len( *this ) > 0)
    {
        Cinemas_Pop_back( *this );
    }
    free( *this );
    *this = NULL;
}
/**
 * @brief Agrega una Sala a la lista de Salas al inicio.
 *
 * @param this Un puntero a la lista de Salas.
 * @param info Información del ticket de la sala.
 */
void Cinemas_Push_front( Cinemas* this, Ticket info ) //Se agrega una Sala a la lista de Salas por enfrente
{
    assert( this );
    
    Cinema* c = Cinema_New( info );
    assert( c );
    if( Cinemas_IsEmpty( this ) )
    {
        this->first = this->cursor = this->last = c;
        c->next = c->prev = c;
    }
    else
    {
        c->next = this->first;
        this->first->prev = c;
        c->prev = this->last;
        this->last->next = c;
        this->first = c;
    }
    ++this->len;
}
/**
 * @brief Agrega una Sala a la lista de Salas al final.
 *
 * @param this Un puntero a la lista de Salas.
 * @param info Información del ticket de la sala.
 */
void Cinemas_Push_back( Cinemas* this, Ticket info ) //Se agrega una Sala a la lista de Salas por detras
{
    assert ( this );
    Cinema* c = Cinema_New( info );
    assert( c );
    
    if( this->first != NULL )
    {
        this->last->next = c;
        c->prev = this->last;
        this->first->prev = c;
        c->next = this->first;
        this->last = c;
    }
    else
    {
        this->first = this->last = this->cursor = c;
        c->next = c->prev = c;
    }
    ++this->len;
}
/**
 * @brief Agrega una Sala a la lista de Salas en la posición del cursor.
 *
 * @param this Un puntero a la lista de Salas.
 * @param info Información del ticket de la sala.
 */
void Cinemas_Insert( Cinemas* this, Ticket info ) //Se agrega una Sala a la lista de Salas en cursor
{
    assert( this );
    
    if( this->cursor == this->last )
    {
        Cinemas_Push_back( this, info );
    }
    else
    {
        Cinema* c = Cinema_New( info );
        assert( c );
        
        Cinema* right = this->cursor->next;
        this->cursor->next = c;
        c->next = right;
        right->prev = c;
        c->prev = this->cursor;
        this->cursor = c;
        
        ++this->len;
    }
}
/**
 * @brief Elimina la Sala al inicio de la lista.
 *
 * @param this Un puntero a la lista de Salas.
 */
void Cinemas_Pop_front( Cinemas* this ) //Se elimina una Sala de la lista por enfrente
{
    assert( this );
    assert( this->len > 0 );
    
    if( this->first != this->last ) //Evalua que haya mas de 1 Sala
    {
        Cinema* tmp = this->first->next;
        free( this->first );
        tmp->prev = this->last;
        this->last->next = tmp;
        this->first = tmp;
        --this->len;
    }
    else
    {
        free( this->first );
        this->first = this->last = this->cursor = NULL;
        this->len = 0;
    }
}
/**
 * @brief Elimina la Sala al final de la lista.
 *
 * @param this Un puntero a la lista de Salas.
 */
void Cinemas_Pop_back( Cinemas* this ) //Se elimina una Sala de la lista por detras
{
    assert( this );
    assert( this->len > 0 );
    
    if( this->len > 1 )
    {
        Cinema* x = this->last->prev;
        free( this->last );
        x->next = this->first;
        this->first->prev = x;
        this->last = x;
        --this->len;
    }
    else
    {
        free( this->last );
        this->first = this->last = this->cursor = NULL;
        this->len = 0;
    }
}
/**
 * @brief Vacia la lista de Salas.
 *
 * @param this Un puntero a la lista de Salas.
 */
void Cinemas_MakeEmpty( Cinemas* this ) //Vacia la lista de Salas
{
    assert( this );
    assert( this->len > 0 );
    
    while( this->first )
    {
        Cinema* tmp = this->first->next;
        if( tmp == this->last)
        {
            this->last->next = NULL;
        }
        free( this->first );
        this->first = tmp;
    }
    this->first = this->last = this->cursor = NULL;
    this->len = 0;
}
/**
 * @brief Devuelve una copia del ticket de la Sala apuntada por el cursor.
 *
 * @param this Un puntero a la lista de Salas.
 * @return El ticket de la Sala apuntada por el cursor.
 */
Ticket Cinemas_Cursor_Get( Cinemas* this ) //Devuelve copia del ticket de la Sala apuntada por cursor
{
    assert( this );
    assert( this->first );
    assert( this->cursor );
    
    return this->cursor->info;
}
/**
 * @brief Coloca el cursor al inicio de la lista de Salas.
 *
 * @param this Un puntero a la lista de Salas.
 */
void Cinemas_Cursor_front( Cinemas* this ) //Coloca el cursor al inicio de la lista de Salas
{
    assert( this );
    assert( this->first );
    assert( this->cursor );
    
    this->cursor = this->first;
}
/**
 * @brief Coloca el cursor al final de la lista de Salas.
 *
 * @param this Un puntero a la lista de Salas.
 */
void Cinemas_Cursor_back( Cinemas* this ) //Coloca el cursor al final de la lista de Salas
{
    assert( this );
    assert( this->first );
    assert( this->cursor );
    
    this->cursor = this->last;
}
/**
 * @brief Mueve el cursor una Sala a la derecha.
 *
 * @param this Un puntero a la lista de Salas.
 */
void Cinemas_Cursor_next( Cinemas* this ) //Mueve el cursor una Sala a la derecha
{
    assert( this );
    assert( this->first );
    assert( this->cursor );
    
    Cinema* right = this->cursor->next;
    this->cursor = right;
}
/**
 * @brief Mueve el cursor una Sala a la izquierda.
 *
 * @param this Un puntero a la lista de Salas.
 */
void Cinemas_Cursor_prev( Cinemas* this ) //Mueve el cursor una Sala a la izquierda
{
    assert( this->cursor != NULL );
    
    Cinema* left = this->cursor->prev;
    this->cursor = left;
}
/**
 * @brief Comprueba si el cursor ha llegado al final de la lista de Salas.
 *
 * @param this Un puntero a la lista de Salas.
 * @return Verdadero si el cursor está al final de la lista, falso en caso contrario.
 */
bool Cinemas_Cursor_end( Cinemas* this ) //Funcion que se usa en ciclos for que involucren a cursor, todavia no se prueba, puede estar mal
{
    assert( this );
    assert( this->cursor );

    bool isEnd = false;  // Bool para indicar si el cursor ha llegado al final de la lista

    for ( Cinema* current = this->first; current != NULL; current = current->next ) //Duda aqui, no se si este for se deba aplicar en la main o en esta funcion
    {
        if ( current == this->last )
        {
            isEnd = true;  // current apunta al último nodo de la lista
        }
        // Realiza las operaciones necesarias en cada iteración ( incluso si es el ultimo elemento )
        if ( isEnd )
        {
            break;  // Termina el ciclo después de evaluar el último elemento
        }
    }

    return isEnd;
}
/**
 * @brief Comprueba si la lista de Salas está vacía.
 *
 * @param this Un puntero a la lista de Salas.
 * @return Verdadero si la lista está vacía, falso en caso contrario.
 */
bool Cinemas_IsEmpty( Cinemas* this )
{
    assert( this );
    return this->first == NULL;
}
/**
 * @brief Obtiene la longitud de la lista de Salas.
 *
 * @param this Un puntero a la lista de Salas.
 * @return La longitud de la lista.
 */
size_t Cinemas_Len( Cinemas* this )
{
    assert( this );
    return this->len;
}

