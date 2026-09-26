# Listas, pilas y colas: soluciones actuales

[Índice general](../../README.md) · [Biblioteca de listas](biblioteca/listas/LEEME.md) · [Ejemplo de uso](ejemplos/uso_lista.cpp)

Cada archivo de `soluciones/` es un programa independiente con su propio `main`. La biblioteca de listas está en `biblioteca/listas/` y se compila junto con los programas que la usan.

| Evaluación | Solución | Enunciado |
| --- | --- | --- |
| 2025-1, laboratorio 2, P1 | [Cuadrigas](soluciones/2025_1_lab02_p01_cuadrigas.cpp) | [PDF](enunciados/2025_1_lab02_cuadrigas_y_vetas_de_oro.pdf) |
| 2025-2, examen 1, P4 | [ROBOTJARDIN](soluciones/2025_2_ex01_p04_robotjardin.cpp) · [visualización](robotjardin_2025_2/index.html) | [PDF](enunciados/2025_2_ex01_alertas_hanoi_estructuras_lineales.pdf) |
| 2026-1, laboratorio 2, P1 | [Barajado de cartas](soluciones/2026_1_lab02_p01_barajado.cpp) | [PDF](enunciados/2026_1_lab02_barajado_y_canarios.pdf) |
| 2026-1, laboratorio 2, P2 | [Canario ancestral](soluciones/2026_1_lab02_p02_canarios.cpp) | [PDF](enunciados/2026_1_lab02_barajado_y_canarios.pdf) |

[Lista enlazada en un solo archivo](soluciones/2026_1_lab02_lista_enlazada.cpp) y [biblioteca reutilizable](biblioteca/listas/LEEME.md) son material de apoyo, no preguntas adicionales.

La P2 de 2025-1 (vetas de oro) no se incluyó como solución: la copia local tiene un error de compilación y requiere revisión funcional. El [catálogo](../CATALOGO.md) registra esta incidencia.

## Verificar

Desde la raíz del repositorio:

```sh
python3 soluciones-actuales/04_listas_pilas_colas/tests/test_listas.py
python3 soluciones-actuales/04_listas_pilas_colas/robotjardin_2025_2/tests/test_robotjardin.py
```

Se necesita Python 3, un compilador C++17 y Node.js para comprobar la visualización de ROBOTJARDIN. Las pruebas compilan en una carpeta temporal. Para activar AddressSanitizer y UndefinedBehaviorSanitizer en las pruebas de listas, usa `LISTAS_SANITIZERS=1` en la primera orden.
