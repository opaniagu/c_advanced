/**
 * Compilar: gcc -Wall -Iinclude src/main.c -o bin/main
 * Ejecutar: ./bin/main
 **/
#include "c_advanced.h"

// se define aca porque tiene que ser independiente de la implementacion de 'buffer'
#define BUFFER_LEN 3

int main(void)
{
    int resultado;

    printf("Bienvenidos al curso C Avanzado!\n");

    // test de las apis de 'buffer'
    buffer_t buffer;

    // forma de declarar e inicializar uns struct indicando .campo
    // ojo que si la estructura ya esta declarada, no se peude igualar un str!
    todo_t tarea = {
        .id = 1,
        .title = "Tarea #1",
        .complete = FALSE,
    };

    if (buffer_init(&buffer, BUFFER_LEN))
    {
        printf("Error en la creacion del buffer\n");
        return -1;
    }

    resultado = buffer_create(&buffer, &tarea);
    if (resultado != EXIT_SUCCESS)
        printf("Se produjo un error en buffer_create(). Código de error: %d\n", resultado);

    // creo una nueva tarea, reutilizo estructura 'tarea'
    tarea.id = 2;
    strcpy(tarea.title, "Tarea #2");
    tarea.complete = TRUE;
    resultado = buffer_create(&buffer, &tarea);
    if (resultado != EXIT_SUCCESS)
        printf("Se produjo un error en buffer_create(). Código de error: %d\n", resultado);

    resultado = buffer_create(&buffer, &tarea);
    if (resultado != EXIT_SUCCESS)
        printf("Se produjo un error en buffer_create(). Código de error: %d\n", resultado);

    resultado = buffer_create(&buffer, &tarea); // se descarta, buffer full
    if (resultado != EXIT_SUCCESS)
        printf("Se produjo un error en buffer_create(). Código de error: %d\n", resultado);

    resultado = buffer_create(&buffer, &tarea); // se descarta, buffer full
    if (resultado != EXIT_SUCCESS)
        printf("Se produjo un error en buffer_create(). Código de error: %d\n", resultado);

    // muestro la lista de tarea
    buffer_dump(&buffer);

    // libero el buffer
    buffer_destroy(&buffer);

    return 0;
}