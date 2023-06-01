#include <stdio.h>
#include "modulo_ticket.h"

void imprimir_ticket(Ticket* t) {
  printf("Ticket de cine\n");
  printf("Pelicula: %s\n", t->nombre_pelicula);
  printf("Hora de proyeccion: %s\n", t->hora_proyeccion);
  printf("Sala: %d\n", t->numero_sala);
  printf("Precio: $%.2f\n", t->precio_entrada);
  printf("el asiento es:\n fila:%i \n columna:%i\n ",t->a2,t->a1);
}
