#include <stdio.h>
#include<stdlib.h>
#include "modulo_ticket.h"
#include "modulo_sala.h"
#include "modulo_cola.h"

int main() {
  // Crear las salas
  Sala* sala1 = crear_sala(1);
  Sala* sala2 = crear_sala(2);

  // Crear la cola de tickets
  Cola* cola_tickets = crear_cola();

  // Crear y agregar tickets a la cola
  Ticket ticket1 = {"Avengers Endgame", "14:00", sala1->id, 2, 3, 120.0f};
  encolar(cola_tickets, ticket1);
  Ticket ticket2 = {"Avengers Endgame", "14:00", sala1->id, 1, 1, 120.0f};
  encolar(cola_tickets, ticket2);

  // Procesar tickets
  Ticket* ticket;
  while((ticket = desencolar(cola_tickets)) != NULL) {
    imprimir_ticket(ticket);
  }

  free(sala1);
  free(sala2);
  free(cola_tickets);

  return 0;
}
