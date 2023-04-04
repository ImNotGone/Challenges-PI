#include <stdio.h>
#include <assert.h>

// dado un arreglo (no importa el tipo de los elementos),
// reordenar sus elementos de manera circular moviendo
// los elementos n posiciones a la izquierda (sentido antihorario)

// ej: nums = {1, 2, 3} con n = 1 => nums = {2, 3, 1}
// con n = 2 => nums = {3, 1, 2}
// con n = 3 => nums = {1, 2, 3}
// con n = 5 => nums = {3, 1, 2}


// @param nums: array de numeros a ordenar
// @param dim:  dimension del array
// @param n:    cant de rotaciones
// @param res:  array de salida
void rotate_arr(const int nums[], int dim, int n, int res[]);

int main() {
    const int nums[] = {1, 2, 3};
    int dim = 3;
    int res[3];

    int n = 0;
    rotate_arr(nums, dim, n, res);
    // expected: no varia
    for(int i = 0; i < dim; i++) {
        assert(nums[(i+n)%dim] == res[i]);
    }

    n = 1;
    rotate_arr(nums, dim, n, res);
    // expected se mueve 1 pos
    for(int i = 0; i < dim; i++) {
        assert(nums[(i+n)%dim] == res[i]);
    }

    n = 2;
    rotate_arr(nums, dim, n, res);
    // expected se mueve 2 pos
    for(int i = 0; i < dim; i++) {
        assert(nums[(i+n)%dim] == res[i]);
    }

    n = 3;
    rotate_arr(nums, dim, n, res);
    // expected no varia
    for(int i = 0; i < dim; i++) {
        assert(nums[(i+n)%dim] == res[i]);
    }

    n = 4;
    rotate_arr(nums, dim, n, res);
    // expected se mueve 1 pos
    for(int i = 0; i < dim; i++) {
        assert(nums[(i+n)%dim] == res[i]);
    }

    puts("OK!");
}


// @param nums: array de numeros a ordenar
// @param dim:  dimension del array
// @param n:    cant de rotaciones
// @param res:  array de salida
void rotate_arr(const int nums[], int dim, int n, int res[]) {

}
