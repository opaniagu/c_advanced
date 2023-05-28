#include "util.h"

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

void imprimir_estructura(const void *estructura, pointer_func_t imprimir)
{
    // llamo a la funcion a traves del puntero y le paso como argumento
    // la estructura a imprimir
    imprimir(estructura);
}