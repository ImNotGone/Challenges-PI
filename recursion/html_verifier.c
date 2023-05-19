/*
HTML es un lenguaje de marcado que se utiliza para el desarrollo de paginas de internet.
Un archivo .html tendria algo como esto:
<html>
    <head>
        <title>Titulo de la pagina</title>
    </head>
    <body>
        <h1>Mi pagina</h1>
        <p>Esta es mi pagina</p>
    </body>
</html>

En este caso vamos a desestimar la posibilidad de tener string dentro de los tags e inclusive
la posibilidad que un tag tenga multiples tags hijos, entonces el ejemplo previo quedaria como:
<html>
  <head>
    <title/>
  </head>
</html>

Notar como la apertura de un tag es con <, el nombre del tag en el medio y al final >.
Para cerrar dicho tag se añade un / antes del nombre del tag. Ademas, los tags que solamente
son de apertura se pueden cerrar en la misma linea, como el tag <title/> del ejemplo anterior 
(en cuyo caso el formato es <, nombre del tag, / y >, y NO aparece el nombre nuevamente).

Se pide implementar una funcion html_verifier() que reciba un string que representa un archivo .html y devuelva
1 si el archivo es valido y 0 en caso contrario. Un archivo es valido si:
- Todos los tags de apertura tienen su correspondiente tag de cierre.
- Los tags de apertura y cierre estan balanceados, es decir, si se abre un tag <head> y luego
  un tag <body>, el tag <body> se cierra antes que el tag </head>.

Prototipo:
int html_verifier(const char* html);

Ejemplos:
- Input: "<html><head><title/></head></html>"
  Output: 1

- Input: "<html><head><title/></head>"
  Output: 0

- Input: "<html><body></html>"
  Output: 0

- Input: "<html><body><p>"
  Output: 0
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define REACHED_END 1
#define INVALID 0

static int html_verifier_rec(char **html) {
    if (html[0] == '\0') {
        return REACHED_END;
    }

    // salteo el caracter <
    (*html)++;

    // guardo el inicio del tag donde estoy parado
    char *tag_start = *html;

    // itero contando el largo del tag entre < y >
    unsigned int tag_len = 0;
    char is_end_tag = 0;
    while (tag_start[tag_len] != '>') {
        if (tag_start[tag_len] == '/') {
            is_end_tag = 1;
        }
        tag_len++;
    }
    // mueve el puntero al final del tag asi continua iterando (recordar que hay que saltear el >)
    *html += tag_len + 1;

    printf("moved: %s\n", *html);

    // si es un tag de cierre, llegue al tag del medio
    if (is_end_tag) {
        return REACHED_END;
    }

    // guardo el nombre del tag
    char *tag_name = calloc(tag_len + 1, sizeof(char));
    strncpy(tag_name, tag_start, tag_len);

    printf("tag_name: %s\n", tag_name);


    // si no es un tag de cierre, busco el tag de cierre
    int value = html_verifier_rec(html);
    printf("remaining: %s\n", *html);

    // si es invalido, ni me gasto en seguir
    if (value == INVALID) {
        free(tag_name);
        return INVALID;
    }

    // al volver de la recursion, ver si se llego al final o no
    if (**html == '\0') {
        free(tag_name);
        return INVALID;
    }

    // ver si el tag de cierre es el correcto -> OJO! puede que sea mas corto que el tag de apertura y pisar memoria invalida
    *html += 2; // salteo </
    if (strncmp(*html, tag_name, tag_len) != 0) {
        free(tag_name);
        return INVALID;
    }

    free(tag_name);

    // salteo el tag + >
    *html += tag_len + 1;

    return value;
}

int html_verifier(const char *html) {
    char *html_copy = calloc(strlen(html) + 1, sizeof(char));
    strcpy(html_copy, html);

    int value = html_verifier_rec(&html_copy);

    free(html_copy);

    return value;
}

int main() {
    printf("%d\n", html_verifier("<html><head><title/></head></html>"));
    printf("%d\n", html_verifier("<html><head><title/></head>"));
    printf("%d\n", html_verifier("<html><body></html>"));
    printf("%d\n", html_verifier("<html><body><p>"));
    // printf("%d\n", html_verifier("<html><head><title/></head><body></body></html>"));
    // printf("%d\n", html_verifier("<html><head><title/></head><body><h1></h1></body></html>"));
    // printf("%d\n", html_verifier("<html><head><title/></head><body><h1></h1></body></html>"));
    // printf("%d\n", html_verifier("<html><head><title/></head><body><h1></h1></body></html>"));
    // printf("%d\n", html_verifier("<html><head><title/></head><body><h1></h1></body></html>"));
    // printf("%d\n", html_verifier("<html><head><title/></head><body><h1></h1></body></html>"));
    // printf("%d\n", html_verifier("<html><head><title/></head><body><h1></h1></body></html>"));
    // printf("%d\n", html_verifier("<html><head><title/></head><body><h1></h1></body></html>"));
    // printf("%d\n", html_verifier("<html><head><title/></head><body><h1></h1></body></html>"));
    // printf("%d\n", html_verifier("<html><head><title/></head><body><h1></h1></body></html>"));

    return 0;
}