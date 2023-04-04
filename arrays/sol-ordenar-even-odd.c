#include <stdio.h>
#include <assert.h>

// Dado un arreglo de elementos enteros,
// reordenarlo poniendo todos los numeros pares al inicio (y los impares al final)

// Retornar en res cualquier arreglo que cumpla la condicion
// Por ejemplo: si el array de entrada es {3, 1, 2, 4}

// Las soluciones validas serian
//  1) {2, 4, 1, 3}
//  2) {2, 4, 3, 1}
//  3) {4, 2, 1, 3}
//  4) {4, 2, 3, 1}


// @param nums: array de numeros a ordenar
// @param dim: dimension del array
// @param res: array de salida
void order_even_uneven(int nums[], int dim, int res[]);

int main() {
    int nums[] = {3, 1, 2, 4};
    int dim = 4;
    int res[4];

    order_even_uneven(nums, dim, res);

    int i = 0;
    int expected_even = 2;
    for (; i < expected_even; i++) {
        assert(res[i] % 2 == 0);
    }

    for (; i < dim; i++) {
        assert(res[i] % 2 == 1);
    }

    puts("OK!");
    return 0;
}

// @param nums: array de numeros a ordenar
// @param dim: dimension del array
// @param res: array de salida
void order_even_uneven(int nums[], int dim, int res[]) {
    for(int i = 0, evenIdx = 0, oddIdx = dim; i < dim; ++i) {
        res[nums[i] % 2 == 1? --oddIdx : evenIdx++] = nums[i]; // nums[i] & 1 sería otra opcion
    }
}
