# Laboratorio 1 — semestre 2025-1

## Archivos incluidos

- `lab1.pdf`: enunciado original.
- `resolucion/pregunta1.cpp`: asignación óptima de tablas a discos mediante
  fuerza bruta.
- `resolucion/pregunta2a.cpp`: combinaciones que cumplen el rango de
  presupuesto y las dependencias.
- `resolucion/pregunta2b.cpp`: segundo proyecto de la Pregunta 2, añadiendo el
  nivel mínimo de seguridad.
- `resolucion/CMakeLists.txt`: permite compilar los tres ejecutables.
- `GUIA_CLASE_DOCENTE.md`: explicación y propuesta de desarrollo de la clase.

## Compilación desde la terminal

Primero entren a la carpeta:

```bash
cd laboratorios/laboratorio-01/2025-1/material_original/clase-docente/resolucion
```

### Pregunta 1

```bash
clang++ -std=c++17 -Wall -Wextra -Wpedantic pregunta1.cpp -o pregunta1
./pregunta1
```

Resultado principal esperado:

```text
Disco 1 - Tablas: 3, 5, 6 | Velocidad restante: 40 IOPs
Disco 2 - Tablas: 2, 4    | Velocidad restante: 50 IOPs
Disco 3 - Tablas: 1       | Velocidad restante: 50 IOPs
Velocidad minima del grupo: 40 IOPs
Combinaciones evaluadas: 729
```

El orden `3, 5, 6` representa el mismo conjunto que `5, 3, 6` mostrado en el
PDF; el orden de las tablas dentro de un disco no altera la solución.

### Pregunta 2a

```bash
clang++ -std=c++17 -Wall -Wextra -Wpedantic pregunta2a.cpp -o pregunta2a
./pregunta2a
```

Presupuestos de prueba:

```text
100
80
```

### Pregunta 2b

```bash
clang++ -std=c++17 -Wall -Wextra -Wpedantic pregunta2b.cpp -o pregunta2b
./pregunta2b
```

Casos de prueba, ingresando primero el presupuesto y luego el nivel mínimo:

```text
200
400
```

```text
300
620
```

```text
100
600
```

## Uso con CMake

```bash
cmake -S . -B build
cmake --build build
./build/pregunta1
./build/pregunta2a
./build/pregunta2b
```

## Requisitos que deben poder justificar

- La Pregunta 1 explora `3^6 = 729` asignaciones.
- Las Preguntas 2a y 2b exploran `2^10 = 1024` subconjuntos, incluyendo el
  vacío; el programa procesa las 1023 combinaciones no vacías.
- No se utilizan variables globales.
- Solo se emplean librerías autorizadas por el documento.
- Cada función contiene un comentario que explica su estrategia.
- La parte 2b está separada de 2a, como solicita el PDF.

El documento original exige NetBeans y un formato de nombre basado en el
código del alumno. Si estos archivos se utilizan para una entrega formal,
cada alumno debe trasladarlos a los proyectos indicados y aplicar exactamente
el nombre solicitado por el docente.
