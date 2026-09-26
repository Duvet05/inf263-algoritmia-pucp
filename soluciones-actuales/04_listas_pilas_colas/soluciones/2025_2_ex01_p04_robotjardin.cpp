// Pregunta 4: ROBOTJARDIN 1.0.
// Solucion iterativa: un arreglo de alturas y una pila de indices.
// Tiempo O(n * m), memoria auxiliar O(m). La matriz se recibe como const.
#include <iostream>
using namespace std;

// Capacidad de columnas de las matrices de entrada; m indica cuantas se usan.
const int MAX_COLUMNAS = 100;

struct Nodo {
    int columna;
    Nodo *siguiente;
};

struct Pila {
    Nodo *tope = nullptr;
};

struct Rectangulo {
    long long area = 0;
    int filaInicio = -1;
    int filaFin = -1;
    int columnaInicio = -1;
    int columnaFin = -1;
};

// Consulta directa del tope: O(1).
bool esPilaVacia(const Pila &pila) {
    return pila.tope == nullptr;
}

// Consulta directa: llamar solamente cuando la pila no este vacia.
int cima(const Pila &pila) {
    return pila.tope->columna;
}

// Insercion al inicio de la pila enlazada: O(1), sin recursion.
void apilar(Pila &pila, int columna) {
    pila.tope = new Nodo{columna, pila.tope};
}

// Extraccion del tope: O(1). La pila debe contener un elemento.
int desapilar(Pila &pila) {
    Nodo *sale = pila.tope;
    int columna = sale->columna;
    pila.tope = sale->siguiente;
    delete sale;
    return columna;
}

// Se recorren las filas y se resuelve cada histograma con una pila.
// Cada indice se apila y desapila una sola vez por fila: O(n * m).
Rectangulo calcularAreaMaxima(const int jardin[][MAX_COLUMNAS], int n, int m) {
    Rectangulo mejor;
    if (n <= 0 || m <= 0 || m > MAX_COLUMNAS) return mejor;

    int *alturas = new int[m]{}; // Unico arreglo auxiliar, inicialmente en cero.
    Pila pila;                 // Unica pila auxiliar; guarda COLUMNAS.

    for (int fila = 0; fila < n; fila++) {
        // Altura = cantidad de unos consecutivos que terminan en esta fila.
        for (int col = 0; col < m; col++) {
            if (jardin[fila][col] == 1) alturas[col]++;
            else alturas[col] = 0;
        }

        // col == m representa el final: vacia la pila sin acceder a alturas[m].
        for (int col = 0; col <= m; col++) {
            int actual = col < m ? alturas[col] : 0;

            while (!esPilaVacia(pila) &&
                   (col == m || alturas[cima(pila)] > actual)) {
                int indice = desapilar(pila);
                int alto = alturas[indice];
                int izquierda = esPilaVacia(pila) ? 0 : cima(pila) + 1;
                int ancho = col - izquierda;
                long long area = 1LL * alto * ancho;

                if (area > mejor.area) {
                    mejor.area = area;
                    mejor.filaInicio = fila - alto + 1;
                    mejor.filaFin = fila;
                    mejor.columnaInicio = izquierda;
                    mejor.columnaFin = col - 1;
                }
            }

            // Las alturas de los indices en la pila quedan en orden no decreciente.
            if (col < m) apilar(pila, col);
        }
        // La pila termina vacia: todos sus nodos ya fueron liberados.
    }

    delete[] alturas;
    return mejor;
}

// Muestra el resultado. Las coordenadas se imprimen contando desde 1.
void mostrarResultado(const Rectangulo &rectangulo) {
    cout << "Area maxima: " << rectangulo.area << '\n';
    if (rectangulo.area > 0) {
        cout << "Filas: " << rectangulo.filaInicio + 1
             << " a " << rectangulo.filaFin + 1 << '\n';
        cout << "Columnas: " << rectangulo.columnaInicio + 1
             << " a " << rectangulo.columnaFin + 1 << '\n';
    }
}

// Ejecuta los dos ejemplos. Estas matrices son entradas, no memoria auxiliar.
int main() {
    const int jardin1[4][MAX_COLUMNAS] = {
        {1, 1, 1, 0},
        {1, 1, 1, 0},
        {1, 0, 1, 1},
        {1, 1, 0, 0}
    };

    const int jardin2[4][MAX_COLUMNAS] = {
        {1, 1, 1, 0, 0},
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 1, 0, 0, 0}
    };

    cout << "Ejemplo 1 (4 x 4)\n";
    mostrarResultado(calcularAreaMaxima(jardin1, 4, 4));
    cout << "\nEjemplo 2 (4 x 5)\n";
    mostrarResultado(calcularAreaMaxima(jardin2, 4, 5));
    return 0;
}
