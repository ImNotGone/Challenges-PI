/*
Escribir una funcion binary_compression() que dado un string s, comprima los numeros binarios
pasandolos a su representacion decimal. La funcion debe devolver la cantidad de numeros comprimidos
en su nombre. A su vez, debe devolver por parametro las posiciones de los numeros decimales resultantes de
comprimir cada numero binario (inicio y fin). En caso de no encontrar numeros binarios, la funcion debe devolver
0 y no modificar los valores de los parametros.

Consideraciones:
- Modularizar el codigo.
- No usar funciones de la biblioteca standard ni de math.h.
- Se garantiza que ningun numero decimal tiene 0s o 1s, sino solo digitos del 2 al 9, el resto es binario.
- Utilizar el tipo de dato apropiado (ej: unsigned int o size_t para variables que representan valores positivos)

[OPCIONAL] Consideraciones extra:
- No usar aritmetica modular.

Ejemplos:
- Input: s = "esto es un 1010"
  Output: 1, s = "esto es un 10"
             pos: [[9, 9]]

- Input: s = "cumplo anios el 1101 del mes 111, habiendo nacido en 11111000001"
  Output: 3, s: cumplo anios el 13 del mes 7, habiendo nacido en 1985
             pos: [[16, 17][27, 27][49, 52]]

- Input: s = "este string no tiene numeros binarios"
  Output: 0, s = "este string no tiene numeros binarios"
             pos: []

- Input: s = "001"
  Output: 1, s = "1"
             pos: [[0, 0]]

- Input: s = "1111 por 10001 es equivalente a 11111111, lo cual es 255"
  Output: 1, s = "15 por 17 es equivalente a 255, lo cual es 255"
             pos: [[0, 3]]
*/

#include <stdio.h>

static unsigned int binary_to_decimal(const char *s, unsigned int start, unsigned int end)
{
    unsigned int decimal = 0;
    char underflow = 0;
    for (unsigned int i = end, multiplier = 1; !underflow && i >= start; i--)
    {
        decimal += (s[i] - '0') * multiplier;
        multiplier <<= 1; // alternativa multiplier *= 2;
        /*
            si start == 0 e i == 0, al ejecutar i-- se produce un underflow, lo que deriva
            en una operacion llamada wraparound, que consiste en que el valor de i se vuelve
            el mayor valor posible para un unsigned int, es decir, 4294967295 (32 bits), por lo
            que i >= start nunca sera falso y el bucle nunca terminara
        */
        if (i == 0) {
            underflow = 1;
        }
    }
    return decimal;
}

static unsigned int decimal_length(unsigned int decimal)
{
    unsigned int length = 0;
    while (decimal)
    {
        decimal /= 10;
        length++;
    }
    return length;
}

static void insert_decimal(char *s, unsigned int decimal, unsigned int start, unsigned int total_digits)
{
    /* 
        obtenemos el mayor denominador para recorrer los digitos del numero de izquierda a derecha
    */
    unsigned int denominator = 1;
    for (unsigned int i = 0; i < total_digits - 1; i++)
    {
        denominator *= 10;
    }

    for (unsigned int digits = 0; digits < total_digits; digits++)
    {
        unsigned int digit = decimal / denominator;
        decimal -= digit * denominator; // alternativa decimal %= denominator;
        denominator /= 10;
        s[start + digits] = digit + '0';
    }
}

unsigned int binary_compression(char *s, unsigned int pos[][2])
{
    unsigned int count = 0, newDim = 0;
    for (unsigned int i = 0, start = -1, end; s[i]; ++i)
    {
        if (s[i] == '0' || s[i] == '1')
        {
            if (start == -1)
            {
                start = i;
            }
            end = i;
        }
        else
        {
            s[newDim++] = s[i];
        }

        /*
            comprimimos el numero binario cuando tengamos un numero binario recorrido
            y el siguiente caracter no sea un 0 ni un 1 o el siguiente caracter sea el final del string,
            de esta forma evitamos duplicar codigo y que se comprima el ultimo numero binario
        */
        if (start != -1 && ((s[i + 1] != '0' && s[i + 1] != '1') || s[i + 1] == '\0'))
        {
            unsigned int decimal = binary_to_decimal(s, start, end);
            unsigned int length = decimal_length(decimal);
            pos[count][0] = newDim;
            pos[count][1] = newDim + length - 1;
            insert_decimal(s, decimal, newDim, length);
            count++;
            start = -1;
            newDim += length;
        }
    }

    /*
        importante agregar el NULL TERMINATED para que el string sea valido
    */
    s[newDim] = '\0';

    return count;
}

int main()
{
    // char s[] = "cumplo anios el 1101 del mes 111, habiendo nacido en 11111000001";
    // char s[] = "esto es un 1010";
    // char s[] = "este string no tiene numeros binarios";
    // char s[] = "001";
    char s[] = "1111 por 10001 es equivalente a 11111111, lo cual es 255";
    unsigned int pos[64][2];
    unsigned int count = binary_compression(s, pos);
    printf("count: %d\ns: %s\npos: [", count, s);
    for (unsigned int i = 0; i < count; i++)
    {
        printf("[%d, %d]", pos[i][0], pos[i][1]);
    }
    printf("]\n");

    for (unsigned int i = 0; i < count; i++)
    {
        unsigned int start = pos[i][0], end = pos[i][1];
        printf("start: %d, end: %d, number: ", start, end);
        for (unsigned int j = start; j <= end; j++)
        {
            printf("%c", s[j]);
        }
        printf("\n");
    }
    return 0;
}