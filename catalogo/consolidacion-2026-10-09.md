# Consolidación local del curso — 9 de octubre de 2026

La copia de trabajo canónica es este repositorio y su [proyecto de VS Code](../algoritmia.code-workspace). Se compararon las carpetas locales LAB1, LAB2, Pásalo, el sílabo y los ZIP archivados antes de sustituir las copias dispersas.

## Material recuperado

- [Laboratorio complementario de Algoritmos Avanzados, 1INF32](../material-de-apoyo/algoritmos-avanzados/2024-2/laboratorio-01/README.md).
- [Sílabo 2026-2](../material-de-apoyo/silabos/2026-2/enunciado.pdf).
- [Clase completa de mochilas](../clases/mochilas/README.md), con HTML, PDF, práctica, guion y casos.
- Visualizaciones de [Po](../clases/po-2024-1/LEEME.md) y [radar](../clases/radar-2024-1/README.md).
- [Guía docente del laboratorio 1 de 2025-1](../laboratorios/laboratorio-01/2025-1/material_original/clase-docente/GUIA_CLASE_DOCENTE.md), variantes de código y versiones rescatadas de ZIP.

## Comprobación

El [inventario CSV](consolidacion-2026-10-09.csv) registra 831 archivos, accesos directos y miembros de ZIP. Los destinos conservados tienen SHA-256. Los cambios de enlaces y formato se identifican; las variantes funcionales permanecen separadas de las soluciones verificadas.

Los ZIP se descomprimieron y compararon por contenido. Sus accesos directos apuntan al documento canónico. Los ejecutables, cachés, metadatos e índices regenerables no se añaden al repositorio.

~~~sh
python3 scripts/verificar_actuales.py
~~~

La limpieza se realiza después de publicar y verificar los destinos. Las carpetas sustituidas se trasladan a la Papelera, sin borrado permanente.
