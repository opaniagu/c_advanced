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
    // char complete_bool_str[6];

    fprintf(stderr, "\n---- bounded buffer ---\n");
    fprintf(stderr, "size: %d\n", buffer->size);
    fprintf(stderr, "\n");

    for (i = 0; i < buffer->size; i++)
    {
        // para poder imprimir 'true' o 'false', en vez de 0 o 1
        // bool_to_str(buffer->array[i].complete, complete_bool_str);
        // fprintf(stderr, "buffer[%d]: (%d|%s|%s)\n", i, buffer->array[i].id, buffer->array[i].title, complete_bool_str);
        fprintf(stderr, "buffer[%d]: ", i);
        // todo_print(&buffer->array[i]);
        // utilizo puntero a funcion para imprimir la estructura
        // y que sea aun mas generica la implementacion de 'buffer'
        imprimir_estructura(&buffer->array[i], todo_print_ptr);
    }
    fprintf(stderr, "--------------------------\n");
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
            // task->id = buffer->array[i].id;
            // strcpy(task->title, buffer->array[i].title);
            // task->complete = buffer->array[i].complete;
            *task = buffer->array[i];

            return TRUE;
        }
    }
    return FALSE;
}

// el id no haria falta enviar....lo podria leer desde task!
int buffer_update(buffer_t *buffer, todo_t *task, int id)
{
    // int i;
    int index = -1;

    // busco el id
    // for (i = 0; i < buffer->size; i++)
    // {
    //     if (buffer->array[i].id == id)
    //     {
    //         index = i;
    //         break;
    //     }
    // }
    index = buffer_task_id_found(buffer, id);
    if (index > 0)
    {
        // actualizo, el id no hace falta actualizar
        // strcpy(buffer->array[index].title, task->title);
        // buffer->array[index].complete = task->complete;

        buffer->array[index] = *task; // copio la estructura

        return TRUE;
    }
    return FALSE;
}

int buffer_delete(buffer_t *buffer, int id)
{
    int i;
    int index = -1;

    // 1) verificar que id sea un valor valido
    if (id < 0 || id > buffer->size)
    {
        printf("Posicion ingresada no valida\n");
        return EXIT_FAILURE;
    }

    // 2) con el id, tengo que buscar la posicion en el array
    // for (i = 0; i < buffer->size; i++)
    // {
    //     if (buffer->array[i].id == id)
    //     {
    //         index = i;
    //         break;
    //     }
    // }
    index = buffer_task_id_found(buffer, id);
    if (index < 0)
    {
        return EXIT_FAILURE;
    }

    // 3) desplazo a la izquierda desde la posicion indicada
    for (i = index; i < buffer->size - 1; i++)
    {
        // en C con las estructuras se puede utilizar el operador de asignacion (=)
        buffer->array[i] = buffer->array[i + 1];
    }

    // 4) Actualizar el tamaño del array
    buffer->size--;
    return EXIT_SUCCESS;
}

int buffer_task_id_found(buffer_t *buffer, int id)
{
    int i, index;

    for (i = 0; i < buffer->size; i++)
    {
        if (buffer->array[i].id == id)
        {
            index = i;
            break;
        }
    }
    return index;
}