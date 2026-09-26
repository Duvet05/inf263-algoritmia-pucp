# Mantener el repositorio actualizado

Las carpetas históricas se mantienen como referencia. Para una solución reciente, usa `soluciones-actuales/` y anota su estado en [el catálogo](soluciones-actuales/CATALOGO.md).

1. Guarda el programa con el patrón `aaaa_c_labNN_pNN_tema.cpp` (por ejemplo, `2026_1_lab02_p01_barajado.cpp`). Coloca datos y enunciado en la misma carpeta de la evaluación cuando estén disponibles. No subas binarios, archivos temporales ni copias repetidas del mismo PDF.
2. Añade una fila al catálogo con ciclo, evaluación, pregunta, enlace al código y al enunciado, y qué se comprobó. Distingue código verificado de material pendiente; no presentes una pregunta sin compilar como resuelta.
3. Documenta desde qué carpeta se compila y ejecuta. Si un programa usa `main`, compílalo de forma independiente. Añade una prueba que compruebe el resultado o una propiedad del algoritmo y registra el caso del enunciado.
4. Incorpora la nueva prueba a `scripts/verificar_actuales.py` y ejecuta `python3 scripts/verificar_actuales.py` antes de enviar cambios. El flujo de GitHub Actions ejecuta esa misma orden en cada propuesta y cambio a la rama principal.
5. Comprueba que los enlaces relativos de README y catálogo abren archivos existentes. Actualiza el índice de la portada con la nueva evaluación.

Si una solución procede de material externo, conserva su procedencia y evita atribuirla a una evaluación distinta. Una prueba de compilación por sí sola no valida el algoritmo.
