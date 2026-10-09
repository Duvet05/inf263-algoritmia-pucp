# Laboratorio 1: instrucciones para los alumnos

De verdad agradezco que hayan estado presentes. Para las siguientes clases me
voy a asegurar de llevar todo mucho mejor preparado y que podamos aprovechar
mejor el tiempo. Gracias por la comprensión.

## Contenido

- `lab1.pdf`: enunciado original.
- `resolucion/pregunta1.cpp`: solución recursiva del robot arqueólogo.
- `resolucion/pregunta2.cpp`: solución por fuerza bruta del odontólogo.
- `resolucion/CMakeLists.txt`: configuración para abrir ambas soluciones en
  CLion.

## Antes de ejecutar

Lean primero el PDF e identifiquen las restricciones de cada pregunta:

- No se utilizan variables globales.
- Solo se emplean las librerías permitidas por el enunciado.
- En la Pregunta 1 existe una única función recursiva y no contiene
  iteraciones. Los `for` se usan solamente para imprimir la matriz.
- En la Pregunta 2 se utiliza fuerza bruta iterativa, sin recursión.

## Ejecución en CLion

1. Abran CLion.
2. Seleccionen **Open** y abran la carpeta `lab1/resolucion`.
3. Esperen a que CLion termine de cargar CMake.
4. En la lista de configuraciones elijan `pregunta1` o `pregunta2`.
5. Presionen **Run**.

## Ejecución desde una terminal

Entren a la carpeta de soluciones:

```bash
cd lab1/resolucion
```

Compilen y ejecuten la Pregunta 1:

```bash
clang++ -std=c++17 -Wall -Wextra -Wpedantic pregunta1.cpp -o pregunta1
./pregunta1
```

Compilen y ejecuten la Pregunta 2:

```bash
clang++ -std=c++17 -Wall -Wextra -Wpedantic pregunta2.cpp -o pregunta2
./pregunta2
```

En Windows con MinGW pueden reemplazar `clang++` por `g++` y ejecutar, por
ejemplo, `./pregunta1.exe` o `.\pregunta1.exe` desde PowerShell.

## Resultados esperados

### Pregunta 1

El robot debe encontrar 4 artefactos y marcar con `*` el despliegue con anchos
7, 5, 3, 1, 3, 5 y 7. Los dos artefactos que están fuera del alcance deben
permanecer como `A`.

### Pregunta 2

El programa debe evaluar 65 536 combinaciones y obtener una ganancia máxima
de S/ 437. Un plan óptimo posible es:

- Cita 1: dientes 7 y 8, 60 de 60 minutos.
- Cita 2: dientes 4, 5 y 6, 42 de 45 minutos.
- Cita 3: dientes 1 y 2, 20 de 50 minutos.

El resultado 307 mostrado en el PDF es un plan factible, pero no es el máximo.
A ese mismo plan todavía se le pueden agregar el diente 1 en la cita 1 y el
diente 5 en la cita 2, sin exceder sus límites. Por ello:

```text
307 + 60 + 70 = 437
```

## Ideas que deben poder explicar

- Cómo se calcula el tiempo y la ganancia total de cada diente.
- Por qué asignar un solo número de cita a cada diente evita dividir sus
  restauraciones.
- Por qué cada diente tiene cuatro decisiones posibles: 0, 1, 2 o 3.
- Cómo `% 4` obtiene una decisión y `/= 4` permite leer la siguiente.
- Por qué existen `4^8 = 65 536` combinaciones.
- La diferencia entre `planActual` y `mejorPlan`.
- Por qué una combinación se descarta cuando excede el tiempo de una cita.
- Por qué encontrar un plan factible con ganancia 437 demuestra que es óptimo:
  437 es la suma de todas las ganancias disponibles.

## Checklist antes de entregar

1. Reemplacen los nombres por el formato solicitado en el PDF:
   `CODIGO_LAB1_P1B.cpp` y `CODIGO_LAB1_P2B.cpp`.
2. Sustituyan `CODIGO` por su código de alumno.
3. Compilen ambos archivos y revisen sus resultados.
4. No incluyan ejecutables, carpetas de compilación ni archivos temporales.
5. Para la entrega oficial, creen el ZIP con la herramienta indicada en el
   enunciado y súbanlo a la tarea correspondiente de PAIDEIA.
