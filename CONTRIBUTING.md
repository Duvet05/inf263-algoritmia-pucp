# Mantener el repositorio actualizado

Las carpetas históricas se mantienen como referencia. Para una solución reciente, usa `soluciones-actuales/` y anota su estado en [el catálogo](soluciones-actuales/CATALOGO.md).

1. Guarda el programa con el patrón `aaaa_c_labNN_pNN_tema.cpp` (por ejemplo, `2026_1_lab02_p01_barajado.cpp`). Coloca datos y enunciado en la misma carpeta de la evaluación cuando estén disponibles. No subas binarios, archivos temporales ni copias repetidas del mismo PDF.
2. Añade una fila al catálogo con ciclo, evaluación, pregunta, enlace al código y al enunciado, y qué se comprobó. Distingue código verificado de material pendiente; no presentes una pregunta sin compilar como resuelta.
3. Documenta desde qué carpeta se compila y ejecuta. Si un programa usa `main`, compílalo de forma independiente. Añade una prueba que compruebe el resultado o una propiedad del algoritmo y registra el caso del enunciado.
4. Incorpora la nueva prueba a `scripts/verificar_actuales.py` y ejecuta `python3 scripts/verificar_actuales.py` antes de enviar cambios. El flujo de GitHub Actions ejecuta esa misma orden en cada propuesta y cambio a la rama principal.
5. Comprueba que los enlaces relativos de README y catálogo abren archivos existentes. Actualiza el índice de la portada y el [índice de laboratorios](laboratorios/README.md) con la nueva evaluación. Añade la huella SHA-256 de cada PDF nuevo a `catalogo/checksums.sha256` y, para laboratorios, también a `laboratorios/checksums.sha256`. Mantén los archivos de `material_original/` separados de las soluciones verificadas.

Si una solución procede de material externo, conserva su procedencia y evita atribuirla a una evaluación distinta. Una prueba de compilación por sí sola no valida el algoritmo.

## Catálogo y material de clase

El registro de cada documento se mantiene en `catalogo/documentos.json`. Los PDF de evaluaciones se guardan en `laboratorios/laboratorio-NN/ciclo/enunciado.pdf` o `examenes/parcial|final/ciclo/enunciado.pdf`. Los índices por tema, exámenes y material de apoyo se generan desde ese registro con `python3 scripts/generar_catalogo.py`; CI comprueba que estén actualizados y que los enlaces, las huellas de los PDF y el seguimiento de Excel sean coherentes.

Las guías de enseñanza y CSV se guardan en `clases/`. Mantén vacía la plantilla del alumno y verifica el ejemplo completo. El PDF vacío de origen se registra como incidencia, sin crear un enunciado de cero bytes. Conserva variantes de código distintas en `material_original/`; agrupa las copias idénticas y mantén su procedencia en `catalogo/procedencia.csv`.
