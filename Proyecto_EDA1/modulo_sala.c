#include <stdlib.h>
#include "modulo_sala.h"

Sala* crear_sala(int id) {
  Sala* sala = malloc(sizeof(Sala));
  sala->id = id;
  // Inicializar asientos a 1 (disponibles)
  for (int i = 0; i < MAX_ASIENTOS; i++) {
    for (int j = 0; j < MAX_ASIENTOS; j++) {
      sala->asientos[i][j] = 1;
    }
  }
  return sala;
}
