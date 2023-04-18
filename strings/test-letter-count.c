/*
Dado un array de palabras, escribir la funcion letter_count() que debe
contar la cantidad de veces que aparece cada letra en todas las palabras,
distinguindo ntre mayúsculas y minúsculas, y devolver dicho resultado en una matriz
M de 52*2 elementos, donde M[i][0] es la i-ava letra y M[i][1] es la cantidad de veces
que aparece la i-ava letras. A su vez, la funcion debe devolver cual es la letra que mas
apariciones tiene en el array de palabras, contando minusculas y mayusculas. En caso de
empate, se debe devolver la letra que aparece ultima en el abecedario. En caso que no
aparezca ninguna letra, se debe devolver el caracter ' ' (espacio en blanco).

Consideraciones:
- Se garantiza que todas las palabras tienen como máximo N caracteres.
- No es necesario que el array de salida M este ordenado.
- No usar funciones de la biblioteca standard (ctype, etc).
- Las palabras pueden tener caracteres que no necesariamente son letras.
- Utilizar la menor cantidad de for's posibles ()

[OPCIONAL] Consideraciones extra:
- Definir una constante (NO magic number) para indicar la cantidad de filas de la matriz M.
- Utilizar la menor cantidad de for's posibles (la solucion usa 4 pero en 3 se podria hacer).

Ejemplo:
- Input: ["Hola", "Mundo", "Hola", "Mundo"]
  Output: M = [[a, 2][b, 0][c, 0][d, 2][e, 0][f, 0][g, 0][h, 0][i, 0][j, 0][k, 0][l, 2][m, 0][n, 2][o, 4][p, 0][q, 0][r, 0][s, 0][t, 0][u, 2][v, 0][w, 0][x, 0][y, 0][z, 0][A, 0][B, 0][C, 0][D, 0][E, 0][F, 0][G, 0][H, 2][I, 0][J, 0][K, 0][L, 0][M, 2][N, 0][O, 0][P, 0][Q, 0][R, 0][S, 0][T, 0][U, 0][V, 0][W, 0][X, 0][Y, 0][Z, 0]],
          max_upper = 'M', max_lower = 'o'

- Input: ["hola", "esto", "es", "un", "ejemplo"]
  Output: M = [[a, 1][b, 0][c, 0][d, 0][e, 4][f, 0][g, 0][h, 1][i, 0][j, 1][k, 0][l, 2][m, 1][n, 1][o, 3][p, 1][q, 0][r, 0][s, 2][t, 1][u, 1][v, 0][w, 0][x, 0][y, 0][z, 0][A, 0][B, 0][C, 0][D, 0][E, 0][F, 0][G, 0][H, 0][I, 0][J, 0][K, 0][L, 0][M, 0][N, 0][O, 0][P, 0][Q, 0][R, 0][S, 0][T, 0][U, 0][V, 0][W, 0][X, 0][Y, 0][Z, 0]]
          max_upper = ' ', max_lower = 'e'

- Input: ["hola!!!", "qu3", "bu4n05", "l45", "ch4113ng35"]
  Output: M = [[a, 1][b, 1][c, 1][d, 0][e, 0][f, 0][g, 1][h, 2][i, 0][j, 0][k, 0][l, 2][m, 0][n, 2][o, 1][p, 0][q, 1][r, 0][s, 0][t, 0][u, 2][v, 0][w, 0][x, 0][y, 0][z, 0][A, 0][B, 0][C, 0][D, 0][E, 0][F, 0][G, 0][H, 0][I, 0][J, 0][K, 0][L, 0][M, 0][N, 0][O, 0][P, 0][Q, 0][R, 0][S, 0][T, 0][U, 0][V, 0][W, 0][X, 0][Y, 0][Z, 0]]
          max_upper = ' ', max_lower = 'u'
*/

#include <stdio.h>
#include <assert.h>

#define N 10

/* las siguientes variables NO se incluyen en el tester */
#define LETTERS 'z' - 'a' + 1
#define TOTAL_LETTERS (LETTERS) * 2
#define IS_UPPERCASE(letter) ('A' <= (letter) && (letter) <= 'Z')
#define IS_LOWERCASE(letter) ('a' <= (letter) && (letter) <= 'z')

void letter_count(const char words[][N], unsigned int word_count, char M[TOTAL_LETTERS][2], char *max_upper, char *max_lower);

