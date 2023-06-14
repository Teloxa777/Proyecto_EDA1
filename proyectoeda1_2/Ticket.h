#ifndef TICKET_H
#define TICKET_H

#define FILM_SIZE 50
#define INFINITE 10000
#define MAX_DENOMS 5
#define MAX_CHANGE 999+1
#define MIN( x, y ) (x) < (y) ? (x) : (y)

typedef struct Ticket
{   struct Ticket* next;
    char film[FILM_SIZE];
    int room;
    int row;    // Nuevo campo para la fila del asiento.
    int column; // Nuevo campo para la columna del asiento.
    float price;
} Ticket;

typedef struct 
{
    int denom; // Valor de la moneda
    int quantity; // Cantidad de la moneda
} Coin;

Ticket* Ticket_New(const char* film, int room, int row, int column, float price); // Modificada para incluir fila y columna.
void Ticket_Delete(Ticket** ticket);

const char* Ticket_GetFilm(const Ticket* ticket);
int Ticket_GetRoom(const Ticket* ticket);
int Ticket_GetRow(const Ticket* ticket); // Nueva función para obtener la fila del asiento.
int Ticket_GetColumn(const Ticket* ticket); // Nueva función para obtener la columna del asiento.
float Ticket_GetPrice(const Ticket* ticket);
void Ticket_Print(const Ticket* ticket);

// Funciones del algoritmo

void init_table(int table[][MAX_CHANGE]); // Inicializa la tabla
int change_table(int i, int j, int denom[], int table[][MAX_CHANGE]); //Rellena la tabla de valores
void change(int change, int table[][MAX_CHANGE], Coin results[], int denom[MAX_DENOMS]); // Algoritmo PD que devuelve el cambio, la cantidad y el valor en monedas

#endif // TICKET_H