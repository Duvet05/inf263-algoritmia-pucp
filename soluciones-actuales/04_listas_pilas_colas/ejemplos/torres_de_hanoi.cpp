// Torres de Hanoi con tres pilas enlazadas.
//
// Cada torre es una pila: la cima es el disco mas pequeno visible. Mover un
// disco desapila su nodo de una torre y lo apila en otra, sin new ni delete.
// Se resuelve de dos formas y ambas hacen 2^n - 1 movimientos:
//   - Recursiva: mover n-1 discos al auxiliar, el mayor al destino y
//     luego los n-1 encima.
//   - Iterativa: alternar entre tres pares de torres, haciendo en cada par
//     el unico movimiento valido.
//
// Compilar desde la carpeta 04_listas_pilas_colas:
//   clang++ -std=c++17 -Wall -Wextra -Wpedantic ejemplos/torres_de_hanoi.cpp \
//       biblioteca/pilas/FuncionesPila.cpp biblioteca/listas/FuncionesLista.cpp -o /tmp/hanoi
//   /tmp/hanoi        (3 discos por defecto)
//   /tmp/hanoi 4      (otra cantidad de discos, entre 0 y 20)

#include <cstdlib>
#include <initializer_list>
#include <iostream>
#include <utility>
#include "../biblioteca/pilas/FuncionesPila.h"

using namespace std;

const int TORRES = 3;
const int MAX_DISCOS = 20;
const int MAX_DISCOS_CON_PASOS = 6; // 63 movimientos; mas ya no se lee bien.

struct Torre {
    char nombre;
    pilas::Pila discos;
};

struct Juego {
    Torre torres[TORRES];
    long long movimientos = 0;
    bool mostrarPasos = false;
};

enum class Metodo { Recursivo, Iterativo };

const char *nombreMetodo(Metodo metodo) {
    return metodo == Metodo::Recursivo ? "recursivo" : "iterativo";
}

long long movimientosMinimos(int n) {
    return (1LL << n) - 1;
}

// Coloca n discos en A: el n abajo y el 1 en la cima.
void inicializarJuego(Juego &juego, int n, bool mostrarPasos) {
    const char nombres[TORRES] = {'A', 'B', 'C'};
    for (int i = 0; i < TORRES; i++) {
        juego.torres[i].nombre = nombres[i];
        pilas::inicializar(juego.torres[i].discos);
    }
    for (int disco = n; disco >= 1; disco--) pilas::apilar(juego.torres[0].discos, disco);
    juego.movimientos = 0;
    juego.mostrarPasos = mostrarPasos;
}

void liberarJuego(Juego &juego) {
    for (int i = 0; i < TORRES; i++) pilas::destruir(juego.torres[i].discos);
}

void imprimirTorres(const Juego &juego) {
    for (int i = 0; i < TORRES; i++) {
        cout << "  " << juego.torres[i].nombre << ':';
        pilas::imprimir(juego.torres[i].discos);
        cout << '\n';
    }
}

// Regla del juego: el origen tiene discos y no se pone un disco sobre otro menor.
bool puedeMover(const Torre &origen, const Torre &destino) {
    const pilas::Elemento *arriba = pilas::cima(origen.discos);
    const pilas::Elemento *debajo = pilas::cima(destino.discos);
    return arriba != nullptr && (debajo == nullptr || *arriba < *debajo);
}

bool moverDisco(Juego &juego, Torre &origen, Torre &destino) {
    if (!puedeMover(origen, destino)) {
        cerr << "Movimiento invalido de " << origen.nombre << " a " << destino.nombre << '\n';
        return false;
    }
    pilas::Nodo *disco = pilas::desapilarNodo(origen.discos);
    pilas::apilarNodo(destino.discos, disco);
    juego.movimientos++;
    if (juego.mostrarPasos) {
        cout << juego.movimientos << ". Mover disco " << disco->dato << " de "
             << origen.nombre << " a " << destino.nombre << '\n';
        imprimirTorres(juego);
    }
    return true;
}

// T(n) = 2T(n-1) + 1  =>  2^n - 1 movimientos.
bool hanoiRecursivo(Juego &juego, int n, Torre &origen, Torre &auxiliar, Torre &destino) {
    if (n == 0) return true;
    return hanoiRecursivo(juego, n - 1, origen, destino, auxiliar)
        && moverDisco(juego, origen, destino)
        && hanoiRecursivo(juego, n - 1, auxiliar, origen, destino);
}

