#ifndef BUFFER_H
#define BUFFER_H

#include <stdio.h>
#include <stdlib.h> // EXIT_SUCCESS EXIT_FAILURE
#include <string.h> // strcpy

#include "todo.h"

void bool_to_str(int value_int, char *value_str);

typedef struct
{
    todo_t *array;
    int capacity;
    int size;
} buffer_t;

/**
 * Crea un array dinamico con el tamaño especificado.
 *
 * Recibe el puntero al buffer y el tamaño del array
 *
 * @param buffer es el puntero al array a inicializar (base address)
 * @param capacity es el tamaño maximo del array.
 *
 * @return EXIT_SUCCESS si la inicialziación fue exitosa, o EXIT_FAILURE si ocurrio algun error
 */
int buffer_init(buffer_t *, int capacity);

void buffer_destroy(buffer_t *);

void buffer_dump(buffer_t *);

// CRUD
int buffer_create(buffer_t *, todo_t *);

#endif