# Preparar la clase de listas y pilas

[Abrir el curso en VS Code](../../algoritmia.code-workspace) · [Índice del tema](LEEME.md) · [Práctica del alumno](practica/LEEME.md)

## Abrir y ejecutar

En VS Code, usa **Archivo → Abrir área de trabajo desde archivo** y elige `algoritmia.code-workspace` en la carpeta superior. Así se ven también recursión, divide y vencerás y los demás laboratorios anteriores.

Abre el archivo `.cpp` que quieres ejecutar y guárdalo antes de compilar:

- **Cmd+Shift+B** compila el archivo activo como C++17.
- **Terminal → Ejecutar tarea → Ejecutar C++: archivo activo** compila y ejecuta un programa independiente.
- Para `ejemplos/uso_lista.cpp`, `ejemplos/torres_de_hanoi.cpp` o la solución principal de Bad Sunny, usa **Ejecutar C++: con biblioteca de listas y pilas**. Esta tarea enlaza las dos bibliotecas necesarias.
- Las tareas **Verificar listas y pilas** y **Verificar ROBOTJARDIN** ejecutan las pruebas existentes.

Cada ejercicio tiene su propio `main`: se compilan por separado. Los ejecutables se guardan en `.build/` de la carpeta del curso, oculta en el explorador. El programa se ejecuta desde la carpeta de su fuente, para poder leer sus archivos de datos relativos. La configuración usa `g++` disponible en Mac o Linux; las pruebas de ROBOTJARDIN también requieren Node.js.

## Orden para enseñar

| Paso | Qué trabajar | Material |
| --- | --- | --- |
| 1 | Dibujar un nodo, su dato y su puntero; reconocer cabeza, lista vacía y `nullptr`. | [Biblioteca de listas](biblioteca/listas/LEEME.md) |
| 2 | Insertar al inicio y al final, recorrer, buscar, eliminar y liberar memoria. Trazar los punteros antes de ejecutar. | [Ejemplo de lista](ejemplos/uso_lista.cpp) y [práctica de listas](practica/01-listas/LEEME.md) |
| 3 | Comprender LIFO: apilar 10, 20 y 30; desapilar 30, 20 y 10; manejar la pila vacía. | [Biblioteca de pilas](biblioteca/pilas/LEEME.md) y [práctica de pilas](practica/02-pilas/LEEME.md) |
| 4 | Aplicar operaciones a un problema pequeño de listas. | [Cuadrigas, Lab. 2 de 2025-1, P1](../../laboratorios/laboratorio-02/2025-1/enunciado.pdf) |
| 5 | Practicar traslado de nodos y fusión de listas con las restricciones del enunciado. | [Kupa y fusión de listas, Lab. 3 de 2023-1](../../laboratorios/laboratorio-03/2023-1/enunciado.pdf) |
| 6 | Profundizar en pilas una vez dominadas las operaciones básicas. | [Nautilus, Ex. 1 de 2024-1, P2: enunciado y solución con pila propia](enunciados/nautilus.md) y [Bad Sunny, Ex. 1 de 2022-2, P2](../../examenes/parcial/2022-2/enunciado.pdf) |

La biblioteca de pilas reutiliza la lista y sitúa la cima en su inicio. El [ejemplo independiente de Bad Sunny](ejemplos/bad_sunny_pila_simple.cpp) contiene su propia pila enlazada y se compila con la tarea de archivo activo. Bad Sunny introduce una pila monótona y el área de un histograma; conviene dejarlo para después de la introducción.

## Usar el material en clase

El alumno trabaja en `practica/01-listas/` y `practica/02-pilas/`. Cada carpeta incluye un `main.cpp` inicial y ejercicios con resultados que puede comprobar.

`biblioteca/` reúne las operaciones de referencia; `ejemplos/` muestra su uso; `soluciones/` conserva las resoluciones del profesor; `enunciados/` reúne los PDF y accesos al catálogo.
