# Incidentes de seguridad: pilas y cola

Pregunta 2 del [Examen 1 de 2023-2](../../../examenes/parcial/2023-2/enunciado.pdf), páginas 3 a 5.

[Solución completa en C++](../soluciones/2023_2_ex01_p02_incidentes.cpp). Usa pilas y cola enlazadas propias, sin bibliotecas de contenedores.

## Qué significa un código

En `206`, el `2` indica impacto alto y el `06` indica que fue el incidente número 6. El impacto `1` significa muy alto. Para ordenar por llegada se compara `codigo % 100`, no el código completo.

La cola atiende primero al más antiguo. Los incidentes que están en las pilas llegaron antes que los de la cola. Hay que darles lugar y dejar esperando a los más recientes.

## El caso del examen

La cola se lee del inicio al final. Las pilas se leen de la cima a la base.

| Momento | Cola (capacidad 8) | Pila 1 | Pila 2 |
| --- | --- | --- | --- |
| Inicial | 206 107 208 109 210 211 112 113 | 105 102 101 | 204 203 |
| Después de `reinicia_cola` | 101 102 203 204 105 206 107 208 | Vacía | 113 112 211 210 109 |
| Después de `reclasifica_pilas` | 101 102 203 204 105 206 107 208 | 210 211 | 109 112 113 |

## a) Reiniciar la cola

1. Pasar los nodos de la pila 2 a la pila 1.
2. Ordenar la pila 1 por llegada, usando la pila 2 como apoyo. Su cima queda en `101`.
3. Conservar los tres incidentes más antiguos de la cola: `206 107 208`. Rotarlos al final permite sacar los otros cinco y apilarlos en la pila 2.
4. Encolar los cinco incidentes antiguos de la pila 1: `101 102 203 204 105`.
5. Rotar otra vez los tres conservados: quedan detrás de los que acaban de entrar.

Las operaciones `desapilarNodo` y `desencolarNodo` extraen un nodo sin destruirlo; `apilarNodo` y `encolarNodo` lo colocan en otra estructura. Así se conservan tanto su dirección como su código.

Esta parte utiliza únicamente las dos pilas y la cola originales, más variables escalares y punteros. No reserva nodos, crea otra estructura ni usa recursión. Ordenar los `k` incidentes de las pilas cuesta O(k²); los traslados son lineales. También contempla espacio libre y capacidad insuficiente para todos los incidentes antiguos, bajo las mismas precondiciones de llegada.

## b) Reclasificar las pilas

Con la pila 1 vacía después del reinicio:

1. Pasar toda la pila 2 a una cola temporal, la única estructura auxiliar permitida.
2. Desencolar uno por uno: los códigos `2xx` van a la pila 1 y los `1xx` a la pila 2.

Al apilar, el orden se invierte y el más antiguo de cada impacto queda en la cima. La cola de atención no cambia. Esta parte cuesta O(s), para `s` incidentes sobrantes, y reutiliza todos sus nodos.

## Diferencias dentro del PDF

La solución sigue los nombres de la **salida de consola de la página 5**:

- En el paso azul, el texto menciona apilar los retirados en la pila 1, pero el dibujo y la salida del reinicio los colocan en la pila 2. La pila 1 todavía contiene los incidentes que deben ingresar.
- El dibujo final asigna `1xx` a la pila 1 y `2xx` a la pila 2; la consola muestra lo contrario. Aquí la pila 1 termina con `210 211` y la pila 2 con `109 112 113`.

Es una diferencia de etiquetas en el material. Si en clase se elige seguir el dibujo final, se intercambian los destinos de `reclasifica_pilas`.

## Ejecutar y comprobar

Desde `04_listas_pilas_colas`:

```sh
clang++ -std=c++17 -Wall -Wextra -Wpedantic soluciones/2023_2_ex01_p02_incidentes.cpp -o /tmp/incidentes
/tmp/incidentes
python3 tests/test_listas.py
```

El programa carga el ejemplo del PDF y muestra los tres estados de la tabla. Las pruebas comparan 150 escenarios con un ordenamiento independiente y comprueban que ningún nodo se pierda, se duplique o cambie de código.
