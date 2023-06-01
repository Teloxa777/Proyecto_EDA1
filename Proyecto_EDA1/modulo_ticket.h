#ifndef MODULO_TICKET_H
#define MODULO_TICKET_H

typedef struct {
  char nombre_pelicula[50];
  char hora_proyeccion[5];
  int numero_sala, a1, a2;
  float precio_entrada;
} Ticket;

void imprimir_ticket(Ticket* t);

#endif //MODULO_TICKET_H
