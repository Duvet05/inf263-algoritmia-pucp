# Listas simplemente enlazadas

Trabaja en [main.cpp](main.cpp). Comienza con una estructura `Nodo` que tenga un entero y un puntero al siguiente nodo.

1. Construye una lista vacía e imprime `nullptr`.
2. Inserta 20 al final, 10 al inicio y 30 al final. Resultado: `10 -> 20 -> 30 -> nullptr`.
3. Busca 20 y luego 99. La segunda búsqueda debe indicar que no existe.
4. Elimina 20. Resultado: `10 -> 30 -> nullptr`.
5. Elimina la cabeza, elimina el último nodo y vuelve a intentar eliminar de la lista vacía.
6. Libera los nodos restantes sin acceder a memoria ya liberada.

Implementa primero las operaciones con punteros. Después compara tu trabajo con la [biblioteca de referencia](../../biblioteca/listas/LEEME.md) y el [ejemplo de uso](../../ejemplos/uso_lista.cpp).

Abre y guarda `main.cpp`, y ejecuta la tarea **Ejecutar C++: archivo activo**.
