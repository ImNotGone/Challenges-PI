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

#include <stdio.h>
#include <ctype.h>
#include <assert.h>

#define ROWS 15
#define COLS 5

void extract(const char char_matrix[ROWS][COLS], char digit_matrix[ROWS][COLS], char letter_matrix[ROWS][COLS], unsigned int *digit_count, unsigned int *letter_count);
void assignAndIncrement(char matrix[ROWS][COLS], unsigned int *count, char value);
void printMatrix(const char matrix[ROWS][COLS], unsigned int count);

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

  /*
  printf("Total number of digits: %d, total number of letters: %d\n", digit_count_actual, letter_count_actual);
  printf("Digits: ");
  printMatrix(digit_matrix_actual, digit_count_actual);

  printf("Letters: ");
  printMatrix(letter_matrix_actual, letter_count_actual);
  */
  return 0;
}

void extract(const char char_matrix[ROWS][COLS], char digit_matrix[ROWS][COLS], char letter_matrix[ROWS][COLS], unsigned int *digit_count, unsigned int *letter_count)
{
  *digit_count = 0;
  *letter_count = 0;
  for (int i = 0; i < ROWS; i++)
  {
    for (int j = 0; j < COLS; j++)
    {
      if (isdigit(char_matrix[i][j]))
      {
        assignAndIncrement(digit_matrix, digit_count, char_matrix[i][j]);
      }
      else if (isalpha(char_matrix[i][j]))
      {
        assignAndIncrement(letter_matrix, letter_count, char_matrix[i][j]);
      }
    }
  }
}

void assignAndIncrement(char matrix[ROWS][COLS], unsigned int *count, char value)
{
  matrix[*count / COLS][*count % COLS] = value;
  (*count)++;
}

void printMatrix(const char matrix[ROWS][COLS], unsigned int count)
{
  for (int i = 0; i < count; i++)
  {
    printf("%c ", matrix[i / COLS][i % COLS]);
  }
  printf("\n");
}
