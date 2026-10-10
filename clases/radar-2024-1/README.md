# Radar: recursión por anillos

[Visualización interactiva](index.html) · [Enunciado, P2](../../laboratorios/laboratorio-01/2024-1/enunciado.pdf#page=3)

La animación conserva el algoritmo original: entrada a buscar, recorrido del borde, llamada al anillo interior y retorno. Señala los casos donde el cálculo original genera columnas fuera de la matriz.

Verifica los ejemplos, casos límite y 6084 escenarios rectangulares:

~~~sh
node clases/radar-2024-1/tests/radar.test.cjs
~~~
