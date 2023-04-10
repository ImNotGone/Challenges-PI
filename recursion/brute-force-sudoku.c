#include <stdio.h>
#include <assert.h>

#define EMPTY 0
#define DIM 9
#define SQR_SIZE 3
#define MIN_VALUE 1
#define MAX_VALUE 9
#define false 0
#define true 1

/*
    Sudoku solver recursivo:

    - La funcion sudoku_solver recibira una matriz donde se representa un sudoku.
    - Debe devolver verdadero o falso, dependiendo si pudo o no encontrar la
    solucion.
    - En caso de devolver verdadero, la solucion debe encontrarse en la misma
    matriz de entrada.
    - En caso de devolver falso, la matriz de entrada puede quedar con 'basura'.

    Consideraciones:

    - Para tener mas informacion sudoku_solver deberia ser una 'wrapper' para
    otra funcion 'sudoku_solver_rec' donde ademas de la matriz se reciban por
    ejemplo la fila y columna actual.
*/

// @param: sudoku el sudoku a resolver, donde EMPTY son los valores a remplazar
//
// @return: true si lo resolvio, false si no pudo resolverlo
int sudoku_solver(char matriz[DIM][DIM]);

void print_sudoku(char sudoku[DIM][DIM]) {
  for(int i = 0; i < DIM; i++) {
    printf("{");
    for(int j = 0; j < DIM; j++) {
      printf("%d%c", sudoku[i][j], (j<DIM-1)?',':'\0');
    }
    printf("}%c\n",(i<DIM-1)?',':'\0');
  }
}

int main() {
    char sudoku[DIM][DIM] = {
        {0,0,0,8,0,1,0,0,0},
        {0,0,0,0,0,0,0,4,3},
        {5,0,0,0,0,0,0,0,0},
        {0,0,0,0,7,0,8,0,0},
        {0,0,0,0,0,0,1,0,0},
        {0,2,0,0,3,0,0,0,0},
        {6,0,0,0,0,0,0,7,5},
        {0,0,3,4,0,0,0,0,0},
        {0,0,0,2,0,0,6,0,0}
    };

    int expected[DIM][DIM] = {
        {2,3,7,8,4,1,5,6,9},
        {1,8,6,7,9,5,2,4,3},
        {5,9,4,3,2,6,7,1,8},
        {3,1,5,6,7,4,8,9,2},
        {4,6,9,5,8,2,1,3,7},
        {7,2,8,1,3,9,4,5,6},
        {6,4,2,9,1,8,3,7,5},
        {8,5,3,4,6,7,9,2,1},
        {9,7,1,2,5,3,6,8,4}
    };

    sudoku_solver(sudoku);
    for(int i = 0; i < DIM; i++) {
        for(int j = 0; j < DIM; j++) {
            assert(sudoku[i][j] == expected[i][j]);
        }
    }

    puts("OK!");
    return 0;
}

// @param: sudoku un sudoku
// @param: row la fila en la que quiero probar un valor
// @param: col la columna en la que quiero probar un valor
// @param: value el valor que quiero probar
//
// @return: true o false dependiendo si el valor puede ir en esa posicion
static int is_possible_value(char sudoku[DIM][DIM], int row, int col, char value) {
  // check row
  for(int i = 0; i < DIM; i++) {
    if(sudoku[row][i] == value)
      return false;
  }
  // check col
  for(int j = 0; j < DIM; j++) {
    if(sudoku[j][col] == value)
      return false;
  }
  // check square
  // the first row of the square
  int first_row = (row/SQR_SIZE)*SQR_SIZE;
  // the first col of the square
  int first_col = (col/SQR_SIZE)*SQR_SIZE;
  for(int row_it = first_row; row_it < first_row + DIM/SQR_SIZE; row_it++) {
    for(int col_it = first_col; col_it < first_col + DIM/SQR_SIZE; col_it++) {
      if(row_it != row && col_it != col && sudoku[row_it][col_it] == value)
        return false;
    }
  }
  return true;
}

#define IS_LAST_ROW_LAST_COL(row, col)  ((row) == (DIM - 1) && (col) == (DIM - 1))
#define IS_LAST_ON_ROW(row, col)        ((row)  < (DIM - 1) && (col) == (DIM -1))

#define IS_BASE_CASE(sudoku, row, col)      \
    (IS_LAST_ROW_LAST_COL(row, col))?       \
        true :                              \
        (IS_LAST_ON_ROW(row, col))?         \
            solver_rec(sudoku, row+1, 0):   \
            solver_rec(sudoku, row, col+1)  \

// @param: sudoku el sudoku a resolver, donde EMPTY son los valores a remplazar
// @param: row la fila actual en la que estoy haciendo brute force
// @param: col la columna actual en la que estoy haciendo brute force
//
// @return: true si lo resolvio, false si no pudo resolverlo
static int solver_rec(char sudoku[DIM][DIM], int row, int col) {

  if(sudoku[row][col] == EMPTY) {
    for(char value = MIN_VALUE; value <= MAX_VALUE; value++) {
      if(is_possible_value(sudoku, row, col, value)) {
        sudoku[row][col] = value;
        if(IS_BASE_CASE(sudoku, row, col)) {
          return true;
        }
        sudoku[row][col] = EMPTY;
      }
    }
    return false;
  }
  return IS_BASE_CASE(sudoku, row, col);
}

// @param: sudoku el sudoku a resolver, donde EMPTY son los valores a remplazar
//
// @return: true si lo resolvio, false si no pudo resolverlo
int sudoku_solver(char sudoku[DIM][DIM]) {
  return solver_rec(sudoku, 0, 0);
}
