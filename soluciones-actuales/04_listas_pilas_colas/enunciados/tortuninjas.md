# TortuNinjas — Examen 1 de 2023-2, pregunta 1

[Enunciado completo: páginas 1–2](../../../examenes/parcial/2023-2/enunciado.pdf) · [Solución en C++](../soluciones/2023_2_ex01_p01_tortuninjas.cpp)

Cada camión es una lista simplemente enlazada de pesos. Se ingresan entre 5 y 8 camiones, las capacidades de los cuatro ninjas y una cantidad variable de artefactos por camión. El 0 termina la entrada de cada camión y no se guarda como artefacto.

## Cómo leer el código

1. `Nodo`, `Lista` y `insertarFinal`: construir un camión sin conocer de antemano cuántos artefactos contiene.
2. `sumarPesos`: recorrer una lista para conocer el peso del camión.
3. `buscarAsignacion`: probar un ninja para cada camión mediante dos `for` con avance y retroceso manual; si la elección impide completar la misión, deshacerla y probar otra. Cada ninja recibe uno o dos camiones, sin superar su capacidad.
4. `ordenarBurbuja`: ordenar los pesos del primer camión en forma ascendente y los del segundo en forma descendente.
5. `intercalarListas`: reconectar los nodos originales, uno de cada lista. Los sobrantes se añaden al final y la lista absorbida queda vacía.
6. `prepararRescate` y `mostrarRescate`: reunir los artefactos y mostrar un camión final por ninja.

Toda la solución es iterativa, sin recursión. El reparto del apartado b utiliza los datos de los ninjas y dos índices, sin arreglos ni pilas auxiliares. Burbuja y el intercalado corresponden al apartado c: no reservan nodos ni arreglos adicionales y no usan otro TAD.

## Cómo funciona el reparto sin recursión

La implementación continúa los dos ciclos del alumno: el ciclo exterior mueve el índice del camión manualmente y el interior prueba ninjas. Si una entrega impide continuar, la deshace y sigue desde el siguiente ninja. La [guía de clase y las tablas de Excel](../../../clases/tortuninjas/README.md) muestran cada paso.

## Ejemplo del examen

| Ninja | Capacidad | Camiones | Peso total |
| --- | ---: | --- | ---: |
| Leonardo | 34 | 1 y 5 | 31 |
| Rafael | 24 | 2 | 24 |
| Donatello | 12 | 3 | 9 |
| Miguel Ángel | 30 | 4 | 25 |

Para Leonardo:

```text
Camión 1 ascendente:   8 → 9
Camión 5 descendente:  6 → 5 → 3
Camión final:          8 → 6 → 9 → 5 → 3
```

El PDF muestra un 0 al final de la salida de Miguel Ángel; aquí se interpreta como terminador del ingreso y se imprimen únicamente los artefactos.

## Ejecutar en VS Code

Abre el archivo C++ y usa **Terminal → Ejecutar tarea → Ejecutar C++: archivo activo**. El programa pedirá los datos. Puedes pegar esta entrada completa:

```text
5
34 24 12 30
8 9 0
15 9 0
3 6 0
1 6 8 4 6 0
5 6 3 0
```

Salida del rescate:

```text
Leonardo: 8 6 9 5 3
Rafael: 15 9
Donatello: 3 6
Miguel Angel: 1 6 8 4 6
```

Desde la carpeta del tema también se puede ejecutar el caso guardado:

```sh
clang++ -std=c++17 -Wall -Wextra -Wpedantic soluciones/2023_2_ex01_p01_tortuninjas.cpp -o /tmp/tortuninjas
/tmp/tortuninjas < tests/datos/tortuninjas-ejemplo.txt
```

## Verificar

`python3 tests/test_listas.py` incluye el ejemplo, el ingreso de 5 a 8 camiones, casos sin reparto válido, un caso que exige deshacer asignaciones y la comparación de la búsqueda con una enumeración independiente. También verifica el orden del intercalado, los extremos de las listas y que se conserven los mismos nodos.
