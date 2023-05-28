#ifndef BUFFER_H
#define BUFFER_H

#include <stdio.h>
#include <stdlib.h> // EXIT_SUCCESS EXIT_FAILURE
#include <string.h> // strcpy

#include "data.h"
#include "util.h"

void bool_to_str(int value_int, char *value_str);

typedef struct
{
    data_t *array; // n * 136 bytes
    int capacity;  // 4 bytes
    int size;      // 4 bytes
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

int buffer_create(buffer_t *, void *, pointer_func_asignar_t asignar);

int buffer_read(buffer_t *, data_t *, int);

int buffer_update(buffer_t *, data_t *, int);

int buffer_delete(buffer_t *, int);

int buffer_item_id_found(buffer_t *, int);

// archivos

void save(buffer_t *);

void load(buffer_t *);

#endif