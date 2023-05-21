/*
Una montaña de numeros consiste en dado un numero n, imprimir todos los numeros de manera escalonada
ascendente hasta n y luego descendente hasta 1. Por ejemplo, si n = 5, la montaña de numeros es:
1 2 3 4 5 4 3 2 1

Se pide implementar la funcion number_mountain() que reciba un numero entero n y guarde
la montaña de numeros en un puntero. La montaña no puede estar formada por mas de 100 numeros
y debe contener al menos 1 numero.

En caso que no se pueda arma la montaña de numeros, la funcion debe devolver NULL.

Consideraciones:
- Liberar toda la memoria reservada (en caso de ser necesario).
- No utilizar variables globales.
- Se pueden usar funciones auxiliares.
- La funcion recursiva no debe ocupar mas de 4 lineas.

Tips:
- Combinar recursion de tipo stack (FILO - ida) con recursion de tipo cola (FIFO - vuelta).
- Pensar como la funcion recursiva sabe el numero a guardar en la montaña y como frenar la recursion (caso base).
- Pensar si se puede saber de antemano el tamaño de la montaña.

Ejemplos:
- Input: n = 5
  Output: mountain = [1, 2, 3, 4, 5, 4, 3, 2, 1]

- Input: n = 1
  Output: mountain = [1]

- Input: n = 0
  Output: mountain = NULL

- Input: n = 100
  Output: mountain = NULL

- Input: n = -5
  Output: mountain = NULL
*/

#include <stdio.h>
#include <stdlib.h>

static void number_mountain_rec(unsigned int n, unsigned int *mountain, unsigned int iteration)
{
    // guardo el numero de la iteracion en la posicion de la iteracion correspondiente
    mountain[iteration - 1] = iteration;

    // si llegue al tope de la montaña, finalizo la recursion
    if (n == iteration) return;

    // me muevo a la siguiente iteracion
    number_mountain_rec(n, mountain, iteration + 1);

    // ESTO YA ES LA VUELTA -> recursion de tipo cola (FIFO)
    // 2 * n - 1 me deja una posicion a la derecha del ultimo elemento, y le resto la iteracion que NO es un indice
    mountain[2 * n - 1 - iteration] = iteration; // alternativa con indices: mountain[(2 * n - 1) - 1 - (iteration - 1)] = iteration;
}

unsigned int *number_mountain(int n)
{
    if (n < 1 || (2 * n - 1) > 100)
    {
        return NULL;
    }
    unsigned int *mountain = malloc((2 * n - 1) * sizeof(unsigned int));

    number_mountain_rec(n, mountain, 1);
    return mountain;
}

int main()
{
    int n = -1;
    unsigned int *mountain = number_mountain(n);

    for (int i = 0; i < (2 * n - 1); i++)
    {
        printf("%d ", mountain[i]);
    }

    printf("\n");
    free(mountain);
    return 0;
}