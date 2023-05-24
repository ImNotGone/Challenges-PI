/*
Escribir una funcion recursiva llamada is_present() que reciba una lista y un valor
y devuelva 1 si el valor se encuentra en la lista y 0 en caso contrario.

Usar la siguiente definicion de lista:

typedef​ struct node * TList; 

typedef​ struct node {
  int elem;
  struct node * tail;
} TNode;
*/

#include <stdio.h>

typedef struct node * TList;

typedef struct node {
  int elem;
  struct node * tail;
} TNode;

char is_present(TList list, int value) {
  if (list == NULL) {
    return 0;
  }

  if (list->elem == value) {
    return 1;
  }

  return is_present(list->tail, value);
}

int main(void) {
  TNode n1 = {1, NULL};
  TNode n2 = {2, &n1};
  TNode n3 = {3, &n2};
  TNode n4 = {4, &n3};
  TNode n5 = {5, &n4};

  TList list = &n5;

  printf("%d\n", is_present(list, 1));
  printf("%d\n", is_present(list, 2));
  printf("%d\n", is_present(list, 3));
  printf("%d\n", is_present(list, 4));
  printf("%d\n", is_present(list, 5));
  printf("%d\n", is_present(list, 6));

  return 0;
}