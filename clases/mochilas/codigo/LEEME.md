# Ejecutar los ejemplos de mochilas

Compila un programa por ejecutable. Desde la raíz del repositorio:

~~~sh
mkdir -p .build
c++ -std=c++17 -O2 -Wall -Wextra -Wpedantic clases/mochilas/codigo/mochila_binaria.cpp -o .build/mochila
.build/mochila < clases/mochilas/codigo/casos/mochila-15.txt
.build/mochila < clases/mochilas/codigo/casos/mochila-9.txt
.build/mochila < clases/mochilas/codigo/casos/mochila-voraz.txt
c++ -std=c++17 -O2 -Wall -Wextra -Wpedantic 'laboratorios/laboratorio-01/2024-1/material_original/variantes/2024-2/LAB1/Viernes 13／09/Copia de P1.cpp' -o .build/po
.build/po 'laboratorios/laboratorio-01/2024-1/material_original/variantes/2024-2/LAB1/Viernes 13／09/Copia de datos1.txt'
.build/po clases/mochilas/codigo/casos/po-igualdad.txt
.build/po clases/mochilas/codigo/casos/po-requisito.txt
.build/po clases/mochilas/codigo/casos/po-sin-solucion.txt
~~~

Mochila: capacidad 15 → peso 15 y selección 1 0 1 1; capacidad 9 → peso 7 y selección 1 1 0 1; pesos 4,3,3 y capacidad 6 → peso 6 y selección 0 1 1. Dos artículos del mismo peso siguen siendo distintos.

Po: igualdad de poder no basta; los requisitos deben estar en la misma mochila y los tipos deben ser compatibles. Los casos cortos producen, respectivamente, sin solución, solución y sin solución.

El primer artículo es el dígito de la izquierda. Los códigos decimales de otras convenciones pueden producir selecciones distintas.

[C++ de Po](../../../laboratorios/laboratorio-01/2024-1/material_original/variantes/2024-2/LAB1/Viernes%2013%EF%BC%8F09/Copia%20de%20P1.cpp) · [Datos](../../../laboratorios/laboratorio-01/2024-1/material_original/variantes/2024-2/LAB1/Viernes%2013%EF%BC%8F09/Copia%20de%20datos1.txt) · [Guía](../README.md)
