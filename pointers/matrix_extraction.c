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

#define ROWS 15
#define COLS 5

void extract(const char charMatrix[ROWS][COLS], char digitMatrix[ROWS][COLS], char letterMatrix[ROWS][COLS], unsigned int *digitCount, unsigned int *letterCount);
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

  char digitMatrix[ROWS][COLS];
  char letterMatrix[ROWS][COLS];
  unsigned int digitCount, letterCount;

  extract(charMatrix, digitMatrix, letterMatrix, &digitCount, &letterCount);

  printf("Total number of digits: %d, total number of letters: %d\n", digitCount, letterCount);
  printf("Digits: ");
  printMatrix(digitMatrix, digitCount);

  printf("Letters: ");
  printMatrix(letterMatrix, letterCount);

  return 0;
}

void extract(const char charMatrix[ROWS][COLS], char digitMatrix[ROWS][COLS], char letterMatrix[ROWS][COLS], unsigned int *digitCount, unsigned int *letterCount)
{
  *digitCount = 0;
  *letterCount = 0;
  for (int i = 0; i < ROWS; i++)
  {
    for (int j = 0; j < COLS; j++)
    {
      if (isdigit(charMatrix[i][j]))
      {
        assignAndIncrement(digitMatrix, digitCount, charMatrix[i][j]);
      }
      else if (isalpha(charMatrix[i][j]))
      {
        assignAndIncrement(letterMatrix, letterCount, charMatrix[i][j]);
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