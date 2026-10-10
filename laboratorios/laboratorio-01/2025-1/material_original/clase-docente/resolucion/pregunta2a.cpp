#include <iostream>

using namespace std;

/*
 * Estrategia de fuerza bruta:
 * Una mascara binaria de 10 bits representa una combinacion de recursos.
 * Se prueban todas las mascaras no vacias. Para cada recurso seleccionado se
 * comprueba que todos los bits de sus dependencias tambien esten presentes.
 * Finalmente se muestran las combinaciones validas cuyo costo se encuentre
 * entre el 80% del presupuesto y el presupuesto completo.
 */
void listarPorPresupuesto(const int costos[], const int dependencias[],
                          int cantidadRecursos, int presupuesto) {
    int totalCombinaciones = 1 << cantidadRecursos;
    int costoMinimo = (presupuesto * 80 + 99) / 100;
    bool existeCombinacion = false;

    cout << "\nCombinaciones validas (Costo entre " << costoMinimo
         << " y " << presupuesto << " miles):\n";

    for (int mascara = 1; mascara < totalCombinaciones; mascara++) {
        int costoTotal = 0;
        bool dependenciasValidas = true;

        for (int recurso = 0; recurso < cantidadRecursos; recurso++) {
            if (mascara & (1 << recurso)) {
                costoTotal += costos[recurso];

                if ((mascara & dependencias[recurso]) !=
                    dependencias[recurso]) {
                    dependenciasValidas = false;
                }
            }
        }

        if (dependenciasValidas && costoTotal >= costoMinimo &&
            costoTotal <= presupuesto) {
            existeCombinacion = true;
            cout << "Combinacion " << mascara << ": Recursos:";

            for (int recurso = 0; recurso < cantidadRecursos; recurso++) {
                if (mascara & (1 << recurso)) {
                    cout << " R" << recurso + 1;
                }
            }

            cout << " | Costo: " << costoTotal << " miles\n";
        }
    }

    if (!existeCombinacion) {
        cout << "No se encontraron combinaciones que cumplan con lo "
                "solicitado.\n";
    }
}

/*
 * Inicializa los costos y las dependencias del enunciado, solicita el
 * presupuesto y ejecuta la enumeracion exhaustiva.
 */
int main() {
    const int cantidadRecursos = 10;
    int costos[cantidadRecursos] = {50, 40, 80, 70, 85,
                                    140, 55, 130, 30, 150};

    // Cada entero es una mascara con los predecesores requeridos.
    int dependencias[cantidadRecursos] = {
        0,                                  // R1
        0,                                  // R2
        0,                                  // R3
        1 << 0,                             // R4 requiere R1
        1 << 0,                             // R5 requiere R1
        (1 << 0) | (1 << 1),                // R6 requiere R1 y R2
        1 << 1,                             // R7 requiere R2
        (1 << 1) | (1 << 2),                // R8 requiere R2 y R3
        0,                                  // R9
        (1 << 0) | (1 << 1) | (1 << 4)      // R10 requiere R1, R2 y R5
    };

    int presupuesto;
    cout << "Ingrese el presupuesto (en miles de soles): ";

    if (!(cin >> presupuesto) || presupuesto < 0) {
        cout << "El presupuesto debe ser un entero no negativo.\n";
        return 1;
    }

    listarPorPresupuesto(costos, dependencias,
                         cantidadRecursos, presupuesto);

    return 0;
}
