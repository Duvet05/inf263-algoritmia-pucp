#include <algorithm>
#include <cassert>
#include <random>
#include <vector>

#define main mainEjemploCuadrigas
#include "../soluciones/2025_1_lab02_p01_cuadrigas.cpp"
#undef main

int main() {
    std::mt19937 azar(2025);
    for (int caso = 0; caso < 500; caso++) {
        Lista lista;
        inicializar(lista);
        int cantidad = caso % 30;
        std::vector<Nodo *> esperado;
        for (int i = 0; i < cantidad; i++) {
            insertarFinal(lista, static_cast<int>(azar() % 101) - 50, "Prueba", "Azul");
            esperado.push_back(lista.fin);
        }
        std::stable_partition(esperado.begin(), esperado.end(), [](const Nodo *nodo) {
            return nodo->dato.id % 2 == 0;
        });
        reordenar(lista);
        Nodo *actual = lista.inicio;
        for (Nodo *nodo : esperado) {
            assert(actual == nodo); // Mismos nodos, en el orden estable esperado.
            assert(std::strcmp(actual->dato.nombre, "Prueba") == 0);
            assert(std::strcmp(actual->dato.equipo, "Azul") == 0);
            actual = actual->sig;
        }
        assert(actual == nullptr);
        assert(lista.fin == (esperado.empty() ? nullptr : esperado.back()));
        destruir(lista);
        destruir(lista);
        assert(lista.inicio == nullptr && lista.fin == nullptr);
    }
}
