#include <stdio.h>
#include <assert.h>

/*
Dado un array de enteros, escribir una funcion smallest_missing_int()
para encontrar el entero más pequeño que no está en el array (a partir de 0 exclusive).

Consideraciones:
- El array puede contener numeros negativos y 0.
- El array puede contener numeros repetidos.
- El array puede estar desordenado.
- Se puede modificar el array de entrada.
- No utilizar mas de dos niveles de anidacion para los ciclos.
- Modularizar el codigo evitando concentrar toda la logica en la funcion smallest_missing_int().
- Utilizar el tipo de dato adecuado (ej: usar unsigned int o size_t para valores estrictamente positivos)

Ejemplo:
- array = [9,8,6,5,4,3,2,1,0,-1,-2,-3,-4,-5,-6,-7,-8,-9] => devuelve 7
- array = [0,1,2,3,4,5,6,7,8,9] => devuelve 10
- array = [1,9,3,-2,0,5,8,-6,7,4] => devuelve 2
- array = [0, -1, -2, -3, -1, 1, 1, 0, 39, 20, 11, 3, 4, 4, 5, 6, 2] => devuelve 7
- array = [-1, -3, -2, -3, 0, 3, 4] => devuelve 1
- array = [-3, -2, -2, -1] => devuelve 1
*/


// @brief encuentra el menor entero > 0 que no esta en el array
// @param array array de enteros
// @param length cantidad de elementos del array
// @return el menor entero que no esta en el array
unsigned int smallest_missing_int(int *array, unsigned int length);

int main(void)
{
  int array0[] = {9,8,6,5,4,3,2,1,0,-1,-2,-3,-4,-5,-6,-7,-8,-9};
  int * array = array0;
  unsigned int length = 18;
  // deberia devolver 7
  unsigned int expected = 7;
  unsigned int actual = smallest_missing_int(array, length);

  assert(actual == expected);

  int array1[] = {0,1,2,3,4,5,6,7,8,9};
  array = array1;
  length = 10;
  // deberia devolver 10
  expected = 10;
  actual = smallest_missing_int(array, length);
  assert(actual == expected);


  int array2[] = {1,9,3,-2,0,5,8,-6,7,4};
  array = array2;
  length = 10;
  // deberia devolver 2
  expected = 2;
  actual = smallest_missing_int(array, length);
  assert(actual == expected);


  int array3[] = {0, -1, -2, -3, -1, 1, 1, 0, 39, 20, 11, 3, 4, 4, 5, 6, 2};
  array = array3;
  length = 17;
  // deberia devolver 7
  expected = 7;
  actual = smallest_missing_int(array, length);
  assert(actual == expected);


  int array4[] = {-1, -3, -2, -3, 0, 3, 4};
  array = array4;
  length = 7;
  // deberia devolver 1
  expected = 1;
  actual = smallest_missing_int(array, length);
  assert(actual == expected);


  int array5[] = {-3, -2, -2, -1};
  array = array5;
  length = 4;
  // deberia devolver 1
  expected = 1;
  actual = smallest_missing_int(array, length);
  assert(actual == expected);

  puts("OK!");
  return 0;
}

unsigned int smallest_missing_int(int *array, unsigned int length)
{
    return 0;
}

