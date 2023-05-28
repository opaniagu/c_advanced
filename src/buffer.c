#include "buffer.h"

int buffer_init(buffer_t *buffer, int capacity)
{
    // create dynamic array
    buffer->array = malloc(capacity * sizeof(data_t));

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
        fprintf(stderr, "buffer[%d]: ", i);
        imprimir_estructura(&buffer->array[i], data_print_ptr);
    }
    fprintf(stderr, "--------------------------\n");
}

// == CRUD  ==

// creo un elemento y lo inserto al final del array
// en 'size' tengo la ultima posicion
int buffer_create(buffer_t *buffer, void *item, pointer_func_asignar_t asignar)
{
    if (buffer->size < buffer->capacity)
    {
        // buffer->array[buffer->size] = *item;
        asignar(&(buffer->array[buffer->size]), item);

        buffer->size++;
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

// lectura de un elemento por 'id' (find)
// supongo que el id es unico (por ahora no hay ninguna restriccion, luego la incluiremos)
int buffer_read(buffer_t *buffer, data_t *item, int id)
{
    int i;

    for (i = 0; i < buffer->size; i++)
    {
        if (buffer->array[i].id == id)
        {
            // copio la tarea
            // item->id = buffer->array[i].id;
            // strcpy(item->title, buffer->array[i].title);
            // item->complete = buffer->array[i].complete;
            *item = buffer->array[i];

            return TRUE;
        }
    }
    return FALSE;
}

// el id no haria falta enviar....lo podria leer desde item!
int buffer_update(buffer_t *buffer, data_t *item, int id)
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
    index = buffer_item_id_found(buffer, id);
    if (index > 0)
    {
        // actualizo, el id no hace falta actualizar
        // strcpy(buffer->array[index].title, item->title);
        // buffer->array[index].complete = item->complete;

        buffer->array[index] = *item; // copio la estructura

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
    index = buffer_item_id_found(buffer, id);
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

int buffer_item_id_found(buffer_t *buffer, int id)
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

// under testing

void save(buffer_t *buffer)
{
    FILE *fp;

    fp = fopen("c_advanced.db", "w");

    // no guardo todo el array('capacity'), solo los registros cargados('size')
    fwrite(buffer->array, (buffer->size) * sizeof(data_t), 1, fp);

    fclose(fp);
}

void load(buffer_t *buffer)
{
    FILE *fp;
    int tamano;
    int q;

    fp = fopen("c_advanced.db", "r");
    if (fp == NULL)
    {
        printf("Error al abrir el archivo\n");
        exit(-1);
    }

    fseek(fp, 0, SEEK_END);      // Mover el puntero de posición al final del archivo
    tamano = ftell(fp);          // Obtener la posición actual del puntero de posición (que es el tamaño del archivo)
    q = tamano / sizeof(data_t); // cantidad de registros en el archivo
    if (q > buffer->capacity)    // si la cantidad de registros es mayor a la capacidad, trunco
    {
        q = buffer->capacity;
        tamano = q * sizeof(data_t);
        // emito un warning, mas adelante lo puedo enviar a un syslog
        fprintf(stderr, "Se intento cargar una base de datos con mas registros de la capacidad\n");
    }

    fseek(fp, 0, SEEK_SET); // Mover el puntero de posición al inicio del archivo
    fread(buffer->array, tamano, 1, fp);
    buffer->size = q;

    fclose(fp);
}

// import desde un archivo .csv
// (1) generar mock de datos
// https://www.mockaroo.com/
void import(buffer_t *buffer)
{
    FILE *file;
    char str[FILE_LINE_LEN];
    int numLeidos;
    data_t data;

    // abro el archivo
    file = fopen(FILE_CSV, "r");
    if (file == NULL)
    {
        printf("Arhivo csv no encontrado\n");
        exit(-1);
    }

    // proceso el archivo
    // fgets lee de a lineas, hasta encontrar 'newline' o
    // un fin de archivo 'EOF' o el tamaño maximo especificado

    while (fgets(str, FILE_LINE_LEN, file) != NULL)
    {
        // string_to_struct(str, &p);
        numLeidos = sscanf(str, "%d,%128[^,],%d", &data.id, data.title, &data.complete);
        if (numLeidos > 0)
        {
            // printf("title: %s\n", data.title);
            buffer_create(buffer, &data, asign_data);
        }
    }

    // cierro el archivo
    fclose(file);
}
