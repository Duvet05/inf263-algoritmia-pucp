# Laboratorio 1 de 2024-1: Kung Fu Panda, P1

[Código](2024_1_lab01_p01_po.cpp) · [Datos del ejemplo](datos1.txt) · [Enunciado](enunciado.pdf) · [Índice general](../../README.md)

Esta versión usa fuerza bruta iterativa: cada arma queda libre o se asigna a un guerrero. Comprueba tipos permitidos, prerrequisitos en la misma mochila y poder estrictamente mayor que el del guerrero.

```sh
clang++ -std=c++17 -O2 -Wall -Wextra -Wpedantic -Werror 2024_1_lab01_p01_po.cpp -o /tmp/po
/tmp/po datos1.txt
python3 test_p1.py
```

Las pruebas comparan casos pequeños con un enumerador independiente. El programa acepta un archivo de datos como argumento; sin argumento busca `datos1.txt` en el directorio de ejecución.
