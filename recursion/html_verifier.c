/*
#################################################
    NIVEL DE DIFICULTAD (con las consideraciones extra): 10/10 - Es mas dificil que cualquier ejercicio de parcial [VERIFICADO]
#################################################

HTML es un lenguaje de etiquetado que se utiliza para el desarrollo de paginas de internet.
Un tag esta compuesto por un nombre encerrado entre < y >. Por ejemplo, <html> es un tag y
se considera de apertura. El tag </html> es un tag de cierre. Ademas, existen tags que no tienen
apertura ni cierre, como <title/>, que directamente se considera que esta cerrado. Por ultimo,
existen tags que tienen un nombre y un contenido, como <p>Este es el contenido</p>.

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

En este caso vamos a desestimar la posibilidad de tener strings (contenido) dentro de los tags e inclusive
la posibilidad de que un tag tenga multiples tags hijos, entonces el ejemplo previo quedaria como:
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
- Se encuentra presente un tag de solo cierre, como <title/>

Consideraciones:
- Se garantiza que el string recibido representa un archivo .html con las condiciones mencionadas,
es decir, solamente se incluyen tags pero NO se garantiza que el archivo sea valido (puede que falten
tags de cierre, que esten desbalanceados, etc).
- Se garantiza que los nombres de los tags tienen como maximo 20 caracteres.
- Se pueden utilizar funciones de la biblioteca string.h y stdlib.h.
- Se pueden utilizar funciones auxiliares.
- No reservar memoria dinamica a menos que sea necesario.
- Usar una funcion recursiva que reciba como maximo 2 parametros.

[OPCINAL] Consideraciones extra:
- La funcion recursiva recibe solamente 1 parametro. [AUMENTA MUCHO LA DIFICULTAD]
- No usar memoria dinamica.

Tips:
- Buscar el tag de solo cierre y empezar a validar desde ahi.
- Combinar recursion de tipo stack (FILO) con recursion de tipo cola (FIFO).
- Pensar en como se puede validar un tag de apertura y su correspondiente tag de cierre, ¿como puede
un llamado proximo modificar valores del actual?
- Pensar si con el prototipo mencionado alcanza para resolver el problema o si se necesita
alguna funcion extra.
- Jugar muchos con punteros y aritmetica de punteros.

Prototipo:
char html_verifier(const char* html);

Ejemplos:
- Input: "<html><head><title/></head></html>"
  Output: 1 -> el archivo es valido porque todos los tags tienen su correspondiente tag de cierre, estan balanceados y hay un tag de solo cierre.

- Input: "<html><head><title/></head>"
  Output: 0 -> el archivo no es valido porque falta el tag de cierre </html> al final

- Input: "<html><body></html>"
  Output: 0 -> el archivo no es valido porque el tag <body> deberia ser <body/>

- Input: "<html><body><p>"
  Output: 0 -> ningun tag se cierra

- Input: "<html><body/><p>"
  Output: 0 -> el tag <html> no se cierra y aparece un tag <p> de apertura luego de un tag de solo cierre

- Input: "<html><body><p><title/></p></body></html>"
  Output: 1 -> el archivo es valido porque todos los tags tienen su correspondiente tag de cierre, estan balanceados y hay un tag de solo cierre.
*/

#include <stdio.h>
#include <string.h>

#define REACHED_END 1
#define INVALID 0
#define MAX_TAG_NAME_LEN 20

static char html_verifier_rec(char **html)
{
    if (**html == '\0')
    {
        return INVALID; // nunca se llego al tag de solo cierre
    }

    (*html)++; // salteo el caracter <

    // guardo el inicio del tag donde estoy parado
    char *tag_start = *html;

    // itero contando el largo del tag entre < y >
    char tag_name[MAX_TAG_NAME_LEN + 1] = {0};
    unsigned int tag_len = 0;
    char is_end_tag = 0;
    while (tag_start[tag_len] != '>')
    {
        if (tag_start[tag_len] == '/') // es un tag de cierre
        {
            is_end_tag = 1;
        }
        else
        {
            tag_name[tag_len] = tag_start[tag_len]; // guardo el nombre del tag caracter a caracter
        }
        tag_len++;
    }

    tag_len -= is_end_tag; // porque si es un tag de cierre, no cuento el / en el largo del tag

    // mueve el puntero al final del tag asi continua iterando (recordar que hay que saltear el >)
    *html += tag_len + 1;
    *html += is_end_tag; // si es un tag de cierre, salteo el / tambien

    // si es un tag de cierre, llegue al tag del medio
    if (is_end_tag)
    {
        return REACHED_END;
    }

    // si no es un tag de cierre, busco el tag de cierre
    int value = html_verifier_rec(html);

    // si es invalido o llegue al final de la recursion, ni me gasto en seguir
    if (value == INVALID || **html == '\0')
    {
        return INVALID;
    }

    *html += 2; // salteo </

    // ver si el tag de cierre es el correcto
    char *closing_tag_start = *html;
    char closing_tag_name[MAX_TAG_NAME_LEN + 1] = {0};
    unsigned int closing_tag_len = 0;
    while (*closing_tag_start != '>')
    {
        closing_tag_name[closing_tag_len++] = *closing_tag_start; // guardamos el nombre del tag de cierre caracter a caracter
        closing_tag_start++;
    }

    if (tag_len != closing_tag_len || strncmp(tag_name, closing_tag_name, tag_len) != 0)
    {
        return INVALID; // el tag de cierre no coincide con el de apertura
    }

    // salteo el tag + >, asi queda apuntando al siguiente tag para el llamado previo
    *html += tag_len + 1;

    return value;
}

char html_verifier(const char *html)
{
    return html_verifier_rec((char **)&html);
}

int main()
{
    printf("%d\n", html_verifier("<html><head><title/></head></html>"));
    printf("%d\n", html_verifier("<html><head><title/></head>"));
    printf("%d\n", html_verifier("<html><body></html>"));
    printf("%d\n", html_verifier("<html><body><p>"));
    printf("%d\n", html_verifier("<html><body/><p>"));
    printf("%d\n", html_verifier("<html><body><p><title/></p></body></html>"));
    return 0;
}