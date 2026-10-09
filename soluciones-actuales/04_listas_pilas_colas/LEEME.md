# Listas, pilas y colas


[Abrir catálogo general](../../catalogo/index.html) · [Biblioteca de listas](biblioteca/listas/LEEME.md) · [Biblioteca de pilas](biblioteca/pilas/LEEME.md) · [Ejemplo de uso](ejemplos/uso_lista.cpp) · [Torres de Hanói](ejemplos/torres_de_hanoi.cpp)

Para ver una pila enlazada en un solo archivo, usa [Bad Sunny con pila propia](ejemplos/bad_sunny_pila_simple.cpp). Se compila de forma independiente; la solución de `soluciones/` utiliza las bibliotecas compartidas.

También puedes revisar la [biblioteca de listas en un solo archivo](soluciones/2026_1_lab02_lista_enlazada.cpp), con inserción, búsqueda, extracción, eliminación, concatenación, inversión y liberación de nodos.

## Soluciones

Los nombres siguen `ciclo_evaluacion_pregunta_tema.cpp`; por ejemplo, `2026_1_lab02_p01_barajado.cpp` corresponde a 2026-1, laboratorio 2, pregunta 1. Cada archivo es un programa independiente con su propio `main`.

| Ciclo y pregunta | Solución | Enunciado / visualización |
| --- | --- | --- |
| 2022-2 · Ex. 1 · P2 | [Bad Sunny: frecuencia que más dura, con una pila](soluciones/2022_2_ex01_p02_bad_sunny.cpp) | [Enunciado](../../examenes/parcial/2022-2/enunciado.pdf) |
| 2023-2 · Ex. 1 · P1 | [TortuNinjas: reparto sin recursión y listas simples](soluciones/2023_2_ex01_p01_tortuninjas.cpp) | [Enunciado y guía de ejecución](enunciados/tortuninjas.md) |
| 2023-2 · Ex. 1 · P2 | [Incidentes: reiniciar cola y reclasificar pilas](soluciones/2023_2_ex01_p02_incidentes.cpp) | [Enunciado, pasos y estados](enunciados/incidentes.md) |
| 2024-1 · Ex. 1 · P2 | [Nautilus: subir y bajar con una pila enlazada propia](soluciones/2024_1_ex01_p02_nautilus.cpp) | [Enunciado, ejemplos y explicación](enunciados/nautilus.md) |
| 2025-1 · Lab. 2 · P1 | [Cuadrigas: pares antes que impares](soluciones/2025_1_lab02_p01_cuadrigas.cpp) | [Enunciado](../../laboratorios/laboratorio-02/2025-1/enunciado.pdf) |
| 2025-1 · Lab. 2 · P2 | [Vetas de oro: robot con combustible limitado](soluciones/2025_1_lab02_p02_vetas_de_oro.cpp) | [Enunciado](../../laboratorios/laboratorio-02/2025-1/enunciado.pdf) |
| 2025-2 · Ex. 1 · P4 | [ROBOTJARDIN: rectángulo máximo](soluciones/2025_2_ex01_p04_robotjardin.cpp) | [Enunciado](../../examenes/parcial/2025-2/enunciado.pdf) · [Visualización](robotjardin_2025_2/index.html) |
| 2026-1 · Lab. 2 · P1 | [Barajado de cartas](soluciones/2026_1_lab02_p01_barajado.cpp) | [Enunciado](../../laboratorios/laboratorio-02/2026-1/enunciado.pdf) |
| 2026-1 · Lab. 2 · P2 | [Canario ancestral](soluciones/2026_1_lab02_p02_canarios.cpp) | [Enunciado](../../laboratorios/laboratorio-02/2026-1/enunciado.pdf) |

Antes se llamaban `resolucion 2025-1.cpp`, `robotjardin_2025_2/P4.cpp` y `resolucion.cpp`, respectivamente.

## Organización

```text
soluciones/          Programas resueltos y referencia de operaciones con listas
biblioteca/listas/    Estructuras y funciones básicas reutilizables
biblioteca/pilas/     Pila construida sobre la lista (cima = inicio)
ejemplos/            Uso de la lista, Hanói y Bad Sunny con pila propia
practica/            Ejercicios del alumno: listas y pilas
enunciados/          PDFs de los laboratorios y enlaces a exámenes anteriores
robotjardin_2025_2/   Visualización, explicación y pruebas de ROBOTJARDIN
tests/               Pruebas de las bibliotecas, Hanói y las soluciones
```


