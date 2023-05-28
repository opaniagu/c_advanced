#ifndef DATA_H
#define DATA_H

#include <stdio.h>
#include "util.h"

#define TITLE_LEN 128

typedef struct data
{
    int id;                // 4 bytes
    char title[TITLE_LEN]; // 128 bytes
    int complete;          // 4 bytes
} data_t;                  // 136 bytes

// funcion que imprime la estructura
void data_print(data_t *data);

// funcion que imprime la estructura, pero la voy a utilizar
// con punteros a funciones
void data_print_ptr(const void *);

void asign_data(const void *, const void *);

#endif