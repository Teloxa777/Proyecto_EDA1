#ifndef MODULO_SALA_H
#define MODULO_SALA_H

#include "modulo_ticket.h"

#define MAX_SALAS 2
#define MAX_ASIENTOS 4

typedef struct {
  int id;
  Ticket* asientos[MAX_ASIENTOS][MAX_ASIENTOS];
} Sala;

Sala* crear_sala(int id);

#endif //MODULO_SALA_H
