#include <stdio.h>
#include "Cinemas.c"
#include "Ticket.c"

int main() {
    // Crear una instancia de la lista de cines
    Cinemas* cinemas = Cinemas_New();
    
    // Crear nuevos boletos
    Ticket ticket1 = Ticket_New();
    Ticket ticket2 = Ticket_New();

    // Establecer los valores para los boletos
    Ticket_Values(&ticket1, "Pelicula 1", "18:00", 1, 10.0);
    Ticket_Values(&ticket2, "Pelicula 2", "20:00", 1, 15.0);

    // Agregar los boletos a la lista de cines
    Cinemas_Push_back(cinemas, ticket1);
    Cinemas_Push_back(cinemas, ticket2);

    // Mover el cursor al frente de la lista
    Cinemas_Cursor_front(cinemas);
    
    // Imprimir el ticket en la posición actual del cursor
    Ticket currentTicket = Cinemas_Cursor_Get(cinemas);
    Ticket_Print(currentTicket);

    // Mover el cursor al siguiente ticket
    Cinemas_Cursor_next(cinemas);
    
    // Imprimir el ticket en la posición actual del cursor
    currentTicket = Cinemas_Cursor_Get(cinemas);
    Ticket_Print(currentTicket);

    // Limpiar y borrar la lista de cines
    Cinemas_MakeEmpty(cinemas);
    Cinemas_Delete(&cinemas);

    return 0;
}
