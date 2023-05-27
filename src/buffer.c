#include "buffer.h"

int buffer_init(buffer_t *buffer, int capacity)
{
    // create dynamic array
    buffer->array = malloc(capacity * sizeof(todo_t));

    // check malloc
    if (buffer->array == NULL)
    {
        return EXIT_FAILURE;
    }

    buffer->capacity = capacity;
    buffer->size = 0;

    return EXIT_SUCCESS; // stdlib.h
}

void buffer_destroy(buffer_t *buffer)
{
    free(buffer->array);
}

void buffer_dump(buffer_t *buffer)
{
    int i;
    char complete_bool_str[6];

    fprintf(stderr, "\n---- bounded buffer ---\n");
    fprintf(stderr, "size: %d\n", buffer->size);
    fprintf(stderr, "\n");

    for (i = 0; i < buffer->size; i++)
    {
        // para poder imprimir 'true' o 'false', en vez de 0 o 1
        bool_to_str(buffer->array[i].complete, complete_bool_str);
        fprintf(stderr, "buffer[%d]: (%d|%s|%s)\n", i, buffer->array[i].id, buffer->array[i].title, complete_bool_str);
    }
    fprintf(stderr, "--------------------------\n");
}

// util
void bool_to_str(int value_int, char *value_str)
{
    if (value_int == TRUE)
        strcpy(value_str, "true");
    // cualquier otro valor, false
    else
    {
        strcpy(value_str, "false");
    }
}

// == CRUD  ==

// creo un elemento y lo inserto al final del array
int buffer_create(buffer_t *buffer, todo_t *task)
{
    if (buffer->size < buffer->capacity)
    {
        buffer->array[buffer->size] = *task;
        buffer->size++;
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

// lectura de un elemento por 'id' (find)
// supongo que el id es unico (por ahora no hay ninguna restriccion, luego la incluiremos)
int buffer_read(buffer_t *buffer, todo_t *task, int id)
{
    int i;

    for (i = 0; i < buffer->size; i++)
    {
        if (buffer->array[i].id == id)
        {
            // copio la tarea
            task->id = buffer->array[i].id;
            strcpy(task->title, buffer->array[i].title);
            task->complete = buffer->array[i].complete;
            return TRUE;
        }
    }
    return FALSE;
}
