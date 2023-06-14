#include "Room.h"
/**
 * @brief Crea un nuevo objeto Room.
 * 
 * @return Room* El objeto Room recién creado.
 */
Room* Room_New() 
{
    Room* room = (Room*)malloc(sizeof(Room));
    if (room != NULL)
    {
        room->first_ticket = NULL;
        strncpy(room->film, "", FILM_SIZE);
    }
    return room;
}
/**
 * @brief Elimina un objeto Room.
 * 
 * @param room Un doble puntero al objeto Room que se va a eliminar.
 */
void Room_Delete(Room** room)
{
    if(room && *room)
    {
        Ticket* current_ticket = (*room)->first_ticket;
        while(current_ticket != NULL) 
        {
            Ticket* next_ticket = current_ticket->next;
            Ticket_Delete(&current_ticket);
            current_ticket = next_ticket;
        }
        free(*room);
        *room = NULL;
    }
}
/**
 * @brief Obtiene el primer boleto de la sala.
 * 
 * @param room Un puntero al objeto Room.
 * @return Ticket* El primer boleto de la sala.
 */
Ticket* Room_GetFirstTicket(Room* room)
{
    return room ? room->first_ticket : NULL;
}
/**
 * @brief Agrega un nuevo boleto a la sala.
 * 
 * @param room Un puntero al objeto Room.
 * @param film El nombre de la película.
 * @param room_number El número de la sala.
 * @param row El número de fila del asiento.
 * @param column El número de columna del asiento.
 * @param price El precio del boleto.
 */
void Room_AddTicket(Room* room, const char* film, int room_number, int row, int column, float price)
{
    if(room)
    {
        Ticket* new_ticket = Ticket_New(film, room_number, row, column, price);
        new_ticket->next = room->first_ticket;
        room->first_ticket = new_ticket;
    }
}
/**
 * @brief Obtiene el nombre de la película de la sala.
 * 
 * @param room Un puntero al objeto Room.
 * @return char* El nombre de la película de la sala.
 */
char* Room_GetFilm(Room* room)
{
    return room ? room->film : NULL;
}

/**
 * @brief Establece el nombre de la película de la sala.
 * 
 * @param room Un puntero al objeto Room.
 * @param film El nombre de la película.
 */
void Room_SetFilm(Room* room, const char* film)
{
    if(room && film)
    {
        strncpy(room->film, film, FILM_SIZE);
        room->film[FILM_SIZE - 1] = '\0'; // Asegurarse de terminar la cadena
    }
}
/**
 * @brief Imprime todos los boletos en la sala.
 * 
 * @param room Un puntero al objeto Room.
 */
void Room_PrintTicket(const Room* room) 
{
    Ticket* current_ticket = room->first_ticket;
    while(current_ticket != NULL) 
    {
        Ticket_Print(current_ticket);
        current_ticket = current_ticket->next;
    }
}