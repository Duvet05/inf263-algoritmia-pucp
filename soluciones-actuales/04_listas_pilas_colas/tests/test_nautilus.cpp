// Las estructuras auxiliares de este archivo pertenecen solo a las pruebas.
#define main mainEjemploNautilus
#include "../soluciones/2024_1_ex01_p02_nautilus.cpp"
#undef main

#include <cassert>
#include <sstream>
#include <string>
#include <vector>

std::string ejecutarCaso(const std::string &ordenes) {
    std::ostringstream salida;
    std::streambuf *anterior = std::cout.rdbuf(salida.rdbuf());
    generarMovimientos(ordenes.data(), static_cast<int>(ordenes.size()));
    std::cout.rdbuf(anterior);
    return salida.str();
}

// Verifica el contrato: n + 1 niveles distintos en 1..n + 1
// y cada movimiento satisface exactamente su orden de subida o bajada.
void verificarCaso(const std::string &ordenes) {
    const std::string original = ordenes;
    const int n = static_cast<int>(ordenes.size());
    std::istringstream salida(ejecutarCaso(ordenes));
    std::vector<bool> visitados(n + 2, false);
    int anterior = 0;
    for (int i = 0; i <= n; i++) {
        int nivel = 0;
        assert(salida >> nivel);
        assert(nivel >= 1 && nivel <= n + 1);
        assert(!visitados[nivel]);
        visitados[nivel] = true;
        if (i > 0) {
            if (ordenes[i - 1] == 'S') assert(anterior < nivel);
            else assert(anterior > nivel);
        }
        anterior = nivel;
    }
    int extra = 0;
    assert(!(salida >> extra));
    assert(ordenes == original);
}

int main() {
    assert(ejecutarCaso("SSSBS") == "1 2 3 5 4 6\n");
    assert(ejecutarCaso("BBS") == "3 2 1 4\n");
    assert(ejecutarCaso("SBSBBSS") == "1 3 2 6 5 4 7 8\n");
    assert(ejecutarCaso("") == "1\n");
    assert(ejecutarCaso("S") == "1 2\n");
    assert(ejecutarCaso("B") == "2 1\n");

    // Todas las combinaciones hasta 9 ordenes: 1023 casos, incluido el vacio.
    for (int n = 0; n <= 9; n++) {
        for (int mascara = 0; mascara < (1 << n); mascara++) {
            std::string ordenes(n, 'B');
            for (int i = 0; i < n; i++) {
                if (mascara & (1 << i)) ordenes[i] = 'S';
            }
            verificarCaso(ordenes);
        }
    }

    // Extremos largos: pila casi siempre vacia y pila con 10001 nodos.
    verificarCaso(std::string(10000, 'S'));
    verificarCaso(std::string(10000, 'B'));
    std::cout << "Nautilus: ejemplos, 1023 combinaciones y dos casos largos correctos.\n";
    return 0;
}
