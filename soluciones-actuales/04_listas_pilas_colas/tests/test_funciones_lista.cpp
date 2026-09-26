#include <algorithm>
#include <cassert>
#include <climits>
#include <random>
#include <sstream>
#include <vector>
#include "../biblioteca/listas/FuncionesLista.h"

// Contrasta el contenido y los extremos con un contenedor independiente.
void verificar(const listas::Lista &lista, const std::vector<int> &esperado) {
    assert(listas::longitud(lista) == static_cast<int>(esperado.size()));
    assert(listas::esListaVacia(lista) == esperado.empty());
    const listas::Nodo *actual = lista.inicio;
    const listas::Nodo *ultimo = nullptr;
    for (int dato : esperado) {
        assert(actual != nullptr && actual->dato == dato);
        ultimo = actual;
        actual = actual->sig;
    }
    assert(actual == nullptr); // Detecta nodos sobrantes y ciclos.
    assert(lista.fin == ultimo);
    if (lista.fin != nullptr) assert(lista.fin->sig == nullptr);
    assert(listas::obtenerEnPosicion(lista, -1) == nullptr);
    assert(listas::obtenerEnPosicion(lista, lista.longitud) == nullptr);
}

void probarLimitesYTransferencia() {
    listas::Lista lista;
    listas::inicializar(lista);
    verificar(lista, {});
    assert(!listas::insertarEnPosicion(lista, -1, 8));
    assert(!listas::insertarEnPosicion(lista, INT_MAX, 8));
    assert(listas::extraerInicio(lista) == nullptr);
    assert(listas::extraerEnPosicion(lista, 0) == nullptr);
    assert(!listas::eliminarInicio(lista));
    assert(!listas::eliminarFinal(lista));
    assert(!listas::eliminarDato(lista, 8));
    listas::insertarNodoInicio(lista, nullptr);
    listas::insertarNodoFinal(lista, nullptr);
    listas::invertir(lista);
    verificar(lista, {});

    assert(listas::insertarEnPosicion(lista, 0, 8));
    listas::Nodo *unico = lista.inicio;
    listas::Nodo *extraido = listas::extraerEnPosicion(lista, 0);
    assert(extraido == unico && extraido->sig == nullptr);
    verificar(lista, {});
    listas::insertarNodoInicio(lista, extraido);
    assert(lista.inicio == unico && lista.fin == unico);
    listas::invertir(lista);
    verificar(lista, {8});
    assert(listas::eliminarFinal(lista));
    verificar(lista, {});

    listas::insertarFinal(lista, 1);
    listas::insertarFinal(lista, 2);
    listas::insertarFinal(lista, 2);
    listas::Nodo *primero = lista.inicio;
    listas::Nodo *segundo = primero->sig;
    listas::Nodo *tercero = lista.fin;
    assert(listas::buscar(lista, 2) == segundo);
    assert(listas::eliminarDato(lista, 2));
    verificar(lista, {1, 2});
    assert(listas::buscar(lista, 2) == tercero);
    extraido = listas::extraerEnPosicion(lista, 1);
    assert(extraido == tercero && extraido->sig == nullptr);
    assert(lista.fin == primero);

    listas::Lista otra;
    listas::insertarNodoFinal(otra, extraido);
    listas::concatenar(lista, otra);
    verificar(lista, {1, 2});
    verificar(otra, {});
    assert(lista.inicio == primero && lista.fin == tercero);
    listas::concatenar(lista, lista);
    listas::concatenar(lista, otra);
    verificar(lista, {1, 2});
    listas::concatenar(otra, lista);
    verificar(lista, {});
    verificar(otra, {1, 2});
    listas::invertir(otra);
    assert(otra.inicio == tercero && otra.fin == primero);
    verificar(otra, {2, 1});
    std::ostringstream salida;
    listas::imprimir(otra, salida);
    assert(salida.str() == "2 -> 1 -> nullptr\n");
    listas::destruir(otra);
    listas::destruir(otra);
    verificar(otra, {});
    listas::concatenar(lista, otra);
    verificar(lista, {});
    std::ostringstream vacia;
    listas::imprimir(lista, vacia);
    assert(vacia.str() == "nullptr\n");
    listas::insertarInicio(otra, 7); // Reutilizable despues de destruir.
    assert(listas::eliminarDato(otra, 7));
    verificar(otra, {});
}

