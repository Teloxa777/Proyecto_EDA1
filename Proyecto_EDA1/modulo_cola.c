#include <stdlib.h>
#include "modulo_cola.h"

Cola* crear_cola() {
  Cola* c = malloc(sizeof(Cola));
  c->front = c->rear = NULL;
  return c;
}

void encolar(Cola* c, Ticket t) {
  Nodo* n = malloc(sizeof(Nodo));
  n->ticket = t;
  n->next = NULL;
  if(c->rear == NULL) {
    c->front = c->rear = n;
    return;
  }
  c->rear->next = n;
  c->rear = n;
}

Ticket* desencolar(Cola* c) {
  if(c->front == NULL)
    return NULL;
  Nodo* n = c->front;
  Ticket* t = &n->ticket;
  c->front = c->front->next;
  if(c->front == NULL)
    c->rear = NULL;
  free(n);
  return t;
}