int main()
{
    char words[][N] = {"Hola", "Mundo", "Hola", "Mundo"};
    char mat[TOTAL_LETTERS][2];
    char max_upper, max_lower;
    unsigned int word_count = 4;
    letter_count(words, word_count, mat, &max_upper, &max_lower);

    assert(max_upper == 'M');
    assert(max_lower == 'o');

    char expected[TOTAL_LETTERS][2] = {
        {'a', 2},{'b', 0},{'c', 0},{'d', 2},{'e', 0},{'f', 0},{'g', 0},{'h', 0},
        {'i', 0},{'j', 0},{'k', 0},{'l', 2},{'m', 0},{'n', 2},{'o', 4},{'p', 0},
        {'q', 0},{'r', 0},{'s', 0},{'t', 0},{'u', 2},{'v', 0},{'w', 0},{'x', 0},
        {'y', 0},{'z', 0},{'A', 0},{'B', 0},{'C', 0},{'D', 0},{'E', 0},{'F', 0},
        {'G', 0},{'H', 2},{'I', 0},{'J', 0},{'K', 0},{'L', 0},{'M', 2},{'N', 0},
        {'O', 0},{'P', 0},{'Q', 0},{'R', 0},{'S', 0},{'T', 0},{'U', 0},{'V', 0},
        {'W', 0},{'X', 0},{'Y', 0},{'Z', 0},
    };

    for(int i = 0; i < TOTAL_LETTERS; i++) {
        assert(mat[i][0] == expected[i][0]);
        assert(mat[i][1] == expected[i][1]);
    }

    char words0[][N] = {"hola", "esto", "es", "un", "ejemplo"};
    word_count = 5;
    letter_count(words0, word_count, mat, &max_upper, &max_lower);

    assert(max_upper == ' ');
    assert(max_lower == 'e');

    char expected0[TOTAL_LETTERS][2] = {
        {'a', 1},{'b', 0},{'c', 0},{'d', 0},{'e', 4},{'f', 0},{'g', 0},{'h', 1},
        {'i', 0},{'j', 1},{'k', 0},{'l', 2},{'m', 1},{'n', 1},{'o', 3},{'p', 1},
        {'q', 0},{'r', 0},{'s', 2},{'t', 1},{'u', 1},{'v', 0},{'w', 0},{'x', 0},
        {'y', 0},{'z', 0},{'A', 0},{'B', 0},{'C', 0},{'D', 0},{'E', 0},{'F', 0},
        {'G', 0},{'H', 0},{'I', 0},{'J', 0},{'K', 0},{'L', 0},{'M', 0},{'N', 0},
        {'O', 0},{'P', 0},{'Q', 0},{'R', 0},{'S', 0},{'T', 0},{'U', 0},{'V', 0},
        {'W', 0},{'X', 0},{'Y', 0},{'Z', 0}
    };

    for(int i = 0; i < TOTAL_LETTERS; i++) {
        assert(mat[i][0] == expected0[i][0]);
        assert(mat[i][1] == expected0[i][1]);
    }

    char words1[][N] = {"hola!!!", "qu3", "bu4n05", "l45", "ch4113ng35"};
    word_count = 5;
    letter_count(words1, word_count, mat, &max_upper, &max_lower);

    char expected1[TOTAL_LETTERS][2] = {
        {'a', 1},{'b', 1},{'c', 1},{'d', 0},{'e', 0},{'f', 0},{'g', 1},{'h', 2},
        {'i', 0},{'j', 0},{'k', 0},{'l', 2},{'m', 0},{'n', 2},{'o', 1},{'p', 0},
        {'q', 1},{'r', 0},{'s', 0},{'t', 0},{'u', 2},{'v', 0},{'w', 0},{'x', 0},
        {'y', 0},{'z', 0},{'A', 0},{'B', 0},{'C', 0},{'D', 0},{'E', 0},{'F', 0},
        {'G', 0},{'H', 0},{'I', 0},{'J', 0},{'K', 0},{'L', 0},{'M', 0},{'N', 0},
        {'O', 0},{'P', 0},{'Q', 0},{'R', 0},{'S', 0},{'T', 0},{'U', 0},{'V', 0},
        {'W', 0},{'X', 0},{'Y', 0},{'Z', 0}
    };

    for(int i = 0; i < TOTAL_LETTERS; i++) {
        assert(mat[i][0] == expected1[i][0]);
        assert(mat[i][1] == expected1[i][1]);
    }

    assert(max_upper == ' ');
    assert(max_lower == 'u');

    puts("OK!");
    return 0;
}

void letter_count(const char words[][N], unsigned int word_count, char M[TOTAL_LETTERS][2], char *max_upper, char *max_lower)
{
    return;
}
