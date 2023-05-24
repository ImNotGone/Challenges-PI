/*
Escribir una funcion llamada rotate_list() que reciba una lista y un valor
entero n y devuelva una lista con los elementos rotados a la derecha la cantidad
de veces indicada por el valor entero n.

Usar la siguiente definicion de lista:

typedef​ struct node * TList;

typedef​ struct node {
  int elem;
  struct node * tail;
} TNode;

Consideraciones:
- Se pueden usar funciones auxiliares, las que sean necesarias.
- No es necesario crear una nueva lista, se puede manipular la lista original.

Ejemplos:
Partiendo de una lista 5 -> 4 -> 3 -> 2 -> 1 -> NULL

- Input: n = 0
  Output: 5 -> 4 -> 3 -> 2 -> 1 -> NULL (no se rota la lista)

- Input: n = 1
  Output: 1 -> 5 -> 4 -> 3 -> 2 -> NULL

- Input: n = 2
  Output: 2 -> 1 -> 5 -> 4 -> 3 -> NULL

- Input: n = 3
  Output: 3 -> 2 -> 1 -> 5 -> 4 -> NULL

- Input: n = 4
  Output: 4 -> 3 -> 2 -> 1 -> 5 -> NULL

- Input: n = 5
  Output: 5 -> 4 -> 3 -> 2 -> 1 -> NULL (no se rota la lista)

- Input: n = 6
  Output: 1 -> 5 -> 4 -> 3 -> 2 -> NULL
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node *TList;

typedef struct node
{
    int elem;
    struct node *tail;
} TNode;

static unsigned int list_length(TList list)
{
    if (list == NULL)
    {
        return 0;
    }

    return 1 + list_length(list->tail);
}

static TList rotate_list_rec(TList list, unsigned int cut_position)
{
    // si llegue al final o a la posicion de corte, devuelvo la lista
    if (list == NULL || cut_position == 0)
    {
        return list;
    }

    // espero a que me devuelvan el nodo de corte
    TList result = rotate_list_rec(list->tail, cut_position - 1);

    // si estoy en el nodo previo al corte, corto la lista
    if (cut_position == 1)
    {
        list->tail = NULL;
    }

    // devuelvo el nodo de corte
    return result;
}

static void append_list(TList list, TList tail)
{
    if (list == NULL) {
        return;
    }

    if (list->tail == NULL) {
        list->tail = tail;
        return;
    }

    append_list(list->tail, tail);
}

TList rotate_list(TList list, unsigned int times)
{
    unsigned int length = list_length(list);

    // evitar que se hagan vueltas de mas
    times = times % length;

    // si no hay que rotar, devuelvo la lista
    if (times == 0)
    {
        return list;
    }

    // calculo la posicion de corte
    unsigned int cut_position = length - times;

    // busco el nodo de corte
    TList new_tail = rotate_list_rec(list, cut_position);

    // ahora tengo que hacer que el ultimo nodo apunte al primero, uniendo los extremos
    append_list(new_tail, list);

    return new_tail;    
}

static void print_rotation(unsigned int n) {
    TNode n1 = {1, NULL};
    TNode n2 = {2, &n1};
    TNode n3 = {3, &n2};
    TNode n4 = {4, &n3};
    TNode n5 = {5, &n4};

    TList list = &n5;

    TList rotated = rotate_list(list, n);

    printf("Rotated %d times:\n", n);
    while (rotated != NULL)
    {
        printf("%d\n", rotated->elem);
        rotated = rotated->tail;
    }

    puts("#####################");
}

int main()
{
    print_rotation(0); // no deberia rotar
    print_rotation(1); // 1 -> 5 -> 4 -> 3 -> 2
    print_rotation(2); // 2 -> 1 -> 5 -> 4 -> 3
    print_rotation(3); // 3 -> 2 -> 1 -> 5 -> 4
    print_rotation(4); // 4 -> 3 -> 2 -> 1 -> 5
    print_rotation(5); // no deberia rotar
    print_rotation(6); // 1 -> 5 -> 4 -> 3 -> 2
    return 0;
}