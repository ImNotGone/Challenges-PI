#include <stdio.h>
#include <ctype.h>
#include <assert.h>

/*
Dada una matriz de caracteres de 15 filas y 5 columnas, escribir una funcion extract() que
extraiga los caracteres alfabeticos y los numericos en dos matrices separadas.
La funcion no debe devolver nada en su nombre pero debe devolver el numero de
caracteres alfabeticos y numericos extraidos.

Consideraciones:
- La matriz de caracteres de entrada puede contener cualquier caracter ASCII.
- No se debe modificar la matriz de entrada.
- Modularizar el codigo evitando la repeticion del mismo.

[OPCIONAL] Challenges extra:
- La funcion extract() puede declarar como maximo 2 variables.
- La funcion extract() puede tener como maximo 8 lineas (sin contar {} y habiendo modularizado)
*/

#define ROWS 15
#define COLS 5

// @brief separa char_matrix en digit_matrix y letter_matrix, devolviendo ademas digit_count y letter_count
// @param char_matrix la matriz de caracteres a procesar
// @param digit_matrix la matriz de salida donde se guardaran los digitos
// @param letter_matrix la matriz de salida donde se guardaran las letras
// @param digit_count parametro de salida donde se guardara la cantidad de digitos
// @param letter_count parametro de salida donde se guardara la cantidad de letras
// @return void
void extract(const char char_matrix[ROWS][COLS], char digit_matrix[ROWS][COLS], char letter_matrix[ROWS][COLS], unsigned int *digit_count, unsigned int *letter_count);

int main(void)
{
  char charMatrix[ROWS][COLS] = {
      {'a', 'b', 'c', 'd', 'e'},
      {'f', 'g', 'h', 'i', 'j'},
      {'k', 'l', 'm', 'n', 'o'},
      {'p', 'q', 'r', 's', 't'},
      {'u', 'v', 'w', 'x', 'y'},
      {'z', '1', '2', '3', '4'},
      {'5', '6', '7', '8', '9'},
      {'0', '!', '@', '#', '$'},
      {'%', '^', '&', '*', '('},
      {')', '_', '+', '=', '{'},
      {'}', '[', ']', '|', '\\'},
      {'\'', '\"', ';', ':', '<'},
      {'>', '?', '/', '~', '`'},
      {' ', '\t', '\r', '\v', '\f'},
      {'\n', '\0', '\a', '\b', '\e'}};

  char digit_matrix_expected[ROWS][COLS] = {
      {'1', '2', '3', '4', '5'},
      {'6', '7', '8', '9', '0'}};

  char letter_matrix_expected[ROWS][COLS] = {
      {'a', 'b', 'c', 'd', 'e'},
      {'f', 'g', 'h', 'i', 'j'},
      {'k', 'l', 'm', 'n', 'o'},
      {'p', 'q', 'r', 's', 't'},
      {'u', 'v', 'w', 'x', 'y'},
      {'z'}};

  unsigned int digit_count_expected = 10, letter_count_expected = 26;

  char digit_matrix_actual[ROWS][COLS];
  char letter_matrix_actual[ROWS][COLS];
  unsigned int digit_count_actual, letter_count_actual;

  extract(charMatrix, digit_matrix_actual, letter_matrix_actual, &digit_count_actual, &letter_count_actual);

  assert(digit_count_actual == digit_count_expected);
  assert(letter_count_actual == letter_count_expected);

  for (int i = 0; i < digit_count_expected; i++) {
    // assert(digit_matrix_actual[0][i] == digit_matrix_expected[0][i]);
    assert(digit_matrix_actual[i / COLS][i % COLS] == digit_matrix_expected[i / COLS][i % COLS]);
  }

  for (int i = 0; i < letter_count_expected; i++) {
    // assert(letter_matrix_actual[0][i] == letter_matrix_expected[0][i]);
    assert(letter_matrix_actual[i / COLS][i % COLS] == letter_matrix_expected[i / COLS][i % COLS]);
  }

  puts("OK!");

  return 0;
}

void extract(const char char_matrix[ROWS][COLS], char digit_matrix[ROWS][COLS], char letter_matrix[ROWS][COLS], unsigned int *digit_count, unsigned int *letter_count)
{
    return;
}
