#include "Seat.h"
#include <stdlib.h>
/**
 * @brief Crea un nuevo objeto Seat.
 * 
 * @return Seat* El objeto Seat recién creado.
 */
Seat* Seat_New()
{
    Seat* s = (Seat*)malloc(sizeof(Seat));
    if (s != NULL)
    {
        s->row = 0;
        s->column = 0;
        s->occupied = false;
        s->next = NULL;
        s->prev = NULL;
    }
    return s;
}
/**
 * @brief Llena una fila con un número determinado de asientos.
 * 
 * @param this Un puntero a la estructura Row.
 * @param index El índice de la fila.
 * @param seats El número de asientos a llenar.
 */
void Seat_Fill(Row* this, size_t index, int seats)
{
    assert(this);
    assert(index >= 0 && index < this->size);
    
    for(int i = 0; i < seats; ++i)
    {
        Column_Push_back(this->row[index]);
        Column_Cursor_back(this->row[index]);
        this->row[index]->cursor->row = index + 1;
        this->row[index]->cursor->column = i + 1;
    }
}
/**
 * @brief Posiciona el cursor de todas las filas al primer asiento.
 * 
 * @param this Un puntero a la estructura Row.
 */
void Seat_Start(Row* this)
{
    assert(this);
    
    for(size_t i = 0; i < this->size; ++i)
    {
        Column_Cursor_front(this->row[i]);
    }
}
/**
 * @brief Busca un asiento por su número de columna.
 * 
 * @param this Un puntero a la estructura Column.
 * @param key El número de columna a buscar.
 */
void Seat_Find(Column* this, int key)
{
    assert(this);

    for (Column_Cursor_front(this); !Column_Cursor_end(this); Column_Cursor_next(this))
    {
        if (this->cursor->column == key)
        {
            if (Seat_Occupied(this->cursor))
            {
                printf("Este asiento está ocupado\n");
            }
            else
            {
                printf("Este asiento está disponible\n");
            }
            return;
        }
    }

    printf("No se encontró el asiento con el número de columna %d\n", key);
}


/**
 * @brief Establece la posición del asiento seleccionado en una fila específica.
 * 
 * @param this Un puntero a la estructura Row.
 * @param index El índice de la fila.
 * @param column El número de columna del asiento a seleccionar.
 */
void Seat_SetPosition(Row* this, int index, int column)
{
    assert(this);
    assert(index >= 0 && index < this->size);

    Column* columnList = this->row[index];
    Seat_Find(columnList, column);
    if (columnList->cursor != NULL)
    {
        if (Seat_Occupied(columnList->cursor))
        {
            printf("Lo siento, el asiento ya está ocupado.\n");
        }
        else
        {
            Seat_Select(columnList->cursor->next);  // Corrección aquí
            printf("Asiento seleccionado: Fila %d, Columna %d\n", index + 1, column);
            printf("Estado de ocupación: %s\n", Seat_Occupied(columnList->cursor->next) ? "Ocupado" : "Disponible");  // Corrección aquí
        }
    }
    else
    {
        printf("No se encontró el asiento con el número de columna %d en la fila %d\n", column, index + 1);
    }
}




/**
 * @brief Obtiene la posición de columna del asiento.
 * 
 * @param this Un puntero al objeto Seat.
 * @return int La posición de columna del asiento.
 */
int Seat_GetColumnPosition(Seat* this) // Recibe un apuntador a asiento y devuelve su posicion columna
{
    assert(this);
    return this->column;
}
/**
 * @brief Obtiene la posición de fila del asiento.
 * 
 * @param this Un puntero al objeto Seat.
 * @return int La posición de fila del asiento.
 */
int Seat_GetRowPosition(Seat* this) // Recibe un apuntador a asiento y devuelve su posicion de fila
{
    assert(this);
    return this->row;
}

/**
 * @brief Marca el asiento apuntado por el cursor como ocupado.
 * 
 * @param this Un puntero a la estructura Column.
 */
void Seat_Select(Seat* this)
{
    assert(this);
    this->occupied = true;
}

/**
 * @brief Verifica si un asiento está ocupado.
 * 
 * @param this Un puntero al objeto Seat.
 * @return bool true si el asiento está ocupado, false en caso contrario.
 */
