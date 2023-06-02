#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "modulo_cola.h"

Cola* Queue_New(size_t capacity) {
  Cola* c = malloc(sizeof(Cola));

  if(c != NULL) {
    c->queue = malloc(sizeof(Ticket) * capacity);

    if(c->queue != NULL) {
      c->capacity = capacity;
      c->front = 0;
      c->back = 0;
      c->len = 0;
    } else {
      free(c);
      c = NULL;
    }
  }

  return c;
}

void Queue_Delete(Cola** c) {
  assert(*c);
  free((*c)->queue);
  free(*c);
  *c = NULL;
}

void Queue_Enqueue(Cola* c, Ticket t) {
  assert(c->len < c->capacity);
  c->queue[c->back % c->capacity] = t;
  ++c->back;
  ++c->len;
}

Ticket* Queue_Dequeue(Cola* c) {
  if(c->len == 0)
    return NULL;
  Ticket* t = &c->queue[c->front % c->capacity];
  ++c->front;
  --c->len;
  return t;
}

size_t Queue_Len(Cola* c) {
  return c->len;
}

bool Queue_IsEmpty(Cola* c) {
  return c->len == 0;
}

bool Queue_IsFull(Cola* c) {
  return c->len == c->capacity;
}
