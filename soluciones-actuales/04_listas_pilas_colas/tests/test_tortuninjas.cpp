// Las estructuras STL se usan solo en las pruebas, no en la solucion.
#define main mainEjemploTortuninjas
#include "../soluciones/2023_2_ex01_p01_tortuninjas.cpp"
#undef main

#include <algorithm>
#include <cassert>
#include <random>
#include <set>
#include <vector>

using Pesos = std::vector<std::vector<int>>;

Camion *crearCamiones(const Pesos &datos)
{
    Camion *camiones = new Camion[datos.size()];
    for (std::size_t i = 0; i < datos.size(); i++)
        for (int peso : datos[i])
            insertarFinal(camiones[i].artefactos, peso);
    return camiones;
}

std::vector<int> contenido(const Lista &lista)
{
    std::vector<int> salida;
    const Nodo *ultimo = nullptr;
    for (const Nodo *actual = lista.inicio; actual != nullptr; actual = actual->siguiente)
    {
        salida.push_back(actual->peso);
        ultimo = actual;
    }
    assert(ultimo == lista.fin);
    return salida;
}

std::set<const Nodo *> nodos(const Camion camiones[], int cantidad)
{
    std::set<const Nodo *> salida;
    for (int i = 0; i < cantidad; i++)
    {
        for (const Nodo *actual = camiones[i].artefactos.inicio;
             actual != nullptr; actual = actual->siguiente)
            assert(salida.insert(actual).second); // Tambien detecta ciclos y nodos compartidos.
    }
    return salida;
}

// Oraculo independiente: enumera todas las asignaciones mediante numeros en base 4.
bool existePorEnumeracion(const Pesos &datos, const long long capacidades[])
{
    std::vector<long long> pesos;
    int limite = 1;
    for (const auto &lista : datos)
    {
        long long total = 0;
        for (int peso : lista) total += peso;
        pesos.push_back(total);
        limite *= 4;
    }
    for (int alternativa = 0; alternativa < limite; alternativa++)
    {
        int codigo = alternativa;
        int cantidades[4] = {};
        long long cargas[4] = {};
        for (long long peso : pesos)
        {
            int ninja = codigo % 4;
            codigo /= 4;
            cantidades[ninja]++;
            cargas[ninja] += peso;
        }
        bool valido = true;
        for (int i = 0; i < 4; i++)
            if (cantidades[i] < 1 || cantidades[i] > 2 || cargas[i] > capacidades[i])
                valido = false;
        if (valido) return true;
    }
    return false;
}

void verificarCaso(const Pesos &datos, const long long capacidades[])
{
    const int cantidad = static_cast<int>(datos.size());
    Camion *camiones = crearCamiones(datos);
    const auto originales = nodos(camiones, cantidad);
    TortuNinja tortugas[4] = {{"L"}, {"R"}, {"D"}, {"M"}};
    for (int i = 0; i < 4; i++) tortugas[i].capacidad = capacidades[i];

    bool encontrado = buscarAsignacion(camiones, cantidad, tortugas, 0);
    assert(encontrado == existePorEnumeracion(datos, capacidades));
    // La busqueda solo decide el reparto: no debe tocar las listas.
    assert(nodos(camiones, cantidad) == originales);
    for (int i = 0; i < cantidad; i++)
        assert(contenido(camiones[i].artefactos) == datos[i]);
    if (encontrado)
    {
        std::vector<bool> asignados(cantidad, false);
        std::vector<std::vector<int>> esperados(4);
        for (int i = 0; i < 4; i++)
        {
            int primero = tortugas[i].primerCamion;
            int segundo = tortugas[i].segundoCamion;
            assert(primero >= 0 && primero < cantidad && !asignados[primero]);
            asignados[primero] = true;
            assert(tortugas[i].carga <= tortugas[i].capacidad);
            std::vector<int> izquierda = datos[primero];
            if (segundo == -1)
                esperados[i] = izquierda;
            else
            {
                assert(segundo >= 0 && segundo < cantidad && !asignados[segundo]);
                asignados[segundo] = true;
                std::vector<int> derecha = datos[segundo];
                std::sort(izquierda.begin(), izquierda.end());
                std::sort(derecha.rbegin(), derecha.rend());
                for (std::size_t j = 0; j < std::max(izquierda.size(), derecha.size()); j++)
                {
                    if (j < izquierda.size()) esperados[i].push_back(izquierda[j]);
                    if (j < derecha.size()) esperados[i].push_back(derecha[j]);
                }
            }
        }
        assert(std::all_of(asignados.begin(), asignados.end(), [](bool valor) { return valor; }));
        prepararRescate(camiones, tortugas);
        assert(nodos(camiones, cantidad) == originales);
        for (int i = 0; i < 4; i++)
        {
            const Lista &final = camiones[tortugas[i].primerCamion].artefactos;
            assert(contenido(final) == esperados[i]);
            assert(sumarPesos(final) == tortugas[i].carga);
            if (tortugas[i].segundoCamion != -1)
            {
                const Lista &absorbida = camiones[tortugas[i].segundoCamion].artefactos;
                assert(absorbida.inicio == nullptr && absorbida.fin == nullptr);
            }
        }
    }
    else
    {
        for (int i = 0; i < 4; i++)
            assert(tortugas[i].primerCamion == -1 && tortugas[i].segundoCamion == -1
                   && tortugas[i].carga == 0);
        for (int i = 0; i < cantidad; i++)
            assert(contenido(camiones[i].artefactos) == datos[i]);
    }
    liberarCamiones(camiones, cantidad);
}