## Compilar

Ejecuta desde esta carpeta. Puedes sustituir `clang++` por `g++`.

```sh
clang++ -std=c++17 -Wall -Wextra -Wpedantic soluciones/2023_2_ex01_p01_tortuninjas.cpp -o /tmp/tortuninjas
/tmp/tortuninjas < tests/datos/tortuninjas-ejemplo.txt

clang++ -std=c++17 -Wall -Wextra -Wpedantic soluciones/2023_2_ex01_p02_incidentes.cpp -o /tmp/incidentes
/tmp/incidentes

clang++ -std=c++17 -Wall -Wextra -Wpedantic soluciones/2024_1_ex01_p02_nautilus.cpp -o /tmp/nautilus
/tmp/nautilus

clang++ -std=c++17 -Wall -Wextra -Wpedantic soluciones/2025_1_lab02_p01_cuadrigas.cpp -o /tmp/cuadrigas
/tmp/cuadrigas

clang++ -std=c++17 -Wall -Wextra -Wpedantic soluciones/2026_1_lab02_p01_barajado.cpp -o /tmp/barajado
/tmp/barajado

clang++ -std=c++17 -Wall -Wextra -Wpedantic soluciones/2026_1_lab02_p02_canarios.cpp -o /tmp/canarios
/tmp/canarios

clang++ -std=c++17 -Wall -Wextra -Wpedantic soluciones/2026_1_lab02_lista_enlazada.cpp -o /tmp/lista_enlazada
/tmp/lista_enlazada

clang++ -std=c++17 -Wall -Wextra -Wpedantic soluciones/2025_2_ex01_p04_robotjardin.cpp -o /tmp/robotjardin
/tmp/robotjardin

clang++ -std=c++17 -Wall -Wextra -Wpedantic ejemplos/uso_lista.cpp biblioteca/listas/FuncionesLista.cpp -o /tmp/uso_lista
/tmp/uso_lista

clang++ -std=c++17 -Wall -Wextra -Wpedantic ejemplos/torres_de_hanoi.cpp biblioteca/pilas/FuncionesPila.cpp biblioteca/listas/FuncionesLista.cpp -o /tmp/hanoi
/tmp/hanoi      # 3 discos; /tmp/hanoi 5 para otra cantidad

clang++ -std=c++17 -Wall -Wextra -Wpedantic soluciones/2022_2_ex01_p02_bad_sunny.cpp biblioteca/pilas/FuncionesPila.cpp biblioteca/listas/FuncionesLista.cpp -o /tmp/bad_sunny
/tmp/bad_sunny
```

Resultados esperados: cuadrigas muestra los IDs `4, 12, 17, 7`; barajado conserva las 52 cartas y termina con longitud cero; canarios muestra `6`; ROBOTJARDIN obtiene áreas máximas de `6` y `10`; Hanói hace `7` movimientos con 3 discos por ambos métodos; Bad Sunny muestra `Frecuencia maxima = 4 Duracion = 5`; Nautilus reproduce los tres ejemplos del enunciado; TortuNinjas asigna los camiones 1 y 5 a Leonardo y conserva los nodos al intercalar; incidentes reproduce el reinicio de la cola y la reclasificación de la consola del PDF.

## Verificar

```sh
python3 tests/test_listas.py
python3 robotjardin_2025_2/tests/test_robotjardin.py
```

La primera orden comprueba las bibliotecas de listas y pilas, los ejemplos y las soluciones de cuadrigas, barajado, Hanói, Bad Sunny (contra una fuerza bruta) y Nautilus (ejemplos, todas las combinaciones de hasta nueve órdenes y dos secuencias de 10 000 órdenes), además de TortuNinjas (reparto iterativo, entrada variable, burbuja e intercalado de nodos) e incidentes (ejemplo y 150 escenarios que conservan los mismos nodos y códigos); requiere Python 3 y un compilador C++17. La segunda verifica también el algoritmo del HTML de ROBOTJARDIN; requiere Node.js.

