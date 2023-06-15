#ifndef SEAT_H
#define SEAT_H
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

typedef struct Seat
{
    int row; // Fila en la que se encuentra el asiento (dada por el indice del arreglo dinamico)
    int column; // Columna en la que se encuentra el asiento
    bool occupied; // Bool para verificar si esta ocupado el asiento
    struct Seat* next;
    struct Seat* prev;
} Seat;

typedef struct 
{
    Seat* first;
    Seat* last;
    Seat* cursor;
    size_t len;
} Column;

typedef struct 
{
    Column** row;   // Array dinámico cuyas celdas son las distintas filas (contienen listas Column)
    int size; // Tamaño del arreglo
} Row;

Seat* Seat_New();
void Seat_Fill(Row* this, size_t index, int seats); // Recibe la estructura Row, la fila a rellenar y el numero e asientos de la fila

void Seat_Start(Row* this); // Recibe la estructura row y coloca cursor de cada lista al inicio

void Seat_Find(Column* this, int key);

void Seat_SetPosition(Row* this, int index, int column); // 
int Seat_GetColumnPosition(Seat* this); // Recibe un apuntador a asiento y devuelve su posicion columna
int Seat_GetRowPosition(Seat* this); // Recibe una estructura Row, devuelve el indice del arreglo en el que este el asiento elegido

void Seat_Select(Seat* this); // Recibe la lista columna y marca el asiento apuntado por el cursor como ocupado
bool Seat_Occupied(Seat* this); // Recibe apuntador a seat y verifica si esta ocupado

Row* Row_New(int size);
void Row_Delete(Row** this);

void Row_AddColumn(Row* this, size_t index); // Crea y añade una columna a una celda del arreglo
void Row_Fill(); // Rellena todas las celdas del arreglo con listas Column

Column* Column_New();
void Column_Delete(Column** this);

void Column_Push_front(Column* this); // Añade un asiento a la lista por delante
void Column_Push_back(Column* this); // Añade un asiento a la lista por detras

void Column_Pop_front(Column* this);
void Column_Pop_back(Column* this);

void Column_MakeEmpty(Column* this);

bool Column_Cursor_Get(const Column* this); // Regresa el estado del asiento apuntado por cursor
void Column_Cursor_front(Column* this);
void Column_Cursor_back(Column* this);
void Column_Cursor_next(Column* this);
void Column_Cursor_prev(Column* this);
bool Column_Cursor_end(Column* this);

bool Column_IsEmpty(const Column* this);
size_t Column_Len(const Column* this);

Seat* Column_Cursor_GetSeat(const Column* this);

void Seat_Print(Row* this);

#endif /* SEAT_H */
