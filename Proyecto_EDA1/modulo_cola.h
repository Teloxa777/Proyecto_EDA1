#ifndef MODULO_COLA_H
#define MODULO_COLA_H

#include "modulo_ticket.h"

typedef struct Nodo {
    Ticket ticket;
    struct Nodo* next;
} Nodo;

typedef struct {
    Nodo* front;
    Nodo* rear;
} Cola;

Cola* crear_cola();
void encolar(Cola* c, Ticket t);
Ticket* desencolar(Cola* c);

#endif //MODULO_COLA_H
