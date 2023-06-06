#ifndef TICKET_H
#define TICKET_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#define MAX_FILM 50
#define MAX_PROJECTION 6
#define MAX_ROWS 5
#define MAX_COLUMNS 10

typedef struct Seats
{
    size_t row; // posicion: fila
    size_t column; // posicion: columna
    bool avaible; //True= disponible; False = ocupado
    struct Seats* next;
    struct Seats* prev;
} Seats;

typedef struct 
{
    char film[MAX_FILM]; // Nombre de la pelicula
    char projection[MAX_PROJECTION]; // Hora de proyeccion
    unsigned int cinema_id; // Numero de sala
    Seats* position [MAX_ROWS][MAX_COLUMNS]; // Matriz de asientos para la posicion, usar punteros si se generaran los asientos a lo largo del programa
    Seats* cursor; // Cursor para recorrer la matriz
    float price; // Precio
} Ticket;


Ticket Ticket_New();
void Ticket_Delete_Seats( Ticket* t );

void Ticket_Cursor_front( Ticket* this );
void Ticket_Cursor_next( Ticket* this );
void Ticket_Cursor_prev( Ticket* this );

bool Ticket_Get_Seats( const Ticket* this );
void Ticket_Take_Seats( Ticket* this );
void Ticket_Leave_Seats( Ticket* this );

void Ticket_Values( Ticket* ticket, const char* film, const char* projection, unsigned int cinema_id, float price );

void Ticket_Print( Ticket t );

#endif //TICKET_H
