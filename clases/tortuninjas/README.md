# TortuNinjas: continuar la implementación del alumno

[Solución C++](../../soluciones-actuales/04_listas_pilas_colas/soluciones/2023_2_ex01_p01_tortuninjas.cpp) · [Enunciado](../../examenes/parcial/2023-2/enunciado.pdf) · [Plantilla Excel](seguimiento-plantilla.csv) · [Seguimiento resuelto](seguimiento-ejemplo.csv)

## Objetivo del reparto

Repartir de 5 a 8 camiones completos entre cuatro ninjas. Cada camión se entrega una sola vez; cada ninja recibe uno o dos camiones y su carga total no supera su capacidad. El peso de cada camión se obtiene recorriendo su lista simple.

## Qué guarda cada campo

Para un camión de índice 0 con lista `8 → 9`, su peso es 17. Si Leonardo lo recibe:

| Campo | Antes | Después | Significado |
| --- | ---: | ---: | --- |
| `capacidad` | 34 | 34 | Máximo permitido |
| `carga` | 0 | 17 | Peso acumulado |
| `primerCamion` | -1 | 0 | Índice del camión |
| `segundoCamion` | -1 | -1 | Segundo lugar disponible |

El índice cero es válido. Se inicializan ambos campos de camión en -1.

## Continuar los dos for

La solución conserva el recorrido de camiones, el ciclo de cuatro ninjas y las asignaciones que construyó el alumno.

1. Calcular `peso` una vez por intento de camión.
2. Probar los ninjas desde `siguienteNinja`.
3. Saltar al siguiente si ya tiene dos camiones o si `carga + peso > capacidad`. La igualdad está permitida.
4. Registrar `i` en el lugar disponible, acumular el peso y hacer `break`.
5. Avanzar manualmente `i++` y empezar el siguiente camión desde el ninja cero.
6. Si no hay candidato, hacer `i--`, retirar esa entrega, restar su peso y seguir desde el ninja posterior al que la tenía.

Por eso el `for` exterior no lleva `i++` en su cabecera: el cuerpo decide cuándo avanzar o retroceder. `actual` empieza en 0; la llamada es `buscarAsignacion(camiones, cantidad, tortugas, 0)`.

`todosCamionesAsignados` comprueba que cada índice aparezca exactamente una vez. Además, al terminar se comprueba que los cuatro ninjas participaron. Si se agotan las alternativas, devuelve `false` y deja las asignaciones vacías.

## Mostrar el retroceso

El primer intento entrega C1 y C3 a Leonardo, C2 a Rafael y C4 a Miguel. C5 pesa 14 y queda sin lugar. Esa situación exige cambiar decisiones; no demuestra que la misión sea imposible.

En los pasos 13 y 14 de la tabla se retiran C4 de Miguel y C3 de Leonardo. Después se prueba C3 con Rafael y Donatello. El reparto final es Leonardo: C1 y C5; Rafael: C2; Donatello: C3; Miguel: C4.

## Trabajarlo en Excel

Importa el CSV con **Datos → Desde texto/CSV**, codificación UTF-8 y separador **punto y coma**. Cada fila representa un intento o una entrega deshecha. El alumno completa la plantilla antes de comparar con el seguimiento resuelto.

## Completar el rescate

Cuando el reparto es válido, la parte c ordena con burbuja el primer camión en forma ascendente y el segundo en forma descendente. Después intercala sus nodos sin crear otros. La [guía completa del ejercicio](../../soluciones-actuales/04_listas_pilas_colas/enunciados/tortuninjas.md) muestra el ejemplo.
