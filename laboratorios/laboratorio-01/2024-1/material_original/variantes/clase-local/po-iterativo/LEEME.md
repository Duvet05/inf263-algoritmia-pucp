# P1 de 2024-1: fuerza bruta iterativa

[p1.cpp](../../../../../../../soluciones-actuales/2024_1_lab01_po/2024_1_lab01_p01_po.cpp) resuelve Kung Fu Panda enumerando asignaciones completas de armas. Usa base `G + 1`: cada arma queda sin usar (`0`) o se asigna a uno de los `G` guerreros. Con los tres guerreros del ejemplo, la base es 4.

El programa comprueba que cada arma tenga un tipo permitido, que sus prerrequisitos estén en la misma mochila y que el poder reunido sea **estrictamente mayor** al del guerrero. Busca una solución válida; puede encontrar una distinta del ejemplo del PDF.

Desde esta carpeta:

```sh
clang++ -std=c++17 -O2 -Wall -Wextra -Wpedantic p1.cpp -o /tmp/po_p1
/tmp/po_p1 datos1.txt
```

`datos1.txt` contiene el ejemplo del PDF y admite el mismo formato de lectura que la copia de Drive:

1. Cantidad de guerreros, entre 1 y 3.
2. Por cada guerrero: poder, cantidad de tipos permitidos y esos tipos.
3. Cantidad de armas, hasta 12.
4. Por cada arma: letra, poder, tipo, cantidad de prerrequisitos y sus letras.

Los espacios y saltos de línea son intercambiables. Se puede proporcionar otra ruta de datos como argumento; sin argumento se busca `datos1.txt` en el directorio de ejecución.

Para ejecutar las pruebas:

```sh
python3 -m unittest discover -s tests -v
```
