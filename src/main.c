/**
 * Compilar: gcc -Wall -Iinclude src/main.c -o bin/main
 * Ejecutar: ./bin/main
 **/
#include "c_advanced.h"

// se define aca porque tiene que ser independiente de la implementacion de 'buffer'
#define BUFFER_LEN 10

int main(void)
{
    int resultado;

    printf("Bienvenidos al curso C Avanzado!\n");

    // configuracion de la app
    config_t config;
    config_init(&config);
    config_print(&config);

    // test de las apis de 'buffer'
    buffer_t buffer;

    // forma de declarar e inicializar uns struct indicando .campo
    // ojo que si la estructura ya esta declarada, no se peude igualar un str!
    data_t tarea = {
        .id = 1,
        .title = "Tarea #1",
        .complete = FALSE,
    };

    // if (buffer_init(&buffer, BUFFER_LEN))
    if (buffer_init(&buffer, config.database_size))
    {
        printf("Error en la creacion del buffer\n");
        return -1;
    }

    // resultado = buffer_create(&buffer, &tarea, asign_data);
    // if (resultado != EXIT_SUCCESS)
    //     printf("Se produjo un error en buffer_create(). Código de error: %d\n", resultado);

    // test de 'load' de la base de daos (bin)
    load(&buffer, config.database_name);

    // import
    import(&buffer);

    buffer_dump(&buffer);

    // test de 'save'
    save(&buffer, config.database_name);

    // creo una nueva tarea, reutilizo estructura 'tarea'
    // tarea.id = 2;
    // strcpy(tarea.title, "Tarea #2");
    // tarea.complete = TRUE;
    // resultado = buffer_create(&buffer, &tarea);
    // if (resultado != EXIT_SUCCESS)
    //     printf("Se produjo un error en buffer_create(). Código de error: %d\n", resultado);

    // tarea.id = 3;
    // resultado = buffer_create(&buffer, &tarea);
    // if (resultado != EXIT_SUCCESS)
    //     printf("Se produjo un error en buffer_create(). Código de error: %d\n", resultado);

    // tarea.id = 4;
    // resultado = buffer_create(&buffer, &tarea); // se descarta, buffer full
    // if (resultado != EXIT_SUCCESS)
    //     printf("Se produjo un error en buffer_create(). Código de error: %d\n", resultado);

    // tarea.id = 5;
    // resultado = buffer_create(&buffer, &tarea); // se descarta, buffer full
    // if (resultado != EXIT_SUCCESS)
    //     printf("Se produjo un error en buffer_create(). Código de error: %d\n", resultado);

    // muestro la lista de tarea
    buffer_dump(&buffer);

    // test read(find)
    data_t task;
    int found;

    found = buffer_read(&buffer, &task, 2);
    if (found)
    {
        data_print(&task);
    }

    // realizo un update
    task.complete = FALSE;
    strcpy(task.title, "Tarea #3");
    found = buffer_update(&buffer, &task, 3);
    if (found)
    {
        data_print(&task);
    }

    // elimino id=2
    buffer_dump(&buffer);
    buffer_delete(&buffer, 2);
    buffer_dump(&buffer);

    // libero el buffer
    buffer_destroy(&buffer);

    return 0;
}