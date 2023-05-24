/*
Escribir una funcion recursiva llamada sublist() que reciba una lista y dos valores
enteros indicando el inicio y el fin de la sublista a devolver (comenzando desde 0).
La funcion debe devolver una nueva lista con los elementos de la sublista.

Si el inicio es mayor o igual al fin, la funcion debe devolver NULL.
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

typedef struct node *TList;

typedef struct node
{
    int elem;
    struct node *tail;
} TNode;

TList sublist(TList list, unsigned int start, unsigned int end)
{
    // si la lista es nula o el inicio es mayor o igual al fin, devolver NULL
    if (list == NULL || start > end)
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

int main(void)
{
    TNode n1 = {1, NULL};
    TNode n2 = {2, &n1};
    TNode n3 = {3, &n2};
    TNode n4 = {4, &n3};
    TNode n5 = {5, &n4};

    TList list = &n5;

    // TODO: LIBERAR MEMORIA
    TList result = sublist(list, 1, 3);

    while (result != NULL)
    {
        printf("%d\n", result->elem);
        result = result->tail;
    }

    puts("#####################");

    result = sublist(list, 0, 0);

    while (result != NULL)
    {
        printf("%d\n", result->elem);
        result = result->tail;
    }

    puts("#####################");

    result = sublist(list, 0, 10);

    while (result != NULL)
    {
        printf("%d\n", result->elem);
        result = result->tail;
    }

    puts("#####################");

    result = sublist(list, 10, 0);

    while (result != NULL)
    {
        printf("%d\n", result->elem);
        result = result->tail;
    }

    puts("#####################");

    result = sublist(list, 7, 11);

    while (result != NULL)
    {
        printf("%d\n", result->elem);
        result = result->tail;
    }

    return 0;
}