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

- Input: n = 2 y usando como lista la rotada del ejemplo n = 2
  Output: 4 -> 3 -> 2 -> 1 -> 5 -> NULL (es equivalente a usar la lista original con n = 4)
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

TList rotate_list(TList list, unsigned int times);

int main()
{
    TNode n1 = {1, NULL};
    TNode n2 = {2, &n1};
    TNode n3 = {3, &n2};
    TNode n4 = {4, &n3};
    TNode n5 = {5, &n4};

    TList list = &n5;

    TList rotated = rotate_list(list, 2);
    TList rotated_copy = rotated;

    TNode n1_aux_4_2rot = {3, NULL};
    TNode n2_aux_4_2rot = {4, &n1_aux_4_2rot};
    TNode n3_aux_4_2rot = {5, &n2_aux_4_2rot};
    TNode n4_aux_4_2rot = {1, &n3_aux_4_2rot};
    TNode n5_aux_4_2rot = {2, &n4_aux_4_2rot};

    TList expected_for_2_rotations = &n5_aux_4_2rot;

    while (rotated != NULL)
    {
        assert(expected_for_2_rotations->elem == rotated->elem);
        rotated = rotated->tail;
        expected_for_2_rotations = expected_for_2_rotations->tail;
    }

    assert(expected_for_2_rotations == NULL);

    rotated = rotate_list(rotated_copy, 2);
    rotated_copy = rotated;

    TNode n1_aux_4_4rot = {5, NULL};
    TNode n2_aux_4_4rot = {1, &n1_aux_4_4rot};
    TNode n3_aux_4_4rot = {2, &n2_aux_4_4rot};
    TNode n4_aux_4_4rot = {3, &n3_aux_4_4rot};
    TNode n5_aux_4_4rot = {4, &n4_aux_4_4rot};

    TList expected_for_4_rotations = &n5_aux_4_4rot;

    while (rotated != NULL)
    {
        assert(expected_for_4_rotations->elem == rotated->elem);
        rotated = rotated->tail;
        expected_for_4_rotations = expected_for_4_rotations->tail;
    }

    assert(expected_for_4_rotations == NULL);

    rotated = rotate_list(rotated_copy, 2);

    TNode n1_aux_4_6rot = {2, NULL};
    TNode n2_aux_4_6rot = {3, &n1_aux_4_6rot};
    TNode n3_aux_4_6rot = {4, &n2_aux_4_6rot};
    TNode n4_aux_4_6rot = {5, &n3_aux_4_6rot};
    TNode n5_aux_4_6rot = {1, &n4_aux_4_6rot};

    TList expected_for_6_rotations = &n5_aux_4_6rot;

    while (rotated != NULL)
    {
        assert(expected_for_6_rotations->elem == rotated->elem);
        rotated = rotated->tail;
        expected_for_6_rotations = expected_for_6_rotations->tail;
    }

    assert(expected_for_6_rotations == NULL);

    puts("OK!");
    return 0;
}

TList rotate_list(TList list, unsigned int times) {
    return NULL;
}
