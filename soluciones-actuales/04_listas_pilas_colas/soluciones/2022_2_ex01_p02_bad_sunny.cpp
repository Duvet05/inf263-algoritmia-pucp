// PUCP | Algoritmia | Primer Examen 2022-2 | Pregunta 2: Bad Sunny y DJ Robot.
//
// Se busca la frecuencia h que se mantiene durante la mayor cantidad de tiempo w,
// tomando como medida h * w: es el rectangulo de area maxima bajo el histograma
// de frecuencias. En el ejemplo, h = 4 entre los tiempos 4 y 8 (w = 5, area 20);
// las frecuencias de ese tramo que superan 4 se nivelan a 4.
//
// Solo se usa una pila (de indices) y el arreglo de entrada. Cada indice se apila
// y desapila una vez, asi que el algoritmo es O(n).
//
// Compilar desde la carpeta 04_listas_pilas_colas:
//   clang++ -std=c++17 -Wall -Wextra -Wpedantic soluciones/2022_2_ex01_p02_bad_sunny.cpp \
//       biblioteca/pilas/FuncionesPila.cpp biblioteca/listas/FuncionesLista.cpp -o /tmp/bad_sunny
//   /tmp/bad_sunny

#include <iomanip>
#include <iostream>
#include "../biblioteca/pilas/FuncionesPila.h"

using namespace std;

struct Desafinacion {
    int frecuencia = 0; // Frecuencia nivelada (altura del rectangulo).
    int duracion = 0;   // Cantidad de tiempos (ancho del rectangulo).
    int inicio = -1;    // Primer indice del tramo, desde 0.
    int fin = -1;       // Ultimo indice del tramo, desde 0.
};

// Criterio: mayor frecuencia * duracion; ante empate, la frecuencia mas alta.
bool esMejor(long long area, int frecuencia, const Desafinacion &actual) {
    long long areaActual = 1LL * actual.frecuencia * actual.duracion;
    return area > areaActual || (area == areaActual && frecuencia > actual.frecuencia);
}

// La pila guarda indices con frecuencias crecientes desde la base. Cuando llega
// una frecuencia menor o igual, cada indice desapilado ya conoce hasta donde se
// extiende su frecuencia: entre el nuevo tope (exclusivo) y i (exclusivo).
// El indice n actua como centinela de frecuencia 0 para vaciar la pila.
Desafinacion buscarDesafinacion(const int frecuencias[], int n) {
    Desafinacion mejor;
    pilas::Pila pila;
    pilas::inicializar(pila);
    for (int i = 0; i <= n; i++) {
        int actual = (i < n) ? frecuencias[i] : 0;
        while (!pilas::esPilaVacia(pila) && frecuencias[*pilas::cima(pila)] >= actual) {
            int indice = 0;
            pilas::desapilar(pila, indice);
            int frecuencia = frecuencias[indice];
            int inicio = pilas::esPilaVacia(pila) ? 0 : *pilas::cima(pila) + 1;
            int duracion = i - inicio;
            if (esMejor(1LL * frecuencia * duracion, frecuencia, mejor)) {
                mejor.frecuencia = frecuencia;
                mejor.duracion = duracion;
                mejor.inicio = inicio;
                mejor.fin = i - 1;
            }
        }
        if (i < n) pilas::apilar(pila, i);
    }
    pilas::destruir(pila);
    return mejor;
}

// Nivela en el mismo arreglo las frecuencias del tramo que superan la encontrada.
void corregir(int frecuencias[], const Desafinacion &desafinacion) {
    for (int i = desafinacion.inicio; i <= desafinacion.fin; i++) {
        if (frecuencias[i] > desafinacion.frecuencia) frecuencias[i] = desafinacion.frecuencia;
    }
}

const int MAX_TIEMPOS = 64;

void procesar(int frecuencias[], int n) {
    if (n > MAX_TIEMPOS) n = MAX_TIEMPOS; // Solo limita la tabla de este ejemplo.
    int originales[MAX_TIEMPOS];
    for (int i = 0; i < n; i++) originales[i] = frecuencias[i];

    Desafinacion desafinacion = buscarDesafinacion(frecuencias, n);
    corregir(frecuencias, desafinacion);

    cout << setw(6) << "Tiempo" << setw(12) << "Original" << setw(12) << "Corregida" << '\n';
    for (int i = 0; i < n; i++) {
        cout << setw(6) << i + 1 << setw(12) << originales[i] << setw(12) << frecuencias[i] << '\n';
    }
    cout << "Frecuencia maxima = " << desafinacion.frecuencia
         << " Duracion = " << desafinacion.duracion;
    if (desafinacion.duracion > 0) {
        cout << " (tiempos " << desafinacion.inicio + 1 << " a " << desafinacion.fin + 1 << ")";
    }
    cout << "\n\n";
}

int main() {
    int ejemplo[] = {1, 2, 1, 4, 5, 6, 4, 5, 2, 2, 1};
    procesar(ejemplo, sizeof(ejemplo) / sizeof(ejemplo[0]));

    // Un pico alto y corto pierde frente a un tramo mas bajo y largo: 3 * 6 > 9 * 1.
    int picoCorto[] = {3, 3, 9, 3, 3, 3, 1};
    procesar(picoCorto, sizeof(picoCorto) / sizeof(picoCorto[0]));
    return 0;
}
