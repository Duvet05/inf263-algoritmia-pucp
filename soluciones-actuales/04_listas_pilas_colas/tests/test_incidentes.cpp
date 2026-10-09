// Las estructuras auxiliares de este archivo pertenecen solo a las pruebas.
#define main mainEjemploIncidentes
#include "../soluciones/2023_2_ex01_p02_incidentes.cpp"
#undef main

#include <algorithm>
#include <cassert>
#include <map>
#include <random>
#include <vector>

using Registro = std::map<const Nodo *, int>;

std::vector<int> contenidoPila(const Pila &pila)
{
    std::vector<int> salida;
    for (const Nodo *actual = pila.cima; actual != nullptr; actual = actual->siguiente)
        salida.push_back(actual->codigo);
    assert(static_cast<int>(salida.size()) == pila.longitud);
    return salida;
}

std::vector<int> contenidoCola(const Cola &cola)
{
    std::vector<int> salida;
    const Nodo *ultimo = nullptr;
    for (const Nodo *actual = cola.inicio; actual != nullptr; actual = actual->siguiente)
    {
        salida.push_back(actual->codigo);
        ultimo = actual;
    }
    assert(ultimo == cola.fin);
    assert(static_cast<int>(salida.size()) == cola.longitud);
    return salida;
}

Registro registrar(const Cola &cola, const Pila &pila1, const Pila &pila2)
{
    Registro registro;
    for (const Nodo *actual = cola.inicio; actual != nullptr; actual = actual->siguiente)
        assert(registro.emplace(actual, actual->codigo).second);
    for (const Pila *pila : {&pila1, &pila2})
        for (const Nodo *actual = pila->cima; actual != nullptr; actual = actual->siguiente)
            assert(registro.emplace(actual, actual->codigo).second);
    return registro;
}

// Oraculo: ordenar una copia por numero de llegada y repartir por capacidad/impacto.
// Verifica que cada nodo conserve su codigo y aparezca en una sola estructura.
void verificarCaso(const std::vector<int> &antiguos, const std::vector<int> &recientes, int capacidad)
{
    Cola cola;
    Pila pila1, pila2;
    for (int codigo : antiguos)
    {
        if (codigo / 100 == 1) apilarInicial(pila1, codigo);
        else apilarInicial(pila2, codigo);
    }
    for (int codigo : recientes) encolarInicial(cola, codigo);
    Registro originales = registrar(cola, pila1, pila2);
    std::vector<int> ordenados = antiguos;
    ordenados.insert(ordenados.end(), recientes.begin(), recientes.end());
    std::sort(ordenados.begin(), ordenados.end(), [](int a, int b) { return a % 100 < b % 100; });
    int ocupados = std::min(capacidad, static_cast<int>(ordenados.size()));
    std::vector<int> esperadaCola(ordenados.begin(), ordenados.begin() + ocupados);
    std::vector<int> sobrantes(ordenados.begin() + ocupados, ordenados.end());
    std::vector<int> esperadaPila2(sobrantes.rbegin(), sobrantes.rend());

    assert(reinicia_cola(cola, capacidad, pila1, pila2));
    assert(contenidoCola(cola) == esperadaCola);
    assert(contenidoPila(pila1).empty());
    assert(contenidoPila(pila2) == esperadaPila2);
    assert(cola.longitud <= capacidad);
    assert(registrar(cola, pila1, pila2) == originales);

    reclasifica_pilas(pila1, pila2);
    std::vector<int> alto, muyAlto;
    for (int codigo : sobrantes)
    {
        if (codigo / 100 == 2) alto.push_back(codigo);
        else muyAlto.push_back(codigo);
    }
    assert(contenidoCola(cola) == esperadaCola);
    assert(contenidoPila(pila1) == alto);
    assert(contenidoPila(pila2) == muyAlto);
    assert(registrar(cola, pila1, pila2) == originales);
    destruirCola(cola);
    destruirPila(pila1);
    destruirPila(pila2);
}

int main()
{
    verificarCaso({101,102,105,203,204}, {206,107,208,109,210,211,112,113}, 8);
    verificarCaso({}, {}, 0);
    verificarCaso({101,202,103}, {}, 0);
    verificarCaso({101,202,103,204}, {105}, 1);
    verificarCaso({}, {101,202,103}, 5);
    verificarCaso({101,102,103}, {104,105,106}, 3);
    verificarCaso({201,202,203}, {204,205,206}, 3);

    std::mt19937 azar(20231014);
    for (int capacidad = 0; capacidad <= 12; capacidad++)
    {
        for (int cantidadAntiguos = 0; cantidadAntiguos <= 10; cantidadAntiguos++)
        {
            int cantidadRecientes = static_cast<int>(azar() % (capacidad + 1));
            std::vector<int> antiguos, recientes;
            for (int i = 1; i <= cantidadAntiguos + cantidadRecientes; i++)
            {
                int codigo = (azar() % 2 ? 100 : 200) + i;
                if (i <= cantidadAntiguos) antiguos.push_back(codigo);
                else recientes.push_back(codigo);
            }
            std::shuffle(antiguos.begin(), antiguos.end(), azar);
            verificarCaso(antiguos, recientes, capacidad);
        }
    }

    // Un parametro de capacidad invalido se rechaza sin modificar las estructuras.
    Cola cola;
    Pila pila1, pila2;
    encolarInicial(cola, 203);
    encolarInicial(cola, 104);
    apilarInicial(pila1, 101);
    apilarInicial(pila2, 202);
    Registro originales = registrar(cola, pila1, pila2);
    assert(!reinicia_cola(cola, 1, pila1, pila2));
    assert(!reinicia_cola(cola, -1, pila1, pila2));
    assert(contenidoCola(cola) == std::vector<int>({203,104}));
    assert(contenidoPila(pila1) == std::vector<int>({101}));
    assert(contenidoPila(pila2) == std::vector<int>({202}));
    assert(registrar(cola, pila1, pila2) == originales);
    destruirCola(cola);
    destruirPila(pila1);
    destruirPila(pila2);
    std::cout << "Incidentes: ejemplo, 150 escenarios y mismos nodos/codigos conservados.\n";
    return 0;
}
