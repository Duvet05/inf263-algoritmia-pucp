# Catálogo de soluciones actuales

[Volver al inicio](../README.md)

[Ver todos los laboratorios por ciclo](../laboratorios/README.md)

Esta sección incorpora código local reciente sin modificar las soluciones históricas. **Verificado** significa que el archivo compila con C++17 y que pasan las pruebas indicadas; no afirma una calificación oficial del curso. Cada programa con `main` se compila por separado.

| Ciclo | Evaluación | Pregunta | Código | Enunciado | Verificación |
| --- | --- | --- | --- | --- | --- |
| 2024-1 | Lab. 1 | P1, Kung Fu Panda | [C++](2024_1_lab01_po/2024_1_lab01_p01_po.cpp) | [PDF](2024_1_lab01_po/enunciado.pdf) | Compilación y 5 pruebas con oráculo exhaustivo |
| 2025-1 | Lab. 2 | P1, cuadrigas | [C++](04_listas_pilas_colas/soluciones/2025_1_lab02_p01_cuadrigas.cpp) | [PDF](04_listas_pilas_colas/enunciados/2025_1_lab02_cuadrigas_y_vetas_de_oro.pdf) | Compilación; orden estable y conservación de nodos |
| 2025-2 | Ex. 1 | P4, ROBOTJARDIN | [C++](04_listas_pilas_colas/soluciones/2025_2_ex01_p04_robotjardin.cpp) · [visualización](04_listas_pilas_colas/robotjardin_2025_2/index.html) | [PDF](04_listas_pilas_colas/enunciados/2025_2_ex01_alertas_hanoi_estructuras_lineales.pdf) | 4885 matrices frente a búsqueda exhaustiva |
| 2026-1 | Lab. 1 | P1, robot arqueólogo | [C++](2026_1_lab01/2026_1_lab01_p01_arqueologo.cpp) | [PDF](2026_1_lab01/enunciado.pdf) | Compilación y caso del enunciado |
| 2026-1 | Lab. 1 | P2, citas odontológicas | [C++](2026_1_lab01/2026_1_lab01_p02_citas.cpp) | [PDF](2026_1_lab01/enunciado.pdf) | Compilación y caso del enunciado |
| 2026-1 | Lab. 2 | P1, barajado | [C++](04_listas_pilas_colas/soluciones/2026_1_lab02_p01_barajado.cpp) | [PDF](04_listas_pilas_colas/enunciados/2026_1_lab02_barajado_y_canarios.pdf) | Compilación; 52 cartas y conservación de nodos |
| 2026-1 | Lab. 2 | P2, canario ancestral | [C++](04_listas_pilas_colas/soluciones/2026_1_lab02_p02_canarios.cpp) | [PDF](04_listas_pilas_colas/enunciados/2026_1_lab02_barajado_y_canarios.pdf) | Compilación y caso del enunciado |

La [biblioteca de listas](04_listas_pilas_colas/biblioteca/listas/LEEME.md) y la [implementación en un solo archivo](04_listas_pilas_colas/soluciones/2026_1_lab02_lista_enlazada.cpp) sirven como referencia para ejercicios nuevos.

## Pendiente de revisión

- **2025-1, Lab. 2, P2 (vetas de oro):** el archivo local `laboratorios/04_listas_pilas_colas/soluciones/2025_1_lab02_p02.cpp` contiene una expresión donde debería llamarse a `recorrer` y falla al compilar con `-Werror`. Hace falta corregirlo y contrastar sus resultados con el enunciado antes de publicarlo como solución.
- **2024-1, Lab. 1, P2 (radar)** y **2025-2, Lab. 1, P2 (galerías):** hay fuentes en el material local de recursión, pero no se incluyeron en este lote porque aún no tienen una comprobación funcional reproducible.
- El resto de los enunciados del material local no tiene una solución verificada en esta actualización. Añade cada pregunta al catálogo cuando haya código y una comprobación reproducible.
