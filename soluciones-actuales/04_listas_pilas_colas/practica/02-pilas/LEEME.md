# Pilas enlazadas

Trabaja en [main.cpp](main.cpp). Dibuja siempre cuál es la cima.

1. Construye una pila vacía y comprueba su estado.
2. Apila 10, 20 y 30. La cima debe contener 30.
3. Consulta la cima sin retirar el dato.
4. Desapila tres veces. Los resultados deben ser `30, 20, 10`.
5. Intenta desapilar de nuevo: la operación debe informar que la pila está vacía sin acceder a un puntero nulo.
6. Apila otra vez y libera todos los nodos al terminar.

Implementa primero `apilar`, `desapilar` y la consulta de pila vacía. Después compara con la [biblioteca de pilas](../../biblioteca/pilas/LEEME.md), que reutiliza las operaciones del inicio de una lista.

Como ampliación, invierte una secuencia usando una pila y explica por qué aparece el orden inverso.

Abre y guarda `main.cpp`, y ejecuta la tarea **Ejecutar C++: archivo activo**.
