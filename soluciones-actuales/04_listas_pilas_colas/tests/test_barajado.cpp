#include <cassert>
#include <map>
#include <set>

#define main mainEjemploBarajado
#include "../soluciones/2026_1_lab02_p01_barajado.cpp"
#undef main

int main() {
    Baraja vacia;
    inicializar(vacia);
    barajar(vacia);
    assert(extraer_en_posicion(vacia, 0) == nullptr);
    destruir(vacia);
    assert(vacia.inicio == nullptr && vacia.fin == nullptr && vacia.longitud == 0);

    for (unsigned semilla = 0; semilla < 50; semilla++) {
        srand(semilla);
        Baraja baraja;
        crear_baraja(baraja);
        assert(baraja.longitud == 52);
        std::map<NodoBaraja *, Carta> originales;
        std::set<std::pair<int, char>> cartas;
        for (NodoBaraja *nodo = baraja.inicio; nodo != nullptr; nodo = nodo->sig) {
            assert(originales.emplace(nodo, nodo->carta).second);
            assert(cartas.emplace(nodo->carta.numero, nodo->carta.palo).second);
        }
        assert(originales.size() == 52 && cartas.size() == 52);
        assert(extraer_en_posicion(baraja, -1) == nullptr);
        assert(extraer_en_posicion(baraja, 52) == nullptr);
        NodoBaraja *ultimo = baraja.fin;
        assert(extraer_en_posicion(baraja, 51) == ultimo);
        assert(ultimo->sig == nullptr && baraja.fin->sig == nullptr);
        insertar_nodo_final(baraja, ultimo);
        for (int repeticion = 0; repeticion < 5; repeticion++) {
            barajar(baraja);
            std::set<NodoBaraja *> vistos;
            NodoBaraja *fin = nullptr;
            for (NodoBaraja *nodo = baraja.inicio; nodo != nullptr; nodo = nodo->sig) {
                assert(vistos.insert(nodo).second);
                assert(originales.count(nodo) == 1);
                assert(nodo->carta.numero == originales.at(nodo).numero);
                assert(nodo->carta.palo == originales.at(nodo).palo);
                fin = nodo;
            }
            assert(vistos.size() == 52 && baraja.longitud == 52);
            assert(baraja.fin == fin && fin->sig == nullptr);
        }
        destruir(baraja);
        destruir(baraja);
        assert(baraja.inicio == nullptr && baraja.fin == nullptr && baraja.longitud == 0);
    }
}