Para ejecutar las pruebas de listas con detección de accesos inválidos a memoria y comportamiento indefinido (Clang/GCC compatibles):

```sh
LISTAS_SANITIZERS=1 python3 tests/test_listas.py
```

## Material anterior

| Material | Preguntas y páginas |
| --- | --- |
| [2025-1 — Laboratorio 2 — Cuadrigas y vetas de oro](../../laboratorios/laboratorio-02/2025-1/enunciado.pdf) | P1 (p. 1): partición estable de lista por IDs pares e impares. P2 (p. 2): robot que detecta vetas de oro con combustible limitado y cambios de dirección. |
| [2022-2 — Examen 1 — Listas, frecuencias y criba de Eratóstenes](../../examenes/parcial/2022-2/enunciado.pdf) | P1 (p. 1): fusión de pedidos en listas. P2 (p. 2): frecuencias con una pila. P3 (p. 3): criba de Eratóstenes recursiva con lista y cola. |
| [2025-2 — Examen 1 — Alertas, Hanói y estructuras lineales](../../examenes/parcial/2025-2/enunciado.pdf) | P1 (p. 1): selección de alertas por fuerza bruta. P2 (p. 2): Hanói con movimientos solo entre almacenes adyacentes. P3 (p. 3): intercalar tipos en una lista. P4 (p. 4): rectángulos con pila. P5 (p. 4): cola de prioridad. |
| [2023-1 — Laboratorio 3 — Pilas Kupa y fusión de listas](../../laboratorios/laboratorio-03/2023-1/enunciado.pdf) | P1 (p. 1): unir, ordenar y trasladar pilas de guerreros. P2 (p. 2): fusionar listas de problemas de seguridad. |
| [2024-1 — Laboratorio 2 — Emergencias y robot Hanói 3.0](../../laboratorios/laboratorio-02/2024-1/enunciado.pdf) | P1 (p. 1): cola de prioridad de pacientes. P2 (p. 2): robot apilador con una lista y tres pilas auxiliares. |
| [2024-2 — Laboratorio 2 — Equipos y pedidos de delivery](../../laboratorios/laboratorio-02/2024-2/enunciado.pdf) | P1 (p. 1): formar equipos con una pila auxiliar. P2 (p. 2): ordenar pedidos de delivery por tiempo total. |
| [2025-2 — Laboratorio 4 — Canarios y min-heap](../../laboratorios/laboratorio-04/2025-2/enunciado.pdf) | P1 (p. 1): parejas y aves sobrantes con divide y vencerás. P2 (p. 2): construir un min-heap con árbol binario y una cola o pila. |
| [2023-2 — Examen 1 — Tortuninjas, incidentes y robot apilador](../../examenes/parcial/2023-2/enunciado.pdf) | P1 (p. 1): asignación, ordenamiento y fusión de listas. P2 (p. 3): gestión de incidentes con colas y pilas. P3 (p. 5): robot HEX que ordena productos. |
| [2024-1 — Examen 1 — Vaguito, Nautilus, riesgos y aterrizajes](../../examenes/parcial/2024-1/enunciado.pdf) | P1 (p. 1): fusión de listas de productos. P2 (p. 3): movimientos de Nautilus usando una pila. P3(a) (p. 4): ordenar riesgos con divide y vencerás; P3(b): gestionar cola de aterrizaje. |
| [2024-1 — Examen 2 — Pilas, emociones, grafos y Josephus](../../examenes/final/2024-1/enunciado.pdf) | P1 (p. 1): clonar una pila. P2 (p. 1): secuencias de emociones en ABB. P3(a) (p. 4): rutas de mínima latencia en un grafo; P3(b): eliminación circular de Josephus. |
| [2025-1 — Examen 2 — ABB, búsquedas, SQL e inversiones](../../examenes/final/2025-1/enunciado.pdf) | P1 (p. 1): ABB balanceado desde un arreglo. P2 (p. 2): búsqueda en arreglo rotado. P3 (p. 3): AST para SELECT. P4 (p. 4): conteo de inversiones. P5 (p. 5): capacidad de comederos con pila o cola. |
