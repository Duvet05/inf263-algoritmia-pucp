# Biblioteca de pilas

Pila enlazada construida sobre la [biblioteca de listas](../listas/LEEME.md). La **cima es el inicio de la lista**, así que apilar y desapilar cuestan O(1) y no se recorre nada.

- [FuncionesPila.h](FuncionesPila.h): `pilas::Pila` y declaraciones.
- [FuncionesPila.cpp](FuncionesPila.cpp): implementación con las funciones de `listas`.
- Ejemplos que la usan: [Torres de Hanói](../../ejemplos/torres_de_hanoi.cpp) y [Bad Sunny](../../soluciones/2022_2_ex01_p02_bad_sunny.cpp).

## Compilar

Agrega las dos implementaciones, la de pilas y la de listas:

```sh
clang++ -std=c++17 -Wall -Wextra -Wpedantic tu_programa.cpp biblioteca/pilas/FuncionesPila.cpp biblioteca/listas/FuncionesLista.cpp -o /tmp/programa
```

## Operaciones

| Función | Resultado | Costo |
| --- | --- | --- |
| `inicializar(pila)` | Pila vacía; usar solo al crearla o después de destruirla. | O(1) |
| `esPilaVacia(pila)`, `altura(pila)` | Consultan si está vacía y cuántos elementos tiene. | O(1) |
| `apilar(pila, dato)` | Crea un nodo en la cima. | O(1) |
| `desapilar(pila, dato)` | Copia la cima en `dato` y libera el nodo; `false` si estaba vacía. | O(1) |
| `cima(pila)` | Puntero al dato de la cima sin quitarlo, o `nullptr`. | O(1) |
| `desapilarNodo(pila)`, `apilarNodo(pila, nodo)` | Mueven un nodo entre pilas sin `new` ni `delete`. | O(1) |
| `imprimir(pila)` | Muestra los datos desde la base hasta la cima. | O(n) |
| `destruir(pila)` | Libera todos los nodos. | O(n) |

El tipo de dato es `listas::Elemento` (inicialmente `int`). Para otro ejercicio, cámbialo en `../listas/Estructuras.h`.

[Volver al índice](../../LEEME.md)
