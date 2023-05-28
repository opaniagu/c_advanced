#include "config.h"

void config_init(config_t *config)
{

    // seteo los valores por default
    config->database_size = DATABASE_SIZE_DEFAULT;
    strcpy(config->database_name, DATABASE_FILE_NAME_DEFAULT);

    // los reemplazo por variables de entorno, si existen
    char *valor1 = getenv(ENV_DATABASE_SIZE);
    char *valor2 = getenv(ENV_DATABASE_FILE_NAME);

    // TODO: se podrian agregar mas validaciones...

    if (valor1 != NULL)
        config->database_size = atoi(valor1);

    if (valor2 != NULL)
        strcpy(config->database_name, valor2);
}

void config_print(const config_t *config)
{
    printf("=== config start ===\n");
    printf("Capacidad de la base de datos: %d\n", config->database_size);
    printf("Nombre del archivo de la base de datos: %s\n", config->database_name);
    printf("=== config end ===\n");
}