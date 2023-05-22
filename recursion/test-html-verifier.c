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
#include <assert.h>

#define REACHED_END 1
#define INVALID 0
#define MAX_TAG_NAME_LEN 20

char html_verifier(const char *html);

int main()
{
    assert(1 == html_verifier("<html><head><title/></head></html>"));
    assert(0 == html_verifier("<html><head><title/></head>"));
    assert(0 == html_verifier("<html><body></html>"));
    assert(0 == html_verifier("<html><body><p>"));
    assert(0 == html_verifier("<html><body/><p>"));
    assert(1 == html_verifier("<html><body><p><title/></p></body></html>"));

    puts("OK!");
    return 0;
}
