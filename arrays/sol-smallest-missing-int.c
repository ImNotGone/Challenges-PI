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

// @brief ordena el array de menor a mayor
// @param array array de enteros a ordenar
// @param length cantidad de elementos del array
// @return void
static void bubble_sort(int *array, unsigned int length)
{
  for (unsigned int i = 0, temp; i < length; i++)
  {
    for (unsigned int j = 0; j < length - 1; j++)
    {
      if (array[j] > array[j + 1])
      {
        temp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = temp;
      }
    }
  }
}

// @brief elimina los elementos negativos y el 0 del array
// @param array array de enteros para limpiar
// @param length cantidad de elementos del array
// @return la nueva dimension del array
static unsigned int remove_negatives(int *array, unsigned int length)
{
  unsigned int new_dim = 0;
  for(unsigned int i = 0; i < length; i++)
  {
    if(array[i] > 0)
    {
      array[new_dim++] = array[i];
    }
  }

  return new_dim;
}

// solcion O(n^2) temporal O(1) espacial
unsigned int smallest_missing_int(int *array, unsigned int length)
{
  unsigned int new_dim = remove_negatives(array, length);
  // si no hay elementos positivos, el menor entero que no esta en el array es 1
  if (!new_dim)
  {
    return 1;
  }

  bubble_sort(array, new_dim);
  // si el primer elemento es mayor que 1, el menor entero que no esta en el array es 1
  if (array[0] != 1)
  {
    return 1;
  }

  for (unsigned int i = 0; i < new_dim - 1; i++)
  {
    // en cuanto la diferencia entre dos elementos consecutivos sea mayor a 1,
    // el menor entero que no esta en el array es el siguiente al primero
    if (array[i + 1] - array[i] > 1)
    {
      return array[i] + 1;
    }
  }

  // si todos los elementos son consecutivos, el menor entero que no esta en el array es el siguiente al ultimo
  return array[new_dim - 1] + 1;
}

// solucion O(n) temporal O(n) espacial
unsigned int smallest_missing_int_On(int *array, unsigned int length)
{
    char seen_ints[length];
    for(int i = 0; i < length; i++) {
        seen_ints[i] = 0;
    }
    for(int i = 0; i < length; i++) {
        if(array[i] > 0 && array[i] < length) {
            seen_ints[array[i]]++;
        }
    }
    for(int i = 1; i < length; i++) {
        if(seen_ints[i] == 0) {
            return i;
        }
    }
    return length;
}