void verificarIntercalado(const std::vector<int> &izquierda, const std::vector<int> &derecha)
{
    Pesos datos = {izquierda, derecha};
    Camion *camiones = crearCamiones(datos);
    const auto originales = nodos(camiones, 2);
    std::vector<int> esperado;
    for (std::size_t i = 0; i < std::max(izquierda.size(), derecha.size()); i++)
    {
        if (i < izquierda.size()) esperado.push_back(izquierda[i]);
        if (i < derecha.size()) esperado.push_back(derecha[i]);
    }
    intercalarListas(camiones[0].artefactos, camiones[1].artefactos);
    assert(contenido(camiones[0].artefactos) == esperado);
    assert(camiones[1].artefactos.inicio == nullptr && camiones[1].artefactos.fin == nullptr);
    assert(nodos(camiones, 2) == originales);
    liberarCamiones(camiones, 2);
}

void verificarValidador()
{
    TortuNinja tortugas[4] = {{"L"}, {"R"}, {"D"}, {"M"}};
    assert(!todosCamionesAsignados(tortugas, 5));
    tortugas[0].primerCamion = 0;
    tortugas[0].segundoCamion = 4;
    tortugas[1].primerCamion = 1;
    tortugas[2].primerCamion = 2;
    tortugas[3].primerCamion = 3;
    assert(todosCamionesAsignados(tortugas, 5));
    tortugas[3].segundoCamion = 0;
    assert(!todosCamionesAsignados(tortugas, 5));
    tortugas[3].segundoCamion = -1;
    tortugas[2].primerCamion = -1;
    assert(!todosCamionesAsignados(tortugas, 5));
}

int main()
{
    verificarValidador();
    long long capacidades[] = {34, 24, 12, 30};
    verificarCaso({{8,9}, {15,9}, {3,6}, {1,6,8,4,6}, {5,6,3}}, capacidades);
    // Si Leonardo toma los dos primeros camiones, el de peso 8 queda sin destino.
    // Hay solucion, pero exige deshacer decisiones: L=4+6, R=8, D=6, M=4.
    long long conRetroceso[] = {10, 8, 6, 4};
    verificarCaso({{4}, {4}, {6}, {8}, {6}}, conRetroceso);
    // Aunque todos pesen cero, los cuatro ninjas deben recibir algun camion.
    long long ceros[] = {0, 0, 0, 0};
    verificarCaso(Pesos(5), ceros);
    long long pequenas[] = {1, 1, 1, 1};
    verificarCaso({{2}, {2}, {2}, {2}, {2}}, pequenas);
    long long iguales[] = {2, 2, 2, 2};
    for (int n = 5; n <= 8; n++)
        verificarCaso(Pesos(n, std::vector<int>{1}), iguales);
    // La capacidad total no basta si un ninja no puede recibir ningun camion.
    long long sinParticipacion[] = {100, 100, 100, 0};
    verificarCaso({{1}, {1}, {1}, {1}, {1}}, sinParticipacion);
    long long grandes[] = {6000000000LL, 6000000000LL, 6000000000LL, 6000000000LL};
    verificarCaso({{2000000000, 2000000000}, {1}, {1}, {1}, {1}}, grandes);

    verificarIntercalado({}, {});
    verificarIntercalado({}, {6,5,3});
    verificarIntercalado({8,9}, {});
    verificarIntercalado({8,9}, {6,5,3});
    verificarIntercalado({1,2,3,4}, {9});

    std::mt19937 azar(20231014);
    for (int caso = 0; caso < 40; caso++)
    {
        Pesos datos(5 + caso % 4);
        for (auto &lista : datos)
        {
            int cantidad = static_cast<int>(azar() % 5);
            for (int i = 0; i < cantidad; i++)
                lista.push_back(1 + static_cast<int>(azar() % 10));
        }
        long long limites[4];
        for (long long &limite : limites) limite = static_cast<long long>(azar() % 50);
        verificarCaso(datos, limites);
    }
    std::cout << "TortuNinjas: reparto iterativo contra enumeracion, burbuja y nodos conservados.\n";
    return 0;
}
