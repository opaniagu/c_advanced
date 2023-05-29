/**
 * Compilar: gcc -Wall -Iinclude src/main.c -o bin/main
 * Ejecutar: ./bin/main
 **/
#include "c_advanced.h"

// se define aca porque tiene que ser independiente de la implementacion de 'buffer'
#define BUFFER_LEN 10

void menu(buffer_t *buffer, config_t *config);
void opcion1(buffer_t *buffer);
void opcion2(buffer_t *buffer);
void opcion3(buffer_t *buffer, char *filename);
void opcion5(buffer_t *buffer, config_t *config);
void opcion6(buffer_t *buffer);
void opcion7(buffer_t *buffer);
void opcion8(buffer_t *buffer);

int main(void)
{
    buffer_t buffer;
    config_t config;

    config_init(&config);

    if (buffer_init(&buffer, config.database_size))
    {
        printf("Error en la creacion del buffer\n");
        return -1;
    }

    load(&buffer, config.database_name);

    menu(&buffer, &config);

    buffer_destroy(&buffer);

    return 0;
}

void menu(buffer_t *buffer, config_t *config)
{
    int opcion;
    while (1)
    {
        printf("==== Menú ====\n");
        printf("1. Dump\n");
        printf("2. Import .csv\n");
        printf("3. Save\n");
        printf("4. Exit\n");
        printf("5. Reset database\n");
        printf("6. Read by 'id'\n");
        printf("7. Delete by 'id'\n");
        printf("8. Update by 'id'\n");
        printf("Ingrese su opción: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            opcion1(buffer);
            break;
        case 2:
            opcion2(buffer);
            break;
        case 3:
            opcion3(buffer, config->database_name);
            break;
        case 4:
            printf("Saliendo del programa...\n");
            return;
        case 5:
            opcion5(buffer, config);
            break;
        case 6:
            opcion6(buffer);
            break;
        case 7:
            opcion7(buffer);
            break;
        case 8:
            opcion8(buffer);
            break;
        default:
            printf("Opción inválida. Por favor, ingrese un número válido.\n");
        }
    }
}

void opcion1(buffer_t *buffer)
{
    buffer_dump(buffer);
}

void opcion2(buffer_t *buffer)
{
    import(buffer);
}

void opcion3(buffer_t *buffer, char *filename)
{
    save(buffer, filename);
}

void opcion5(buffer_t *buffer, config_t *config)
{
    buffer_destroy(buffer);
    if (buffer_init(buffer, config->database_size))
    {
        printf("Error en la creacion del buffer\n");
    }
    save(buffer, config->database_name);
}

void opcion6(buffer_t *buffer)
{
    // read (find)
    data_t task;
    int found;
    int id;

    printf("Ingrese el id:");
    scanf(" %d", &id);

    found = buffer_read(buffer, &task, id);
    if (found)
    {
        data_print(&task);
    }
}

void opcion7(buffer_t *buffer)
{
    // delete
    int id;

    printf("Ingrese el id:");
    scanf(" %d", &id);

    buffer_delete(buffer, id);
}

void opcion8(buffer_t *buffer)
{
    // update
    int found;
    data_t data;

    __fpurge(stdin);
    printf("Ingrese el id:");
    scanf("%d", &data.id);
    __fpurge(stdin);
    printf("Ingrese el title:");
    fgets(data.title, 128, stdin);
    __fpurge(stdin);
    printf("Ingrese el complete[0,1]:");
    scanf("%d", &data.complete);

    // TODO: hacer validaciones

    // remover el ENTER
    size_t longitud = strlen(data.title);
    if (longitud > 0 && data.title[longitud - 1] == '\n')
    {
        data.title[longitud - 1] = '\0';
    }

    found = buffer_update(buffer, &data, data.id);
    if (found)
    {
        data_print(&data);
    }
}
