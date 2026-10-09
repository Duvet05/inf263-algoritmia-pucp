// Bad Sunny (Examen 1 2022-2, P2) con una pila enlazada propia, sin lista.
// Compilar: clang++ -std=c++17 bad_sunny_pila_simple.cpp -o bad_sunny

#include <iomanip>
#include <iostream>

using namespace std;

struct Desafinacion {
    int inicio;
    int fin;
    int frecuencia;
    int duracion;
};

// ======================= Biblioteca de pila =======================

struct Nodo {
    Nodo *abajo;     // El nodo que queda debajo en la pila.
    int frecuencia;
    int indice;      // Posición de esta frecuencia en el arreglo.
};

struct Pila {
    Nodo *cima;      // nullptr cuando la pila está vacía.
};

void construirPila(Pila &pila) {
    pila.cima = nullptr;
}

bool esPilaVacia(const Pila &pila) {
    return pila.cima == nullptr;
}

void apilar(Pila &pila, int frecuencia, int indice) {
    Nodo *nuevo = new Nodo;
    nuevo->frecuencia = frecuencia;
    nuevo->indice = indice;
    nuevo->abajo = pila.cima;    // El nuevo apunta a la cima anterior...
    pila.cima = nuevo;           // ...y pasa a ser la nueva cima.
}

// Saca la cima y devuelve una copia de sus datos.
// Precondición: la pila no está vacía.
Nodo desapilar(Pila &pila) {
    Nodo *sale = pila.cima;
    Nodo copia = *sale;
    copia.abajo = nullptr;
    pila.cima = sale->abajo;     // La cima baja un nivel.
    delete sale;
    return copia;
}

void destruirPila(Pila &pila) {
    while (!esPilaVacia(pila)) desapilar(pila);
}

// ========================== Bad Sunny ==========================

Desafinacion buscarDesafinacion(int frecuencias[], int n) {
    Desafinacion mejor = {-1, -1, 0, 0};
    Pila pila;
    construirPila(pila);

    for (int i = 0; i <= n; i++) {
        // Centinela: después del último dato entra un 0 que vacía la pila.
        int actual = (i < n) ? frecuencias[i] : 0;

        // Todo lo que sea >= actual queda cortado por la derecha.
        while (!esPilaVacia(pila) && pila.cima->frecuencia >= actual) {
            Nodo sale = desapilar(pila);
            // Pared izquierda: el nodo que quedó debajo, más 1.
            int inicio = esPilaVacia(pila) ? 0 : pila.cima->indice + 1;
            int duracion = i - inicio;
            if (sale.frecuencia * duracion > mejor.frecuencia * mejor.duracion) {
                mejor.frecuencia = sale.frecuencia;
                mejor.duracion = duracion;
                mejor.inicio = inicio;
                mejor.fin = i - 1;
            }
        }
        if (i < n) apilar(pila, actual, i);
    }
    // No hace falta destruir: el centinela dejó la pila vacía.
    return mejor;
}

void corregir(int frecuencias[], const Desafinacion &d) {
    for (int i = d.inicio; i <= d.fin; i++) {
        if (frecuencias[i] > d.frecuencia) frecuencias[i] = d.frecuencia;
    }
}

int main() {
    const int n = 11;
    int frecuencias[n] = {1, 2, 1, 4, 5, 6, 4, 5, 2, 2, 1};
    int originales[n];
    for (int i = 0; i < n; i++) originales[i] = frecuencias[i];

    Desafinacion d = buscarDesafinacion(frecuencias, n);
    corregir(frecuencias, d);

    cout << setw(6) << "Tiempo" << setw(12) << "Original" << setw(12) << "Corregida" << '\n';
    for (int i = 0; i < n; i++) {
        cout << setw(6) << i + 1 << setw(12) << originales[i] << setw(12) << frecuencias[i] << '\n';
    }
    cout << "Frecuencia maxima = " << d.frecuencia << " Duracion = " << d.duracion << '\n';
    return 0;
}
