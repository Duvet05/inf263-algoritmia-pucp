# Material para dictar recursión

La selección distingue recursión exigida por el enunciado, aplicaciones con estructuras de datos y ejercicios de divide y vencerás. Los niveles y el orden siguientes son sugerencias docentes. Las páginas se cuentan desde el inicio del PDF.

| Orden | Material | Objetivo de clase | Nivel sugerido |
| --- | --- | --- | --- |
| 1 | [Ejemplos básicos](../../material-de-apoyo/fuentes-adicionales/2025-0/Semana%202%20-%20Recursi%C3%B3n/SESI%C3%93N%201/Copia%20de%20main.cpp) | Caso base, reducción del problema y retorno: factorial, Fibonacci, búsqueda, máximo, binario y palíndromos. | Básico |
| 2 | [Hanói clásico](../../material-de-apoyo/fuentes-adicionales/2025-0/Semana%202%20-%20Recursi%C3%B3n/SESI%C3%93N%201/Copia%20de%20hanoi.cpp) | Explicar el árbol de llamadas y el papel de los tres postes. | Básico |
| 3 | [Laboratorio 1 de 2026-1, P1](../../laboratorios/laboratorio-01/2026-1/enunciado.pdf#page=1) | Recorrer un despliegue triangular en una matriz con una única función recursiva. | Intermedio |
| 4 | [Laboratorio 1 de 2024-1, P2](../../laboratorios/laboratorio-01/2024-1/enunciado.pdf#page=3) | Recorrer anillos completos de una matriz sin contar celdas dos veces. | Intermedio |
| 5 | [Laboratorio 2 de 2025-1, P2](../../laboratorios/laboratorio-02/2025-1/enunciado.pdf#page=2) | Representar posición, dirección y combustible como estado recursivo. | Avanzado |
| 6 | [Laboratorio local de 2025-2, recursión](../../laboratorios/laboratorio-01/2025-2/enunciado.pdf#page=2) | Construir galerías, controlar celdas visitadas y deshacer intentos fallidos. | Avanzado |
| 7 | [Examen 1 de 2025-2, P2](../../examenes/parcial/2025-2/enunciado.pdf#page=2) | Adaptar Hanói para permitir solo movimientos entre almacenes adyacentes. | Avanzado |
| 8 | [Examen 1 de 2022-2, P3](../../examenes/parcial/2022-2/enunciado.pdf#page=3) | Aplicar recursión a la criba de Eratóstenes usando lista y cola. El original solicita C. | Avanzado |

## Código asociado a los laboratorios

- Robot arqueólogo (2026-1): [pregunta1.cpp](../../soluciones-actuales/2026_1_lab01/2026_1_lab01_p01_arqueologo.cpp) y [carpeta completa con soluciones, instrucciones y CLion](../../laboratorios/laboratorio-01/2026-1/README.md).
- Radar: [visualización interactiva en HTML](../radar-2024-1/index.html). Incluye los dos ejemplos del enunciado, exploración por anillos o celdas, pila de llamadas, caso base por límites cruzados y suma por referencia. Sigue `Copia de P2.cpp` del exterior al centro; permite mover el radar, editar unidades y descargar el archivo original. Se abre directamente en el navegador, sin instalar nada.
- Radar: [código original](../../laboratorios/laboratorio-01/2024-1/material_original/variantes/2025-0/Semana%202%20-%20Recursi%C3%B3n/SESI%C3%93N%202/Copia%20de%20P2.cpp) y [datos2.txt](../../laboratorios/laboratorio-01/2024-1/material_original/variantes/2024-2/LAB1/Viernes%2013%EF%BC%8F09/Copia%20de%20datos2.txt).
- Vetas de oro: [p2.cpp](../../laboratorios/laboratorio-02/2025-1/material_original/variantes/2025-2/LAB1/2025-1/Lab2/p2.cpp) y [p2.txt](../../laboratorios/laboratorio-02/2025-1/material_original/variantes/2025-2/LAB1/2025-1/Lab2/p2.txt).
- Galerías: [pregunta2.cpp](../../laboratorios/laboratorio-01/2025-2/material_original/resolucion/pregunta2.cpp) y [explicación que ya estaba en la carpeta](../../laboratorios/laboratorio-01/2025-2/material_original/INSTRUCCIONES_ALUMNOS.md).

Para usar los ejemplos que leen un archivo, hay que ejecutar el programa desde su carpeta de datos. Los nombres `datos2.txt` y `p2.txt` se conservan en estos accesos.

No identifiqué una solución específica para Hanói con adyacencia ni para la criba entre los códigos asociados. El archivo `originales/2025-2/EX1/2025-2/p2.cpp` trata fusión de pilas con Hanói clásico y no corresponde a la restricción de adyacencia de ese examen.

## Restricciones que conviene destacar al alumnado

- **Robot arqueólogo (2026-1, P1):** una sola función recursiva sin iteraciones; ciclos solo para imprimir la matriz; sin variables globales.
- **Radar (2024-1, P2):** función recursiva; sin iterativas anidadas; la única global permitida es la matriz.
- **Vetas (2025-1, P2):** una sola función recursiva, una matriz de entrada; sin iterativas dobles ni arreglos o matrices auxiliares.
- **Galerías (PDF local):** una sola función recursiva sin ciclos; los ciclos se permiten para la carga previa o la impresión posterior.
- **Hanói adyacente (2025-2, P2):** una sola función recursiva; no se admite mover directamente A→C.
- **Criba (2022-2, P3):** lista y cola; sin arreglos ni TAD adicionales.

## Continuación del curso

Para divide y vencerás están [búsqueda binaria](../../material-de-apoyo/divide-y-venceras/material_original/binary_search.cpp), [merge sort](../../material-de-apoyo/divide-y-venceras/material_original/merge_sort.cpp), las [diapositivas](../../material-de-apoyo/divide-y-venceras/teoria.pdf) y los [ejercicios adicionales](../../material-de-apoyo/divide-y-venceras/ejercicios.pdf). Los laboratorios clasificados están en [02_divide_y_venceras](../02_divide_y_venceras/README.md).

Para recursión sobre árboles: [Lab 5 de 2025-1, P1(c)](../../laboratorios/laboratorio-05/2025-1/enunciado.pdf#page=1) (árbol gramatical), [Examen 2 de 2024-2, P2(b)](../../examenes/final/2024-2/enunciado.pdf#page=3) (contraseña en ABB) y [Examen 2 de 2025-1, P1](../../examenes/final/2025-1/enunciado.pdf#page=1) (construcción de ABB balanceado).

Para backtracking: [Examen 2 de 2023-1, P3](../../examenes/final/2023-1/enunciado.pdf#page=4) (rutas de Bowser). Su P2 es programación dinámica y exige una implementación iterativa.

Como aplicaciones complementarias están [Lab 2 de 2024-1, P2](../../laboratorios/laboratorio-02/2024-1/enunciado.pdf#page=2) (robot Hanói 3.0), [Examen 1 de 2023-2, P3](../../examenes/parcial/2023-2/enunciado.pdf#page=5) (robot HEX; permite recursión) y [Examen 2 de 2024-1, P3(b)](../../examenes/final/2024-1/enunciado.pdf#page=5) (Josephus; permite recursión).

## Estado del material

En el laboratorio de 2024-1, P1 exige fuerza bruta, pero el código asociado combina enumeración de subconjuntos y backtracking recursivo. [Aclaración sobre P1 y problemas detectados](../03_fuerza_bruta/NOTA_P1_2024_1.md). La exigencia de recursión del enunciado corresponde a P2.

El código se conserva como material original; la tarea realizada verifica la descarga y clasifica el contenido, sin certificar funcionalmente todas las soluciones. La lectura detectó puntos concretos para revisar antes de clase: límites de fila y columna en el código de radar y de vetas; el ejemplo básico convierte un literal a `char*`; merge sort utiliza arreglos de tamaño variable, que dependen de extensiones del compilador. No se modificaron estos ejemplos.

El semestre del PDF local se toma de `INSTRUCCIONES_ALUMNOS.md`; el PDF no lo identifica en su encabezado.

[Volver al catálogo](../../catalogo/index.html)
