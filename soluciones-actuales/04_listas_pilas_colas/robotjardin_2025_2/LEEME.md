# ROBOTJARDIN 1.0 · Pregunta 4

[Abrir la representación visual](index.html) · [Código completo en C++](../soluciones/2025_2_ex01_p04_robotjardin.cpp) · [Volver al catálogo](../LEEME.md)

Abre `index.html` directamente en el navegador. Incluye las dos matrices del enunciado, resalta el rectángulo máximo y permite introducir otra matriz de ceros y unos. En «Ver paso a paso» puedes recorrer las operaciones de la pila o saltar al cierre de cada fila. La vista funciona sin conexión y permite descargar el mismo `2025_2_ex01_p04_robotjardin.cpp` de la carpeta `soluciones`.

## Ejecutar el C++

Desde esta carpeta:

```sh
clang++ -std=c++17 -O2 -Wall -Wextra -Wpedantic ../soluciones/2025_2_ex01_p04_robotjardin.cpp -o /tmp/robotjardin
/tmp/robotjardin
```

El primer ejemplo da **6**: filas 1–2, columnas 1–3, un rectángulo de 2 × 3. El segundo da **10**: filas 2–3, columnas 1–5, un rectángulo de 2 × 5.

`calcularAreaMaxima(jardin, n, m)` recibe la matriz como `const`, así que no puede escribir en ella. Las matrices de entrada se declaran con `MAX_COLUMNAS` columnas de capacidad; `m` indica cuántas se utilizan. Puedes modificar las entradas del `main`, `n` y `m` para probar otros jardines. La capacidad actual es de 100 columnas. La interfaz admite hasta 20 × 20 para mantener legible la matriz.

## Cómo funciona

1. Para cada fila se actualiza **un único arreglo** `alturas`: un 1 incrementa la altura de su columna; un 0 la reinicia.
2. Una **pila enlazada de índices de columnas** mantiene alturas en orden no decreciente.
3. Al encontrar una altura menor, se desapila y se calcula `alto × ancho`. Después de desapilar, `izquierda` es 0 si la pila quedó vacía; de lo contrario es `cima + 1`. El ancho es `col - izquierda`.
4. Al llegar a `col == m`, se vacía la pila y se calculan los rectángulos pendientes. No se agrega una columna a la matriz ni al arreglo.
5. Se guarda el mejor resultado en variables escalares, con sus coordenadas. Si hay empate se conserva el primero encontrado.

Cada columna entra y sale de la pila una sola vez por fila. Por eso el tiempo es **O(n × m)** aunque haya un `while` dentro del `for`; el espacio auxiliar es **O(m)**. Todas las funciones son iterativas y solo se incluye `iostream`. Los nodos se liberan al desapilar y el arreglo se libera al finalizar.

El HTML sigue el mismo orden de operaciones del C++. Guarda instantáneas para permitir retroceder en la explicación; esas instantáneas pertenecen a la interfaz, no al algoritmo del robot.

## Verificación

```sh
python3 tests/test_robotjardin.py
```

Las pruebas compilan el C++, comparan sus resultados y los del HTML contra una búsqueda exhaustiva independiente, comprueban que no se cambia la matriz y verifican los límites de los rectángulos. También cubren ceros, unos, una sola fila o columna, empates y los dos ejemplos.
