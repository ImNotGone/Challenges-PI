/*
Dado un vector de N elementos enteros positivos, implementar la funcion
int_hash_table() que devuelva un puntero de punteros a enteros, donde la
cantidad de punteros es M, y cada posicion (es decir cada uno de los M punteros)
tiene una cantidad indicada en otro puntero recibido por parametro (contiene basura)
llamado quantities, entonces la cantidad de elementos del puntero i se indica en
quantities[i].

Cada elemento del vector recibido se asignara al puntero correspondiente de acuerdo
a una funcion provista llamada hash() que recibe un entero y la cantidad de punteros M,
y devuelve un entero positivo menor a M. En caso que no haya ningun elemento para un
puntero, se asignara NULL.

Prototipo:
unsigned int** int_hash_table(unsigned int* vector, unsigned int N, unsigned int* quantities, unsigned int M) {

Consideraciones:
- No guardar mas bytes de los necesarios, en caso de necesitarlo.
- Modularizar lo mas posible (ej. la funcion int_hash_table() debe tener una logica
  muy simple, delegando en otras funciones la resolucion de problemas ajenos a su
  responsabilidad).
- Liberar toda la memoria dinamica que se solicite, en caso de necesitarla.
- No utilizar ciclos anidados.

Ejemplos:
- Input: vector = {1, 2, 3}, N = 3, quantities = {?, ?, ?}, M = 2
- Output: { {2}, {1, 3} } porque 1 % 2 = 1, 2 % 2 = 0, 3 % 2 = 1
          quantities = {1, 2}

- Input: vector = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, N = 10, quantities = {?, ?, ?}, M = 3
- Output: { {3, 6, 9}, {1, 4, 7, 10}, {2, 5, 8} } porque 1 % 3 = 1, 2 % 3 = 2, 3 % 3 = 0, 4 % 3 = 1, ...
          quantities = {3, 4, 3}

- Input: vector = {1, 1, 1, 6, 6, 4, 0}, N = 7, quantities = {?, ?, ?, ?, ?}, M = 5
- Output: { {0}, {1, 1, 1, 6, 6}, {NULL}, {NULL}, {4} } porque 1 % 5 = 1, 6 % 5 = 1, 4 % 5 = 4, 0 % 5 = 0
          quantities = {1, 5, 0, 0, 1}

*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define BLOCK_SIZE 10

static unsigned int hash(unsigned int value, unsigned int M) {
    return value % M;
}

static void init(unsigned int** hash_table, unsigned int* quantities, unsigned int M) {
    for (unsigned int i = 0; i < M; i++) {
        hash_table[i] = NULL;
        quantities[i] = 0;
    }
}

static void realloc_hash_table_items(unsigned int** hash_table, unsigned int* quantities, unsigned int N) {
    for (unsigned int i = 0; i < N; ++i) {
        // verificar si el bloque NO esta lleno
        if(quantities[i] % BLOCK_SIZE < BLOCK_SIZE && quantities[i] != 0) {
            hash_table[i] = realloc(hash_table[i], quantities[i] * sizeof(unsigned int));
        }
    }
}
unsigned int** int_hash_table(unsigned int* vector, unsigned int N, unsigned int* quantities, unsigned int M) {
    unsigned int** hash_table = malloc(M * sizeof(unsigned int *));
    init(hash_table, quantities, M);

    for (unsigned int i = 0; i < N; ++i) {
        unsigned int index = hash(vector[i], M);
        if(quantities[index] % BLOCK_SIZE == 0) {
            hash_table[index] = realloc(hash_table[index], (quantities[index] + BLOCK_SIZE) * sizeof(unsigned int));
        }

        hash_table[index][quantities[index]++] = vector[i];
    }

    realloc_hash_table_items(hash_table, quantities, M);

    return hash_table;
}

int main() {
    unsigned int vector[] = {1, 1, 1, 6, 6, 4, 0};
    unsigned int quantities[7];
    unsigned int N = 7;
    unsigned int M = 5;

    unsigned int** hash_table = int_hash_table(vector, N, quantities, M);

    unsigned int expected_quantities[] = {1, 5, 0, 0, 1};
    unsigned int r1[] = {0};
    unsigned int r2[] = {1, 1, 1, 6, 6};
    unsigned int r5[] = {4};
    unsigned int * expected_map[] = {
        r1,
        r2,
        NULL,
        NULL,
        r5
    };

    for (int i = 0 ; i < M; i++) {
        assert(quantities[i] == expected_quantities[i]);
        for (int j = 0; j < expected_quantities[i]; j++) {
            assert(hash_table[i][j] == expected_map[i][j]);
        }
        if(quantities[i] == 0) {
            assert(hash_table[i] == expected_map[i]);
        }
    }

    // ESTE PROGRAMA TIENE LEAKS DE MEMORIA,
    // los pueden ver utilizando la flag -fsanitize=address
    // resuelvanlos :D
    puts("OK!");

    return 0;
}
