#ifndef TICKET_H
#define TICKET_H

#define FILM_SIZE 50

typedef struct Ticket
{   struct Ticket* next;
    char film[FILM_SIZE];
    int room;
    int row;    // Nuevo campo para la fila del asiento.
    int column; // Nuevo campo para la columna del asiento.
    float price;
} Ticket;

Ticket* Ticket_New(const char* film, int room, int row, int column, float price); // Modificada para incluir fila y columna.
void Ticket_Delete(Ticket** ticket);

const char* Ticket_GetFilm(const Ticket* ticket);
int Ticket_GetRoom(const Ticket* ticket);
int Ticket_GetRow(const Ticket* ticket); // Nueva función para obtener la fila del asiento.
int Ticket_GetColumn(const Ticket* ticket); // Nueva función para obtener la columna del asiento.
float Ticket_GetPrice(const Ticket* ticket);
void Ticket_Print(const Ticket* ticket);
#endif // TICKET_H