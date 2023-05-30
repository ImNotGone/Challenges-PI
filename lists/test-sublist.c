/*
Escribir una funcion recursiva llamada sublist() que reciba una lista y dos valores
enteros indicando el inicio y el fin de la sublista a devolver (comenzando desde 0).
La funcion debe devolver una nueva lista con los elementos de la sublista.

Si el inicio es mayor al fin, la funcion debe devolver NULL.
Si el fin es mayor a la longitud de la lista, la funcion debe devolver hasta el ultimo elemento.

Usar la siguiente definicion de lista:

typedef​ struct node * TList;

typedef​ struct node {
  int elem;
  struct node * tail;
} TNode;

Ejemplos:
Partiendo de una lista 5 -> 4 -> 3 -> 2 -> 1 -> NULL

- Input: start = 1, end = 3
  Output: 4 -> 3 -> 2 -> NULL

- Input: start = 0, end = 0
  Output: 5 -> NULL

- Input: start = 0, end = 10
  Output: 5 -> 4 -> 3 -> 2 -> 1 -> NULL

- Input: start = 10, end = 0
  Output: NULL

- Input: start = 7, end = 11
  Output: NULL
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node *TList;

typedef struct node
{
    int elem;
    struct node *tail;
} TNode;

// DEBE RESERVAR MEMORIA PARA LA LISTA NUEVA
TList sublist(TList list, int start, int end);

int main(void)
{
    TNode n1 = {1, NULL};
    TNode n2 = {2, &n1};
    TNode n3 = {3, &n2};
    TNode n4 = {4, &n3};
    TNode n5 = {5, &n4};

    TList list = &n5;

    // TODO: LIBERAR MEMORIA (NO DEBEN HABER MEMORY LEAKS)
    // USAR LA FLAG -fsanitize=address
    TList result = sublist(list, 1, 3);

    TNode n1_aux1 = {2, NULL};
    TNode n2_aux1 = {3, &n1_aux1};
    TNode n3_aux1 = {4, &n2_aux1};

    TList expected_1 = &n3_aux1;

    while (result != NULL)
    {
        assert(expected_1->elem == result->elem);
        result = result->tail;
        expected_1 = expected_1->tail;
    }

    assert(expected_1 == NULL);

    result = sublist(list, 0, 0);

    TNode n1_aux2 = {5, NULL};

    TList expected_2 = &n1_aux2;

    while (result != NULL)
    {
        assert(expected_2->elem == result->elem);
        result = result->tail;
        expected_2 = expected_2->tail;
    }

    assert(expected_2 == NULL);

    result = sublist(list, 0, 10);

    TNode n1_aux3 = {1, NULL};
    TNode n2_aux3 = {2, &n1_aux3};
    TNode n3_aux3 = {3, &n2_aux3};
    TNode n4_aux3 = {4, &n3_aux3};
    TNode n5_aux3 = {5, &n4_aux3};

    TList expected_3 = &n5_aux3;

    while (result != NULL)
    {
        assert(expected_3->elem == result->elem);
        result = result->tail;
        expected_3 = expected_3->tail;
    }

    assert(expected_3 == NULL);

    result = sublist(list, 10, 0);

    assert(result == NULL);

    result = sublist(list, 7, 11);

    assert(result == NULL);

    result = sublist(list, -2, -4);

    assert(result == NULL);

    result = sublist(list, -1, 2);

    assert(result == NULL);

    puts("OK!");
    return 0;
}


TList sublist(TList list, int start, int end) {
    return NULL;
}
