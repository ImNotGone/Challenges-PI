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

- Input: start = -2, end = -4
  Output: NULL

- Input: start = -1, end = 2
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

TList sublist(TList list, int start, int end)
{
    // si la lista es nula o el inicio es mayor o igual al fin, devolver NULL
    // o si end o start son negativos, devolver NULL
    if (list == NULL || start > end || start < 0 || end < 0)
    {
        return NULL;
    }

    // como en algun momento llegue al inicio, creo y devuelvo la lista
    if (start == 0)
    {
        TList result = malloc(sizeof(TNode));
        result->elem = list->elem;
        result->tail = sublist(list->tail, start, end - 1);
        return result;
    }

    // itero hasta llegar al inicio
    return sublist(list->tail, start - 1, end - 1);
}

static void freeList(TList first) {
    if(first == NULL) return;
    freeList(first->tail);
    free(first);
    return;
}

int main(void)
{
    TNode n1 = {1, NULL};
    TNode n2 = {2, &n1};
    TNode n3 = {3, &n2};
    TNode n4 = {4, &n3};
    TNode n5 = {5, &n4};

    TList list = &n5;

    TList result = sublist(list, 1, 3);
    TList result_aux = result;

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

    freeList(result_aux);
    result = sublist(list, 0, 0);
    result_aux = result;

    TNode n1_aux2 = {5, NULL};

    TList expected_2 = &n1_aux2;

    while (result != NULL)
    {
        assert(expected_2->elem == result->elem);
        result = result->tail;
        expected_2 = expected_2->tail;
    }

    assert(expected_2 == NULL);

    freeList(result_aux);
    result = sublist(list, 0, 10);
    result_aux = result;

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

    freeList(result_aux);
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
