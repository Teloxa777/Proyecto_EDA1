#include "Ticket.h"


static Seats* Seats_New( size_t row, size_t column ) //Crea un nuevo asiento
{
    Seats* s = (Seats*) malloc( sizeof( Seats ) );
    if( s != NULL )
    {
        s->row = row;
        s->column = column;
        s->avaible = true;
        s->next = NULL;
        s->prev = NULL;
    }
    
    return s;
}

static void Seats_Erase( Seats** this) //Borra un asiento, solo se utilizara cuando sea necesario borrar todos los asientos, por lo que no requiere casos unico
{
    assert( this && *this );
    
    free( *this );
    *this = NULL;
}

Ticket Ticket_New() //Crea un nuevo Ticket
{
    Ticket t;
    t.film[ 0 ] = '\0';
    t.projection[ 0 ] = '\0';
    t.cinema_id = 0;
    t.price = 0;
    t.cursor = NULL;
    for (size_t i = 0; i < MAX_ROWS; i++) 
    {
        for (size_t j = 0; j < MAX_COLUMNS; j++) 
        {
            t.position[i][j] = NULL;
        }
    }
    
    return t;
}

void Ticket_Delete_Seats( Ticket* t ) // Recibe la direccion del ticket y borra sus asientos
{
    for (size_t i = 0; i < MAX_ROWS; i++)
    {
        for (size_t j = 0; j < MAX_COLUMNS; j++)
        {
            Seats* seat = t->position[ i ][ j ];
            if (seat != NULL) 
            {
                Seats_Erase( &seat );
                t->position[i][j] = NULL;
            }
        }
    }
}

void Ticket_Cursor_front( Ticket* this ) // Recibe la direccion del ticket y coloca el cursor al inicio de la lista de Salas
{
    assert( this );
    
    this->cursor = this->position[ 0 ][ 0 ];
}

void Ticket_Cursor_next( Ticket* this ) // Recibe direccion del ticket y mueve el cursor un asiento a la derecha
{
    assert( this );
    assert( this->cursor );
    
    Seats* right = this->cursor->next;
    this->cursor = right;
}

void Ticket_Cursor_prev( Ticket* this ) // Recibe direccion del ticket y mueve el cursor un asiento a la izquierda
{
    assert( this->cursor != NULL );
    
    Seats* left = this->cursor->prev;
    this->cursor = left;
}

bool Ticket_Get_Seats( const Ticket* this ) // Recibe la direccion del ticket y devuelve copia del estado del asiento en la posicion de la matriz
{
    assert( this );
    assert( this-> cursor );
    
    return this->cursor->avaible;
}

void Ticket_Take_Seats( Ticket* this ) // Recibe la direccion del ticket y marca el asiennto apuntado como ocupado
{
    assert( this );
    assert( this->cursor );
    
    this->cursor->avaible = false;
}

void Ticket_Leave_Seats( Ticket* this ) // Recibe la direccion del ticket y marca el asiento apuntado como ocupado
{
    assert( this );
    assert( this->cursor );
    
    this->cursor->avaible = true;
}

void Ticket_Values(Ticket *ticket, const char *film, const char *projection, unsigned int cinema_id, float price) // Recibe direccion del ticket y asigna valores
{
    assert(ticket);
    
    strncpy(ticket->film, film, MAX_FILM - 1); //MAX_FILM = 50
    strncpy(ticket->projection, projection, MAX_PROJECTION - 1); // MAX_PROJECTION = 6
    ticket->cinema_id = cinema_id;
    ticket->price = price;
    for (size_t i = 0; i < MAX_ROWS; i++) 
    {
        for (size_t j = 0; j < MAX_COLUMNS; j++) 
        {
            ticket->position[i][j] = Seats_New(i, j);
        }
    }
    for (size_t i = 0; i < MAX_ROWS; i++) 
    {
        for (size_t j = 0; j < MAX_COLUMNS; j++) 
        {
            if(i == 0 && j == 0) // Primer asiento
            {
                ticket->position[i][j]->next = ticket->position[i][j + 1];
                ticket->position[i][j]->prev = ticket->position[MAX_ROWS - 1][MAX_COLUMNS - 1];
            }
            else if (i == MAX_ROWS - 1 && j == MAX_COLUMNS - 1) // Ultimo asiento
            {
                ticket->position[i][j]->next = ticket->position[0][0];
                ticket->position[i][j]->prev = ticket->position[i][j - 1];
            }
            else if(j == MAX_COLUMNS - 1) // Ultimo asiento de la fila
            {
                ticket->position[i][j]->next = i == MAX_ROWS - 1 ? ticket->position[0][0] : ticket->position[i + 1][0];
                ticket->position[i][j]->prev = ticket->position[i][j - 1];
            }
            else if(j == 0) // Primer asiento de la fila
            {
                ticket->position[i][j]->next = ticket->position[i][j + 1];
                ticket->position[i][j]->prev = i == 0 ? ticket->position[MAX_ROWS - 1][MAX_COLUMNS - 1] : ticket->position[i - 1][MAX_COLUMNS - 1];
            }
            else // Cualquier asiento que no este en los extremos de la matriz
            {
                ticket->position[i][j]->next = ticket->position[i][j + 1];
                ticket->position[i][j]->prev = ticket->position[i][j - 1];
            }
        }
    }
    Ticket_Cursor_front(ticket);
}


void Ticket_Print( Ticket t ) 
{
    printf("Ticket de cine\n");
    printf("Película: %s\n", t.film);
    printf("Hora de proyección: %s\n", t.projection);
    printf("Sala: %d\n", t.cinema_id);
    printf("Precio: $%.2f\n", t.price);
    printf("El asiento es:\n Fila:%zu \n Columna:%zu\n ", t.cursor->row, t.cursor->column );
}