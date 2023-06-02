#ifndef MODULO_COLA_H
#define MODULO_COLA_H

#include <stdbool.h>
#include "modulo_ticket.h"

typedef struct {
    Ticket* queue;
    size_t front;
    size_t back;
    size_t len;
    size_t capacity;
} Cola;

Cola* Queue_New(size_t capacity);
void Queue_Delete(Cola** c);
void Queue_Enqueue(Cola* c, Ticket t);
Ticket* Queue_Dequeue(Cola* c);
size_t Queue_Len(Cola* c);
bool Queue_IsEmpty(Cola* c);
bool Queue_IsFull(Cola* c);

#endif //MODULO_COLA_H
