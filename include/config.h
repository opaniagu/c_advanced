#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h> // getenv - atoi

// valores por default
#define DATABASE_SIZE_DEFAULT 20
#define DATABASE_FILE_NAME_DEFAULT "c_advanced.db"

#define DATABASE_FILE_NAME_LEN 128

// nombre de las variables de entorno
// empieza con el nombre de mi app para que no colisiones
// con alguna otra app
#define ENV_DATABASE_SIZE "C_ADVANCED_DATABASE_SIZE"
#define ENV_DATABASE_FILE_NAME "C_ADVANCED_DATABASE_FILE_NAME"

/**
 * Para crear las variables de entorno desde el shell:
 *      export C_ADVANCED_DATABASE_SIZE=100
 *      export C_ADVANCED_DATABASE_FILE_NAME="bd.bin"
 *
 *      Tambien se podrian configurar al inicio en .bashrc o .bash_profile, de un usuario
 *      O de manera global en /etc/environment o crear un archivo en el directorio /etc/profile.d/
 */

typedef struct config
{
    int database_size;
    char database_name[DATABASE_FILE_NAME_LEN];

} config_t;

void config_init(config_t *);

void config_print(const config_t *);

#endif