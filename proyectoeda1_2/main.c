#include "Cinemas.h"
#include "Room.h"
#include "Ticket.h"
#include "Seat.h"
#include <stdio.h>

#define MAX_FILM_SIZE 50

int main() 
{
    const int NUM_OF_ROWS = 2;
    const int NUM_OF_SEATS = 4;

    // Creamos una lista de cines
    Cinemas* cinemas = Cinemas_New();
    
    // Agregamos dos salas de cine con películas predefinidas y sus respectivos asientos
    Room* room1 = Room_New();
    room1->first_row = Row_New(NUM_OF_ROWS);
    for (int i = 0; i < NUM_OF_ROWS; i++) {
        Seat_Fill(room1->first_row, i, NUM_OF_SEATS);
    }
    Room_SetFilm(room1, "Pelicula 1");
    Cinemas_Push_back(cinemas, room1);

    Room* room2 = Room_New();
    room2->first_row = Row_New(NUM_OF_ROWS);
    for (int i = 0; i < NUM_OF_ROWS; i++) {
        Seat_Fill(room2->first_row, i, NUM_OF_SEATS);
    }
    Room_SetFilm(room2, "Pelicula 2");
    Cinemas_Push_back(cinemas, room2);

    // Ciclo del menú
    while(1) 
    {
        int choice;
        printf("\nMenú:\n");
        printf("1. Seleccione sala y asiento\n");
        printf("2. Imprimir todos los tickets\n");
        printf("3. Salir\n");
        printf("Ingrese su elección: ");
        scanf("%d", &choice);
        
        switch(choice) 
        {
            case 1: 
            {
                int cinemaChoice, seatRow, seatColumn;
                
                // Elegir sala de cine
                printf("Seleccione una sala de cine (1 o 2): ");
                scanf("%d", &cinemaChoice);
                Room* selectedRoom = (cinemaChoice == 1) ? room1 : room2;
                printf("Has seleccionado la sala: %s\n", Room_GetFilm(selectedRoom));

                // Mostrar la sala y asientos disponibles
                Seat_Print(selectedRoom->first_row);
                
                // Elegir asiento
                printf("Ingrese la fila del asiento: ");
                scanf("%d", &seatRow);
                printf("Ingrese la columna del asiento: ");
                scanf("%d", &seatColumn);

                // Verificar si el asiento está ocupado
                Seat_SetPosition(selectedRoom->first_row, seatRow-1 , seatColumn );
                Seat* selectedSeat = Column_Cursor_GetSeat(selectedRoom->first_row->row[seatRow-1 ]);
                if (Seat_Occupied(selectedSeat)) {
                    printf("Lo siento, el asiento ya está ocupado.\n");
                    break;
                }
                else {
                    Seat_Select(Column_Cursor_GetSeat(selectedRoom->first_row->row[seatRow-1 ]));

                }
                
                // Crear y guardar el ticket en la sala seleccionada con el precio predeterminado
                Room_AddTicket(selectedRoom, Room_GetFilm(selectedRoom), cinemaChoice, seatRow, seatColumn, 10.0);
                
                break;
            }
            case 2: 
            {
                // Imprimir todos los tickets de todas las salas
                Cinemas_PrintTickets(cinemas);
                break;
            }
            case 3: 
            {
                // Salir del programa
                printf("Saliendo del programa.\n");
                Cinemas_Delete(&cinemas);
                return 0;
            }
            default: 
            {
                printf("Opción no válida.\n");
                break;
            }
        }
    }
    return 0;
}
