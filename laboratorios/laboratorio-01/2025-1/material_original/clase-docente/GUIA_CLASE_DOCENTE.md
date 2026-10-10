# Guía docente — Laboratorio 1, 2025-1

## Objetivos de aprendizaje

Al finalizar la sesión, los alumnos deberían poder:

1. Modelar una decisión discreta como un número en otra base.
2. Enumerar exhaustivamente un espacio pequeño de soluciones.
3. Diferenciar una función objetivo de las restricciones de factibilidad.
4. Representar subconjuntos y dependencias mediante máscaras de bits.
5. Explicar el costo exponencial de la fuerza bruta.

## Propuesta de clase de 90 minutos

- **10 min — Modelado:** decisiones, restricciones y función objetivo.
- **20 min — Pregunta 1:** codificación en base 3 y criterio maximin.
- **20 min — Pregunta 2a:** subconjuntos binarios y banda del presupuesto.
- **15 min — Dependencias:** máscaras de requisitos y validación.
- **15 min — Pregunta 2b:** incorporación del nivel de seguridad.
- **10 min — Pruebas y cierre:** casos del PDF, complejidad y errores comunes.

## Pregunta 1: tablas y discos

### 1. Identificar las decisiones

Cada una de las seis tablas puede ir a uno de tres discos. Una solución puede
escribirse como un vector de seis decisiones:

```text
[disco(T1), disco(T2), ..., disco(T6)]
```

Existen `3 × 3 × 3 × 3 × 3 × 3 = 3^6 = 729` asignaciones.

### 2. Codificación en base 3

El programa recorre los códigos decimales de 0 a 728. Para cada tabla extrae
un dígito en base 3:

```cpp
int disco = codigoRestante % 3;
codigoRestante /= 3;
```

El código decimal 32 genera:

| Tabla | Valor antes | `% 3` | Disco humano |
|---|---:|---:|---:|
| T1 | 32 | 2 | 3 |
| T2 | 10 | 1 | 2 |
| T3 | 3 | 0 | 1 |
| T4 | 1 | 1 | 2 |
| T5 | 0 | 0 | 1 |
| T6 | 0 | 0 | 1 |

Esta codificación produce precisamente los conjuntos de la respuesta del PDF.

### 3. Separar factibilidad y optimalidad

Una asignación es factible si la demanda total de cada disco no supera su
velocidad inicial. Para una asignación factible se calcula:

```text
velocidad restante = velocidad inicial - demanda asignada
```

Después se toma la menor velocidad restante de los tres discos. El objetivo
es maximizar ese mínimo: esto es un criterio **maximin**.

Para la solución encontrada:

| Disco | Tablas | Demanda | Velocidad inicial | Restante |
|---|---|---:|---:|---:|
| 1 | 3, 5, 6 | 210 | 250 | 40 |
| 2 | 2, 4 | 150 | 200 | 50 |
| 3 | 1 | 150 | 200 | 50 |

El mínimo es 40 IOPs. Como se revisaron las 729 asignaciones y ninguna obtuvo
un mínimo mayor, la solución es óptima.

### Preguntas para los alumnos

- ¿Por qué no basta con maximizar la suma de velocidades restantes?
- ¿Qué significa que dos soluciones tengan el mismo mínimo?
- ¿Qué cambiaría si hubiera cuatro discos?
- ¿Por qué los discos 2 y 3 pueden intercambiarse sin alterar el valor óptimo?

## Pregunta 2: recursos de seguridad

### 1. Representar un subconjunto

Cada recurso solo tiene dos estados: seleccionado o no seleccionado. Por eso
una combinación se representa con diez bits y existen `2^10 = 1024`
posibilidades.

El bit `i` se consulta mediante:

```cpp
mascara & (1 << i)
```

El número de combinación mostrado por el PDF es el valor decimal de la
máscara. Por ejemplo:

```text
263 = 256 + 4 + 2 + 1
```

Por tanto, la combinación 263 contiene `R1`, `R2`, `R3` y `R9`.

### 2. Representar dependencias

Las dependencias también se almacenan como máscaras:

| Recurso | Dependencias | Máscara decimal |
|---|---|---:|
| R4 | R1 | 1 |
| R5 | R1 | 1 |
| R6 | R1, R2 | 3 |
| R7 | R2 | 2 |
| R8 | R2, R3 | 6 |
| R10 | R1, R2, R5 | 19 |

La condición siguiente verifica que estén presentes **todos** los bits
requeridos:

```cpp
(mascara & dependencias[recurso]) == dependencias[recurso]
```

### 3. Banda de presupuesto

El costo debe encontrarse entre el 80% y el 100% de `P`. Como los costos son
enteros, se calcula el menor entero que alcance el 80%:

```cpp
int costoMinimo = (P * 80 + 99) / 100;
```

La combinación es válida cuando:

```text
costoMinimo <= costoTotal <= P
```

### 4. Añadir el nivel de seguridad

La parte 2b conserva todos los filtros anteriores y añade:

```text
seguridadTotal >= seguridadMinima
```

Es importante acumular la seguridad únicamente para recursos cuyo bit esté
encendido.

## Errores comunes para discutir

- Probar solo combinaciones de dos o tres recursos en lugar de todos los
  subconjuntos.
- Usar `<` cuando el presupuesto permite exactamente `P`.
- Exigir `seguridad > mínimo` en vez de `>= mínimo`.
- Validar solo una dependencia cuando un recurso necesita dos o tres.
- Confundir el número decimal de la máscara con el número de recursos.
- Sumar el costo o la seguridad de un recurso no seleccionado.
- Guardar los datos como variables globales pese a la restricción del PDF.

## Demostración sugerida

1. Ejecutar 2a con `P=100` y relacionar las salidas 3, 4, 66 y 257 con sus
   representaciones binarias.
2. Proponer manualmente `R6` sin `R1` ni `R2` y mostrar por qué se rechaza.
3. Ejecutar 2b con `P=200` y seguridad mínima 400.
4. Subir la seguridad mínima hasta que ninguna combinación sea factible.
5. Cerrar comparando los crecimientos `3^6` y `2^10`.

## Complejidad

- Pregunta 1: `O(3^T × (T + D))`, con `T=6` tablas y `D=3` discos.
- Pregunta 2: `O(2^R × R)`, con `R=10` recursos.

La memoria adicional es lineal en la cantidad de tablas o recursos. La fuerza
bruta es adecuada aquí porque los espacios tienen solo 729 y 1024 candidatos;
su crecimiento exponencial sería problemático con entradas grandes.
