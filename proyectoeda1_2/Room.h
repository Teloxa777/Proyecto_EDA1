#ifndef ROOM_H
#define ROOM_H

#include "Ticket.h"
#include "Seat.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#define COL_SIZE 10
#define FILM_SIZE 50

typedef struct 
{
    Row* first_row;  // Puntero a la primera fila de la sala.
    Ticket* first_ticket;  // Puntero al primer ticket en la sala.
    char film[FILM_SIZE]; // Nombre de la película que se muestra en la sala.
} Room;

Room* Room_New();

// Declaraciones de funciones existentes
Ticket* Room_GetTicket(Room* room);
void Room_SetTicket(Room* room, Ticket* ticket);
char* Room_GetFilm(Room* room);
void Room_SetFilm(Room* room, const char* film);
void Room_PrintTicket(const Room* room);

void Room_AddTicket(Room* room, const char* film, int room_number, int row, int column, float price);

#endif /* ROOM_H */