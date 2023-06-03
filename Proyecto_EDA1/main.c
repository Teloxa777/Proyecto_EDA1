#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "modulo_ticket.h"
#include "modulo_sala.h"
#include "modulo_cola.h"

int main() {
  // Crear la cola de salas
  Cola* cola_salas = Queue_New(MAX_SALAS); 

  // Crear las salas y agregarlas a la cola
  Sala* sala1 = crear_sala(1);
  Queue_Enqueue(cola_salas, sala1);
  Sala* sala2 = crear_sala(2);
  Queue_Enqueue(cola_salas, sala2);

  // Crear y asignar tickets a los asientos de las salas
  Ticket ticket1 = {"Avengers Endgame", "14:34", sala2->id, 1, 3, 120.0f};
  sala2->asientos[ticket1.a2][ticket1.a1] = &ticket1;
  Ticket ticket2 = {"Avengers Endgame", "14:00", sala1->id, 3, 1, 120.0f};
  sala1->asientos[ticket2.a2][ticket2.a1] = &ticket2;

  // Imprimir información de salas y sus tickets
  Sala* sala;
  while((sala = Queue_Dequeue(cola_salas)) != NULL) {
    printf("Sala ID: %d\n", sala->id);
    for (int i = 0; i < MAX_ASIENTOS; i++) {
      for (int j = 0; j < MAX_ASIENTOS; j++) {
        if(sala->asientos[i][j] != NULL){
          imprimir_ticket(sala->asientos[i][j]);
        }
      }
    }
  }

  free(sala1);
  free(sala2);
  Queue_Delete(&cola_salas);

  return 0;
}