bool Seat_Occupied(Seat* this)
{
    assert(this);
    
    return this->occupied == true;
}
/**
 * @brief Crea una nueva estructura Row.
 * 
 * @param size El tamaño del arreglo de filas.
 * @return Row* La estructura Row recién creada.
 */
Row* Row_New(int size) // Crea una nueva estructura Row y recibe el tamaño de su arreglo
{
    Row* r = (Row*) malloc(sizeof(Row));
    assert( r );
    
    r->size = size; // Almacenar el número del arreglo
    r->row = (Column**)malloc(size * sizeof(Column));
    assert(r->row);
    
    Row_Fill(r);
    
    return r;
}
/**
 * @brief Elimina una estructura Row.
 * 
 * @param this Un doble puntero a la estructura Row que se va a eliminar.
 */
void Row_Delete(Row** this) // Elimina una estructura Row
{
    assert(this && *this);
    
    for (int i = 0; i < (*this)->size; i++) 
    {
        Column_Delete(&((*this)->row[i])); // Elimina los asientos y las listas de todas las celdas
    }
    
    // Finalmente, liberamos el arreglo de Columnas y la estructura Row
    free((*this)->row); 
    free(*this);
    *this = NULL;
}
/**
 * @brief Agrega una columna a la estructura Row en un índice dado.
 * 
 * @param this Un puntero a la estructura Row.
 * @param index El índice de la fila.
 */
void Row_AddColumn(Row* this, size_t index)
{
    assert(this);
    assert(index >= 0 && index < this->size);
    
    Column* list =  Column_New();
    assert(list);
    
    this->row[index] = list;
}
/**
 * @brief Rellena todas las celdas de la estructura Row con listas de Column.
 * 
 * @param this Un puntero a la estructura Row.
 */
void Row_Fill(Row* this) // Rellena todas las celdas del arreglo con listas Column
{
    assert(this);
    
    for(size_t i = 0; i < this->size; ++i)
    {
        Row_AddColumn( this, i);
    }
}
/**
 * @brief Crea una nueva estructura Column.
 * 
 * @return Column* La estructura Column recién creada.
 */
Column* Column_New()
{
    Column* list = (Column*)malloc(sizeof(Column));
    if (list)
    {
        list->first = list->last = list->cursor = NULL;
        list->len = 0;
    }

    return list;
}
/**
 * @brief Elimina una estructura Column.
 * 
 * @param this Un doble puntero a la estructura Column que se va a eliminar.
 */
void Column_Delete(Column** this)
{
    assert(this && *this);
    
    Column_MakeEmpty(*this);
    
    free(*this);
    *this = NULL;
}
/**
 * @brief Inserta un nuevo asiento al inicio de la lista Column.
 * 
 * @param this Un puntero a la estructura Column.
 */
void Column_Push_front(Column* this)
{
    assert(this);

    Seat* s = Seat_New();
    assert(s);
    if (Column_IsEmpty(this))
    {
        this->first = this->cursor = this->last = s;
    }
    else
    {
        s->next = this->first;
        this->first->prev = s;
        this->first = s;
    }
    ++this->len;
}
/**
 * @brief Inserta un nuevo asiento al final de la lista Column.
 * 
 * @param this Un puntero a la estructura Column.
 */
void Column_Push_back(Column* this)
{
    assert(this);

    Seat* s = Seat_New();
    assert(s);
    if (Column_IsEmpty(this))
    {
        this->first = this->cursor = this->last = s;
    }
    else
    {
        this->last->next = s;
        s->prev = this->last;
        this->last = s;
    }
    ++this->len;
}
/**
 * @brief Elimina el asiento al inicio de la lista Column.
 * 
 * @param this Un puntero a la estructura Column.
 */
