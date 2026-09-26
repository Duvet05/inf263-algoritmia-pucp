# INF263 Algoritmia
[![Verificación de soluciones actuales](https://github.com/Duvet05/inf263-algoritmia-pucp/actions/workflows/verificar-actuales.yml/badge.svg)](https://github.com/Duvet05/inf263-algoritmia-pucp/actions/workflows/verificar-actuales.yml)

<img src="https://imgs.xkcd.com/comics/travelling_salesman_problem.png" width="100%">

Este curso provee una introducción al modelamiento matemático de los problemas computaciones.
Este cubre algoritmos comunes, paradigmas algorítmicos,
y estructuras de datos utilizadas para resolver estos problemas.
El curso enfatiza la relación entre algoritmos y programación,
e introduce técnicas básicas de análisis y medida de la eficiencia.

## Soluciones actuales

Las soluciones incorporadas desde el material local se encuentran en [soluciones-actuales](soluciones-actuales/CATALOGO.md). El catálogo indica evaluación, pregunta, código, enunciado y estado de verificación. El contenido histórico de `laboratorios/`, `examenes/` y `problemas/` se conserva para consulta.

El [índice de laboratorios por ciclo](laboratorios/README.md) reúne los enunciados recientes y señala cuáles tienen soluciones verificadas.

| Ciclo y evaluación | Soluciones |
| --- | --- |
| 2024-1, laboratorio 1 | [Kung Fu Panda, P1](soluciones-actuales/2024_1_lab01_po/LEEME.md) |
| 2025-1, laboratorio 2 | [Cuadrigas, P1](soluciones-actuales/04_listas_pilas_colas/LEEME.md) |
| 2025-2, examen 1 | [ROBOTJARDIN, P4](soluciones-actuales/04_listas_pilas_colas/robotjardin_2025_2/LEEME.md) |
| 2026-1, laboratorio 1 | [Robot arqueólogo, P1; citas odontológicas, P2](soluciones-actuales/2026_1_lab01/LEEME.md) |
| 2026-1, laboratorio 2 | [Barajado, P1; canario ancestral, P2](soluciones-actuales/04_listas_pilas_colas/LEEME.md) |

Para verificar estas soluciones desde la raíz del repositorio:

```sh
python3 scripts/verificar_actuales.py
```

Se necesitan Python 3, un compilador C++17 y Node.js. La [guía de mantenimiento](CONTRIBUTING.md) explica cómo incorporar el siguiente ciclo y mantener el catálogo y las pruebas al día.

## Tabla de contenido
| Módulo | Tema | Contenido |
|:------:|-------|-----------|
| I | Preliminares |➡️ Fueza bruta <br><br>➡️ Recursión <br><br>➡️ Divide y vencerás <br><br>➡️ Backtracking |
| II | Estructuras de datos |➡️ Pilas <br><br>➡️ Colas <br><br>➡️ Listas <br><br>➡️ Árboles binarios |
| III | Algoritmos de ordenamiento |➡️ Selection sort <br><br>➡️ Insertion sort <br><br>➡️ Merge sort|
| IV | Técnicas algorítmicas |➡️ Búsqueda binaria <br><br>➡️ Programación dinámica|

Nota: Como pueden observar, el contenido del curso dictado en la PUCP
se centra en la implementación de los algoritmos y no en la teoría detrás de estos.
En caso quieran aprender el tema con mayor profundidad, recomiendo lo siguiente:
- Bibliografía:
    - Introduction to Algorithms. Thomas Cormen, Charles Leiserson, Ronald Rivest, Clifford Stein.
    - Guide to Competitive Programming. Antti Laaksonen.
    - Competitive Programming. Felix Halim, Steven Halim.
- Resolución de problemas:
    - LeetCode, HackerRank: Dificultad fácil. Plataformas orientadas a preguntas de entrevistas en compañías tecnológicas.
    - Codeforces, AtCoder, CodeChef: Todos los niveles de dificultad. Plataformas orientadas a la programación competitiva.

Asimismo, adjunto [mi otro repositorio](https://github.com/ManuelLoaizaVasquez/acm-icpc-solutions) con mayor variedad de temas y problemas resueltos.

## Organización de las carpetas
`examenes` - contiene los enunciados y soluciones del examen parcial y final del curso.

`laboratorios` - contiene los [enunciados por ciclo](laboratorios/README.md), material de origen y soluciones históricas.

`problemas` - contiene ejercicios agrupados por temas.

`tarea-academica` - contiene el informe final del curso, el cual lo basé en Segment Tree,
mi estructura de datos favorita en programación competitiva.

`soluciones-actuales` - reúne soluciones recientes verificadas, sus datos y enunciados disponibles.

## Lista de cursos universitarios sobre algoritmos

| Curso                                     	    | Universidad                	|
| -------------------------------------------------	| -----------------------------	|
| [Algorithms and Data Structures](https://www.youtube.com/playlist?list=PLrS21S1jm43igE57Ye_edwds_iL7ZOAG4) | ITMO University |
| [Introduction to Algorithms](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/index.htm) | Massachusetts Institute of Technology |
| [Design and Analysis of Algorithms](http://web.stanford.edu/class/archive/cs/cs161/cs161.1168/) | Stanford University |
| [Data Structures](https://sp21.datastructur.es/) | University of California, Berkeley |
