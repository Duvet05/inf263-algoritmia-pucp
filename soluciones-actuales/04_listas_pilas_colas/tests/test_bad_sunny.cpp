#include <cassert>
#include <random>

#define main mainEjemploBadSunny
#include "../soluciones/2022_2_ex01_p02_bad_sunny.cpp"
#undef main

// Referencia O(n^2): para cada inicio, extiende el tramo manteniendo el minimo.
Desafinacion fuerzaBruta(const int frecuencias[], int n) {
    Desafinacion mejor;
    for (int inicio = 0; inicio < n; inicio++) {
        int minimo = frecuencias[inicio];
        for (int fin = inicio; fin < n; fin++) {
            if (frecuencias[fin] < minimo) minimo = frecuencias[fin];
            int duracion = fin - inicio + 1;
            if (esMejor(1LL * minimo * duracion, minimo, mejor)) {
                mejor.frecuencia = minimo;
                mejor.duracion = duracion;
                mejor.inicio = inicio;
                mejor.fin = fin;
            }
        }
    }
    return mejor;
}

int main() {
    int ejemplo[] = {1, 2, 1, 4, 5, 6, 4, 5, 2, 2, 1};
    Desafinacion d = buscarDesafinacion(ejemplo, 11);
    assert(d.frecuencia == 4 && d.duracion == 5 && d.inicio == 3 && d.fin == 7);
    corregir(ejemplo, d);
    const int corregidas[] = {1, 2, 1, 4, 4, 4, 4, 4, 2, 2, 1};
    for (int i = 0; i < 11; i++) assert(ejemplo[i] == corregidas[i]);

    Desafinacion vacio = buscarDesafinacion(ejemplo, 0);
    assert(vacio.frecuencia == 0 && vacio.duracion == 0);

    std::mt19937 azar(2022);
    for (int caso = 0; caso < 3000; caso++) {
        int n = static_cast<int>(azar() % 40);
        int frecuencias[40];
        for (int i = 0; i < n; i++) frecuencias[i] = static_cast<int>(azar() % 10);
        Desafinacion esperado = fuerzaBruta(frecuencias, n);
        Desafinacion obtenido = buscarDesafinacion(frecuencias, n);
        assert(obtenido.frecuencia == esperado.frecuencia);
        assert(obtenido.duracion == esperado.duracion);
        // El tramo devuelto debe tener esa frecuencia como minimo.
        for (int i = obtenido.inicio; i <= obtenido.fin; i++) assert(frecuencias[i] >= obtenido.frecuencia);
    }
    return 0;
}
