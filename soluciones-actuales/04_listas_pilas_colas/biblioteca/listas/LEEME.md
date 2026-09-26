# Biblioteca de listas simplemente enlazadas

Implementación de estudio con `struct`, punteros, `new` y `delete`, sin plantillas ni contenedores STL. Cada lista mantiene `inicio`, `fin` y `longitud`.

- [Estructuras.h](Estructuras.h): define `Elemento` (inicialmente `int`), `Nodo` y `Lista`.
- [FuncionesLista.h](FuncionesLista.h): declaraciones y condiciones de uso.
- [FuncionesLista.cpp](FuncionesLista.cpp): implementación de las operaciones.
- [Ejemplo completo](../../ejemplos/uso_lista.cpp).

## Compilar y usar

Desde la carpeta `04_listas_pilas_colas`:

```sh
clang++ -std=c++17 -Wall -Wextra -Wpedantic ejemplos/uso_lista.cpp biblioteca/listas/FuncionesLista.cpp -o /tmp/uso_lista
/tmp/uso_lista
```

En tu programa incluye `FuncionesLista.h`, crea una `listas::Lista` y llama a las funciones del espacio de nombres `listas`. Agrega también `FuncionesLista.cpp` a la compilación o a los archivos fuente del proyecto de CLion/NetBeans.

```cpp
#include "FuncionesLista.h"

int main() {
    listas::Lista numeros; // Nace vacía.
    listas::insertarFinal(numeros, 10);
    listas::insertarFinal(numeros, 20);
    listas::imprimir(numeros); // 10 -> 20 -> nullptr
    listas::destruir(numeros);
}
```

## Operaciones

Las posiciones empiezan en **0**. `n` representa la cantidad de nodos.

| Función | Resultado | Costo |
| --- | --- | --- |
| `inicializar(lista)` | Establece una lista vacía; usar solo al crearla o después de destruirla. | O(1) |
| `esListaVacia(lista)`, `longitud(lista)` | Consultan si está vacía y su cantidad de nodos. | O(1) |
| `insertarInicio(lista, dato)`, `insertarFinal(lista, dato)` | Crean e insertan un nodo. | O(1) |
| `insertarEnPosicion(lista, posicion, dato)` | Inserta entre 0 y `longitud`, inclusive; devuelve `false` si la posición es inválida. | O(n) |
| `buscar(lista, dato)` | Retorna la primera coincidencia, o `nullptr`. | O(n) |
| `obtenerEnPosicion(lista, posicion)` | Retorna el nodo de esa posición, o `nullptr`. | O(n) |
| `extraerInicio(lista)` | Desconecta el primer nodo sin borrarlo, o retorna `nullptr`. | O(1) |
| `extraerEnPosicion(lista, posicion)` | Desconecta el nodo indicado sin borrarlo, o retorna `nullptr`. | O(n) |
| `insertarNodoInicio(lista, nodo)`, `insertarNodoFinal(lista, nodo)` | Insertan un nodo ya extraído, sin reservar memoria. | O(1) |
| `eliminarInicio(lista)` | Borra el primer nodo; devuelve si se eliminó. | O(1) |
| `eliminarFinal(lista)`, `eliminarEnPosicion(lista, posicion)` | Borran el nodo indicado; devuelven si se eliminó. | O(n) |
| `eliminarDato(lista, dato)` | Borra solo la primera coincidencia. | O(n) |
| `concatenar(destino, origen)` | Transfiere los nodos al final de destino y deja origen vacía. | O(1) |
| `invertir(lista)` | Invierte el orden usando los mismos nodos. | O(n) |
| `imprimir(lista)` | Muestra los datos; admite un `std::ostream` como segundo argumento. | O(n) |
| `destruir(lista)` | Libera todos los nodos y restablece los extremos y la longitud. | O(n) |

## Manejo de memoria

**Extraer** entrega un nodo aislado con `sig == nullptr`: debes reinsertarlo o hacer `delete`. **Eliminar** libera el nodo directamente. Solo pasa a `insertarNodoInicio` y `insertarNodoFinal` nodos extraídos o recién creados; un nodo no puede pertenecer a dos listas. Ambas funciones aceptan `nullptr` sin cambiar la lista.

Pasa las listas por referencia (`Lista &` o `const Lista &`). Una asignación como `otra = lista` copia los punteros y deja dos estructuras apuntando a los mismos nodos. Usa `concatenar` para transferir nodos. Concatenar una lista consigo misma no la modifica.

Las consultas retornan `const Nodo *`. Esas referencias dejan de ser válidas al borrar el nodo o destruir su lista. Para vaciar una lista con datos llama a `destruir`, no a `inicializar`. Es válido destruir una lista vacía varias veces.

## Adaptar a cartas, cuadrigas u otros datos

Esta biblioteca empieza con enteros para practicar las operaciones. Para usarla en otro ejercicio, copia la carpeta `listas` a ese proyecto, define tu estructura y cambia `using Elemento = int` en `Estructuras.h` por el tipo de dato correspondiente. Adapta también la comparación de `buscar` y `eliminarDato`, y los campos que muestra `imprimir`.

Las soluciones de esta carpeta se compilan por separado y conservan las estructuras y firmas de sus enunciados. En particular, cuadrigas se reordena solo con punteros auxiliares y barajado reutiliza los mismos nodos. Las funciones de la biblioteca sirven como base para ejercicios nuevos; revisa qué operaciones y metadatos permite cada enunciado.

[Volver al índice](../../LEEME.md)
