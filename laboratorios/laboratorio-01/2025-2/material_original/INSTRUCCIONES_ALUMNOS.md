# Laboratorio 1 — semestre 2025-2

## Contenido

- `lab1.pdf`: enunciado original.
- `resolucion/pregunta1.cpp`: fuerza bruta para controles de seguridad.
- `resolucion/pregunta2.cpp`: recursión para perforar galerías.
- `resolucion/CMakeLists.txt`: proyecto con ambos ejecutables.

## Uso en Visual Studio Code

Desde la terminal integrada:

```bash
cd /Users/duvet05/Desktop/lab1-2025-02/resolucion
```

Pregunta 1:

```bash
clang++ -std=c++17 -Wall -Wextra -Wpedantic pregunta1.cpp -o pregunta1
./pregunta1
```

Ingresen `P B F` en una sola línea. Casos del PDF:

```text
50000 100 3
70000 150 5
100000 190 4
```

Pregunta 2:

```bash
clang++ -std=c++17 -Wall -Wextra -Wpedantic pregunta2.cpp -o pregunta2
./pregunta2
```

Ingresen `3` para reproducir el primer ejemplo o `2` para el segundo.

## Qué deben explicar

### Pregunta 1

- Ocho controles producen `2^8 = 256` subconjuntos, incluido el vacío.
- Una máscara de bits indica cuáles controles pertenecen a cada subconjunto.
- Se muestran solamente los subconjuntos cuyo costo es `<= P`, cuyo beneficio
  es `>= B` y cuyos falsos negativos son `<= F`.
- Se interpreta la frase ambigua del PDF como `beneficio >= B`, porque sus
  propios casos consideran válidos resultados con beneficio exactamente `B`.

### Pregunta 2

- La única función recursiva tiene un modo para buscar el siguiente inicio y
  otro para construir la galería actual.
- Cada galería comienza en la celda libre más baja del borde izquierdo.
- La prioridad abajo, derecha y arriba mantiene el camino lo más bajo posible
  y reproduce los mapas del PDF.
- Una celda con `-1` es una roca, `0` está libre y un número positivo identifica
  la galería que utiliza la celda.
- Si un camino queda encerrado, se aplica backtracking: se desmarca la celda y
  se intenta otra dirección.
- Los únicos ciclos de la Pregunta 2 cargan las rocas antes de la recursión o
  imprimen la matriz después de ella, como exige el enunciado.

