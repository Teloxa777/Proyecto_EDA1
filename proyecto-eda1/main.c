#include <stdio.h>
#include "Cinemas.c"
#include "Ticket.c"
#define Max_tickets 5
int main() {
    // Crear una instancia de la lista de cines
    Cinemas* cinemas = Cinemas_New();
    
    // Crear nuevos boletos
    for (size_t i = 0; i < Max_tickets; i++)
    {
         // Establecer los valores para los boletos
         Ticket ticket = Ticket_New();
         Ticket_Values(&ticket, "La papu pelicula", "18:00", 1, 10.0+i);
          // Agregar los boletos a la lista de cines
         Cinemas_Push_back(cinemas, ticket);
    }

    Ticket currentTicket = Cinemas_Cursor_Get(cinemas);
size_t len = Cinemas_Len(cinemas);
Cinemas_Cursor_front(cinemas); //Coloca el cursor al inicio
for (size_t i = 0; i < len; i++)
{
    currentTicket = Cinemas_Cursor_Get(cinemas);
    Ticket_Print(currentTicket);
    Cinemas_Cursor_next(cinemas);
}

    // Limpiar y borrar la lista de cines
    Cinemas_MakeEmpty(cinemas);
    Cinemas_Delete(&cinemas);

    return 0;
}
