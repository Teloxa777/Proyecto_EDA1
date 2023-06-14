#include "Ticket.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h> 
/**
 * @brief Crea un nuevo objeto Ticket.
 * 
 * @param film El nombre de la película.
 * @param room El número de la sala.
 * @param row El número de fila del asiento.
 * @param column El número de columna del asiento.
 * @param price El precio del boleto.
 * @return Ticket* El objeto Ticket recién creado.
 */
Ticket* Ticket_New(const char* film, int room, int row, int column, float price)
{
    Ticket* ticket = (Ticket*)malloc(sizeof(Ticket));
    if (ticket != NULL)
    {
        strcpy(ticket->film, film);
        ticket->room = room;
        ticket->row = row; 
        ticket->column = column; 
        ticket->price = price;
        ticket->next = NULL; // Inicializa el nuevo campo 'next' a NULL
    }
    return ticket;
}
/**
 * @brief Elimina un objeto Ticket.
 * 
 * @param ticket Un doble puntero al objeto Ticket que se va a eliminar.
 */
void Ticket_Delete(Ticket** ticket)
{
    if (ticket && *ticket)
    {
        free(*ticket);
        *ticket = NULL;
    }
}
/**
 * @brief Obtiene el nombre de la película del boleto.
 * 
 * @param ticket Un puntero constante al objeto Ticket.
 * @return const char* El nombre de la película del boleto.
 */
const char* Ticket_GetFilm(const Ticket* ticket)
{
    return ticket ? ticket->film : NULL;
}
/**
 * @brief Obtiene el número de la sala del boleto.
 * 
 * @param ticket Un puntero constante al objeto Ticket.
 * @return int El número de la sala del boleto.
 */
int Ticket_GetRoom(const Ticket* ticket)
{
    return ticket ? ticket->room : -1;
}
/**
 * @brief Obtiene el número de fila del asiento del boleto.
 * 
 * @param ticket Un puntero constante al objeto Ticket.
 * @return int El número de fila del asiento del boleto.
 */
int Ticket_GetRow(const Ticket* ticket)
{
    return ticket ? ticket->row : -1;
}
/**
 * @brief Obtiene el número de columna del asiento del boleto.
 * 
 * @param ticket Un puntero constante al objeto Ticket.
 * @return int El número de columna del asiento del boleto.
 */
int Ticket_GetColumn(const Ticket* ticket)
{
    return ticket ? ticket->column : -1;
}
/**
 * @brief Obtiene el precio del boleto.
 * 
 * @param ticket Un puntero constante al objeto Ticket.
 * @return float El precio del boleto.
 */
float Ticket_GetPrice(const Ticket* ticket)
{
    return ticket ? ticket->price : -1.0;
}
/**
 * @brief Imprime la información del boleto.
 * 
 * @param ticket Un puntero constante al objeto Ticket.
 */
void Ticket_Print(const Ticket* ticket)
{
    if(ticket != NULL) 
    {
        printf("Pelicula: %s\n", ticket->film);
        printf("Sala: %d\n", ticket->room);
        printf("Fila: %d\n", ticket->row);
        printf("Columna: %d\n", ticket->column);
        printf("Precio: %.2f\n", ticket->price);
        printf("---------------\n");
    }
}