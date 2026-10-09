# Nautilus — Examen 1 de 2024-1, pregunta 2


El submarino recibe órdenes de subir (`S`) y bajar (`B`). Hay que generar una secuencia de niveles enteros positivos, sin repetirlos, que respete esas órdenes. Para `n` órdenes, los ejemplos utilizan los niveles de 1 a `n + 1`.

| Órdenes | Resultado esperado |
| --- | --- |
| `S S S B S` | `1 2 3 5 4 6` |
| `B B S` | `3 2 1 4` |
| `S B S B B S S` | `1 3 2 6 5 4 7 8` |

## Restricciones para desarrollar en clase

- Usar una sola pila.
- El arreglo de órdenes contiene la entrada; no se puede reutilizar como memoria auxiliar ni modificarlo para almacenar resultados.
- No usar otro TAD ni un arreglo adicional.
- Buscar complejidad **O(n)**: la versión descargada el 9 de octubre añade expresamente este requisito.

La comparación del texto de ambas versiones encontró como única diferencia esa indicación de complejidad. Ambas copias se conservan; la copia anterior se extrae sin avisos y la descarga reciente informa un error de bloque comprimido.

## Solución con una pila enlazada propia

[2024_1_ex01_p02_nautilus.cpp](../soluciones/2024_1_ex01_p02_nautilus.cpp) reúne `Nodo`, `Pila`, las operaciones básicas y los tres ejemplos. No necesita las bibliotecas del proyecto.

Apilamos los niveles consecutivos del 1 al `n + 1`. Mientras la orden sea `B`, dejamos los niveles en la pila. Cuando aparece `S` o llegamos al final, desapilamos e imprimimos todo el bloque. La pila convierte los niveles pendientes en una secuencia descendente; el siguiente bloque utiliza niveles mayores y permite subir.

Por ejemplo, con `B B S`:

| Momento | Pila, de base a cima | Salida |
| --- | --- | --- |
| Apilar 1; la orden es B | 1 | — |
| Apilar 2; la orden es B | 1, 2 | — |
| Apilar 3; la orden es S: vaciar | vacía | 3 2 1 |
| Apilar 4; final: vaciar | vacía | 3 2 1 4 |

Cada nivel se crea una sola vez y se retira una sola vez. Así se obtienen niveles distintos, se libera cada nodo y el tiempo total es **O(n)**. La pila puede guardar **O(n)** nodos. Los resultados se imprimen directamente; el arreglo de entrada no cambia y no se crea un arreglo de salida.

Para ejecutar en VS Code, abre el `.cpp` y usa **Terminal → Ejecutar tarea → Ejecutar C++: archivo activo**.

Desde `04_listas_pilas_colas/` también puedes usar:

```sh
clang++ -std=c++17 -Wall -Wextra -Wpedantic soluciones/2024_1_ex01_p02_nautilus.cpp -o /tmp/nautilus
/tmp/nautilus
```

Las pruebas verifican los tres resultados del enunciado, todas las 1023 combinaciones de hasta nueve órdenes (incluida la entrada vacía) y dos secuencias de 10 000 órdenes. Para cada caso comprueban los niveles, que no se repitan, las subidas y bajadas, y que la entrada se conserve.