void probarSecuencias() {
    std::mt19937 azar(2026);
    listas::Lista lista;
    std::vector<int> esperado;
    for (int paso = 0; paso < 5000; paso++) {
        int dato = static_cast<int>(azar() % 21) - 10;
        int posicion = static_cast<int>(azar() % (esperado.size() + 3)) - 1;
        bool existente = posicion >= 0 && posicion < static_cast<int>(esperado.size());
        switch (azar() % 10) {
        case 0:
            listas::insertarInicio(lista, dato);
            esperado.insert(esperado.begin(), dato);
            break;
        case 1:
            listas::insertarFinal(lista, dato);
            esperado.push_back(dato);
            break;
        case 2: {
            bool valida = posicion >= 0 && posicion <= static_cast<int>(esperado.size());
            assert(listas::insertarEnPosicion(lista, posicion, dato) == valida);
            if (valida) esperado.insert(esperado.begin() + posicion, dato);
            break;
        }
        case 3:
            assert(listas::eliminarEnPosicion(lista, posicion) == existente);
            if (existente) esperado.erase(esperado.begin() + posicion);
            break;
        case 4: {
            auto coincidencia = std::find(esperado.begin(), esperado.end(), dato);
            assert(listas::eliminarDato(lista, dato) == (coincidencia != esperado.end()));
            if (coincidencia != esperado.end()) esperado.erase(coincidencia);
            break;
        }
        case 5: {
            const listas::Nodo *anterior = listas::obtenerEnPosicion(lista, posicion);
            listas::Nodo *nodo = listas::extraerEnPosicion(lista, posicion);
            assert(nodo == anterior);
            if (existente) {
                assert(nodo != nullptr && nodo->sig == nullptr);
                int valor = esperado[posicion];
                esperado.erase(esperado.begin() + posicion);
                verificar(lista, esperado);
                if (azar() % 2 == 0) {
                    listas::insertarNodoInicio(lista, nodo);
                    esperado.insert(esperado.begin(), valor);
                } else {
                    listas::insertarNodoFinal(lista, nodo);
                    esperado.push_back(valor);
                }
            } else assert(nodo == nullptr);
            break;
        }
        case 6:
            listas::invertir(lista);
            std::reverse(esperado.begin(), esperado.end());
            break;
        case 7:
            assert(listas::eliminarInicio(lista) == !esperado.empty());
            if (!esperado.empty()) esperado.erase(esperado.begin());
            break;
        case 8:
            assert(listas::eliminarFinal(lista) == !esperado.empty());
            if (!esperado.empty()) esperado.pop_back();
            break;
        case 9: {
            listas::Lista otra;
            listas::insertarFinal(otra, dato);
            listas::Nodo *transferido = otra.inicio;
            listas::concatenar(lista, otra);
            esperado.push_back(dato);
            assert(lista.fin == transferido);
            verificar(otra, {});
            break;
        }
        }
        verificar(lista, esperado);
        auto coincidencia = std::find(esperado.begin(), esperado.end(), dato);
        const listas::Nodo *encontrado = listas::buscar(lista, dato);
        if (coincidencia == esperado.end()) assert(encontrado == nullptr);
        else {
            int indice = static_cast<int>(coincidencia - esperado.begin());
            assert(encontrado == listas::obtenerEnPosicion(lista, indice));
            assert(encontrado->dato == dato);
        }
    }
    listas::destruir(lista);
    verificar(lista, {});
}

int main() {
    probarLimitesYTransferencia();
    probarSecuencias();
}
