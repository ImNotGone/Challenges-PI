#include <stdio.h>

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

void bubble_sort(int *array, unsigned int length)
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

// excluimos el 0 y los negativos
unsigned int remove_negatives(int *array, unsigned int length)
{
  unsigned int newDim = 0;
  for(unsigned int i = 0; i < length; i++)
  {
    if(array[i] > 0)
    {
      array[newDim++] = array[i];
    }
  }

  return newDim;
}

unsigned int smallest_missing_int(int *array, unsigned int length)
{
  unsigned int newDim = remove_negatives(array, length);
  // si no hay elementos positivos, el menor entero que no esta en el array es 1
  if (!newDim)
  {
    return 1;
  }

  bubble_sort(array, newDim);
  // si el primer elemento es mayor que 1, el menor entero que no esta en el array es 1
  if (array[0] != 1)
  {
    return 1;
  }
  
  for (unsigned int i = 0; i < newDim - 1; i++)
  {
    // en cuanto la diferencia entre dos elementos consecutivos sea mayor a 1, 
    // el menor entero que no esta en el array es el siguiente al primero
    if (array[i + 1] - array[i] > 1)
    {
      return array[i] + 1;
    }
  }

  // si todos los elementos son consecutivos, el menor entero que no esta en el array es el siguiente al ultimo
  return array[newDim - 1] + 1;
}

int main(void)
{
  int array[] = {9,8,6,5,4,3,2,1,0,-1,-2,-3,-4,-5,-6,-7,-8,-9};
  unsigned int length = sizeof(array) / sizeof(array[0]);
  printf("smallest_missing_int(array, %d) = %d\n", length, smallest_missing_int(array, length));
  return 0;
}