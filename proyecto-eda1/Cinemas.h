#ifndef CINEMAS_H
#define CINEMAS_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "Ticket.h"

typedef struct Cinema
{
    Ticket info;
    struct Cinema* next;
    struct Cinema* prev;
} Cinema;

typedef struct 
{
    Cinema* first;
    Cinema* cursor;
    Cinema* last;
    size_t len;
} Cinemas;


Cinemas* Cinemas_New();
void Cinemas_Delete( Cinemas** this );

//Cinema Cinemas_Front( Cinemas* this ); Devuelve una copia de la sala en first
//Cinema Cinemas_Back( Cinemas* this ); Devuelve una copia de la sala en last

void Cinemas_Push_front( Cinemas* this, Ticket item );
void Cinemas_Push_back( Cinemas* this, Ticket item );
void Cinemas_Insert( Cinemas* this, Ticket item );

void Cinemas_Pop_front( Cinemas* this );
void Cinemas_Pop_back( Cinemas* this );

//void Cinemas_Erase( Cinemas* this ); Elimina Una Sala de la lista en la posicion de cursor
//void Cinemas_Remove( Cinemas* this, Ticket key ); Elimina la primer Sala que coincida con la llave

void Cinemas_MakeEmpty( Cinemas* this );

//bool Cinemas_Find( Cinemas* this, Ticket key ); Busca una sala de acuerdo a la informacion del Ticket
//Puede hacerse una funcion de Find por cada dato del Ticket y/o combinaciones de los mismos.

Ticket Cinemas_Cursor_Get( Cinemas* this );
void Cinemas_Cursor_front( Cinemas* this );
void Cinemas_Cursor_back( Cinemas* this );
void Cinemas_Cursor_next( Cinemas* this );
void Cinemas_Cursor_prev( Cinemas* this );
bool Cinemas_Cursor_end( Cinemas* this );

bool Cinemas_IsEmpty( Cinemas* this );
size_t Cinemas_Len( Cinemas* this );

#endif //CINEMAS_H