// Entre dos torres con algun disco solo hay un movimiento valido: el disco menor
// de las dos cimas pasa a la otra torre.
bool moverEntre(Juego &juego, Torre &x, Torre &y) {
    if (puedeMover(x, y)) return moverDisco(juego, x, y);
    return moverDisco(juego, y, x);
}

// Ciclo de pares: (origen, destino), (origen, auxiliar), (auxiliar, destino).
// Con n par se intercambian destino y auxiliar para terminar en el destino.
bool hanoiIterativo(Juego &juego, int n, Torre &origen, Torre &auxiliar, Torre &destino) {
    Torre *aux = &auxiliar;
    Torre *dest = &destino;
    if (n % 2 == 0) swap(aux, dest);
    long long total = movimientosMinimos(n);
    for (long long paso = 1; paso <= total; paso++) {
        bool valido;
        if (paso % 3 == 1) valido = moverEntre(juego, origen, *dest);
        else if (paso % 3 == 2) valido = moverEntre(juego, origen, *aux);
        else valido = moverEntre(juego, *aux, *dest);
        if (!valido) return false;
    }
    return true;
}

bool resolver(Juego &juego, int n, Metodo metodo) {
    Torre &a = juego.torres[0];
    Torre &b = juego.torres[1];
    Torre &c = juego.torres[2];
    if (metodo == Metodo::Recursivo) return hanoiRecursivo(juego, n, a, b, c);
    return hanoiIterativo(juego, n, a, b, c);
}

// Desde la cima deben aparecer 1, 2, ..., n.
bool torreCompleta(const Torre &torre, int n) {
    if (pilas::altura(torre.discos) != n) return false;
    const pilas::Nodo *actual = torre.discos.lista.inicio;
    for (int esperado = 1; esperado <= n; esperado++, actual = actual->sig) {
        if (actual->dato != esperado) return false;
    }
    return true;
}

bool verificar(int n, Metodo metodo) {
    Juego juego;
    inicializarJuego(juego, n, false);
    bool correcto = resolver(juego, n, metodo)
        && juego.movimientos == movimientosMinimos(n)
        && pilas::esPilaVacia(juego.torres[0].discos)
        && pilas::esPilaVacia(juego.torres[1].discos)
        && torreCompleta(juego.torres[2], n);
    liberarJuego(juego);
    return correcto;
}

int main(int argc, char *argv[]) {
    int n = 3;
    if (argc > 1) {
        char *fin = nullptr;
        long leido = strtol(argv[1], &fin, 10);
        if (*fin != '\0' || leido < 0 || leido > MAX_DISCOS) {
            cerr << "Uso: " << argv[0] << " [discos entre 0 y " << MAX_DISCOS << "]\n";
            return 2;
        }
        n = static_cast<int>(leido);
    }

    for (Metodo metodo : {Metodo::Recursivo, Metodo::Iterativo}) {
        Juego juego;
        inicializarJuego(juego, n, n <= MAX_DISCOS_CON_PASOS);
        cout << "=== Hanoi " << nombreMetodo(metodo) << " con " << n << " discos ===\n";
        cout << "Estado inicial:\n";
        imprimirTorres(juego);
        if (!resolver(juego, n, metodo)) {
            liberarJuego(juego);
            return 1;
        }
        if (!juego.mostrarPasos) {
            cout << "Estado final:\n";
            imprimirTorres(juego);
        }
        cout << "Total: " << juego.movimientos << " movimientos (2^" << n << " - 1 = "
             << movimientosMinimos(n) << ")\n\n";
        liberarJuego(juego);
    }

    const int MAX_VERIFICADO = 12;
    bool todoCorrecto = true;
    for (int discos = 0; discos <= MAX_VERIFICADO; discos++) {
        for (Metodo metodo : {Metodo::Recursivo, Metodo::Iterativo}) {
            if (!verificar(discos, metodo)) {
                cout << "Falla el metodo " << nombreMetodo(metodo) << " con " << discos << " discos\n";
                todoCorrecto = false;
            }
        }
    }
    if (todoCorrecto) {
        cout << "Verificacion de 0 a " << MAX_VERIFICADO << " discos: ambos metodos correctos\n";
    }
    return todoCorrecto ? 0 : 1;
}