void Column_Pop_front(Column* this)
{
    assert(this && this->len > 0);

    Seat* tmp = this->first;
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
 * @brief Elimina el asiento al final de la lista Column.
 * 
 * @param this Un puntero a la estructura Column.
 */
void Column_Pop_back(Column* this)
{
    assert(this && this->len > 0);

    if (this->last == this->first)
    {
        free(this->first);
        this->first = this->last = this->cursor = NULL;
    }
    else
    {
        Seat* tmp = this->last->prev;
        
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
 * @brief Vacia la lista Column.
 * 
 * @param this Un puntero a la estructura Column.
 */
void Column_MakeEmpty(Column* this)
{
    assert(this);
    assert(this->len > 0);

    while(!Column_IsEmpty(this))
    {
        Column_Pop_front(this);
    }
}
/**
 * @brief Obtiene el estado del asiento apuntado por el cursor.
 * 
 * @param this Un puntero constante a la estructura Column.
 * @return bool true si el asiento está ocupado, false en caso contrario.
 */
bool Column_Cursor_Get(const Column* this) // Devuelve el estado del asiento, si esta disponible o no
{
    assert(this && this->cursor);

    return this->cursor->occupied;
}
/**
 * @brief Posiciona el cursor al inicio de la lista Column.
 * 
 * @param this Un puntero a la estructura Column.
 */
void Column_Cursor_front(Column* this) // Posiciona el cursor al inicio de la lista
{
    assert(this);
    assert(this->len > 0);

    this->cursor = this->first;
}
/**
 * @brief Posiciona el cursor al final de la lista Column.
 * 
 * @param this Un puntero a la estructura Column.
 */
void Column_Cursor_back(Column* this)
{
    assert(this);
    assert(this->len > 0);
    
    this->cursor = this->last;
}
/**
 * @brief Mueve el cursor al siguiente asiento de la lista Column.
 * 
 * @param this Un puntero a la estructura Column.
 */
void Column_Cursor_next(Column* this) // Mueve el cursor al siguiente asiento
{
    assert(this);
    assert(this->cursor);

    this->cursor = this->cursor->next;
}
/**
 * @brief Mueve el cursor al asiento anterior de la lista Column.
 * 
 * @param this Un puntero a la estructura Column.
 */
void Column_Cursor_prev(Column* this) // Mueve el cursor al anterior asiento
{
    assert(this);
    assert(this->cursor);

    this->cursor = this->cursor->prev;
}
/**
 * @brief Verifica si el cursor ha llegado al final de la lista Column.
 * 
 * @param this Un puntero a la estructura Column.
 * @return bool true si el cursor ha llegado al final, false en caso contrario.
 */
bool Column_Cursor_end(Column* this) // Se usa en ciclos, es el indicador del final
{
    assert(this);

    return this->cursor == NULL;
}
/**
 * @brief Verifica si la lista Column está vacía.
 * 
 * @param this Un puntero constante a la estructura Column.
 * @return bool true si la lista está vacía, false en caso contrario.
 */
bool Column_IsEmpty(const Column* this) // Evalua si la lista esta vacia
{
    assert(this);

    return this->len == 0;
}
/**
 * @brief Obtiene la longitud de la lista Column.
 * 
 * @param this Un puntero constante a la estructura Column.
 * @return size_t La longitud de la lista Column.
 */
size_t Column_Len(const Column* this) // Devuelve la longitud de la lista
{
    assert(this);

    return this->len;
}
/**
 * @brief Obtiene el asiento actual apuntado por el cursor.
 * 
 * @param this Un puntero constante a la estructura Column.
 * @return Seat* El asiento actual apuntado por el cursor.
 */
Seat* Column_Cursor_GetSeat(const Column* this) // Devuelve el asiento actual en el cursor
{
    assert(this && this->cursor);
    return this->cursor;
}
/**
 * @brief Imprime la disposición de los asientos en la estructura Row.
 * 
 * @param this Un puntero a la estructura Row.
 */
void Seat_Print(Row* this)
{
    assert(this);

    Seat_Start(this);

    for (size_t i = 0; i < this->size; ++i)
    {
        printf("%zu: ", i + 1);
        for (Column_Cursor_front(this->row[i]); !Column_Cursor_end(this->row[i]); Column_Cursor_next(this->row[i]))
        {
            printf("[%zu, %d]: ", i + 1, this->row[i]->cursor->column);
            if (Seat_Occupied(this->row[i]->cursor))
            {
                printf("[X]  ");
            }
            else
            {
                printf("[ ]  ");
            }
        }
        printf("\n\n");
    }
    Seat_Start(this);
}
