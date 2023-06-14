#ifndef CINEMAS_H
#define CINEMAS_H

#include "Room.h"
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <stddef.h> 
//hoola perros
typedef struct Cinema 
{
    Room* room;
    struct Cinema* next;
    struct Cinema* prev;
} Cinema;

typedef struct Cinemas 
{
    Cinema* first;
    Cinema* last;
    Cinema* cursor;
    size_t len;
} Cinemas;

Cinemas* Cinemas_New();
void Cinemas_Delete(Cinemas** this);

void Cinemas_Push_front(Cinemas* this, Room* room);
void Cinemas_Push_back(Cinemas* this, Room* room);
void Cinemas_Insert(Cinemas* this, Room* room);

void Cinemas_Pop_front(Cinemas* this);
void Cinemas_Pop_back(Cinemas* this);

void Cinemas_MakeEmpty(Cinemas* this);

Room* Cinemas_Cursor_Get(const Cinemas* this);
void Cinemas_Cursor_front(Cinemas* this);
void Cinemas_Cursor_back(Cinemas* this);
void Cinemas_Cursor_next(Cinemas* this);
void Cinemas_Cursor_prev(Cinemas* this);
bool Cinemas_Cursor_end(Cinemas* this);

bool Cinemas_IsEmpty(const Cinemas* this);
size_t Cinemas_Len(const Cinemas* this);

void Cinemas_PrintTickets(const Cinemas* this);

#endif // CINEMAS_H