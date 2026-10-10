#include <iostream>

using namespace std;

/*
 * Estrategia de fuerza bruta:
 * Se enumeran las 2^10 combinaciones mediante mascaras binarias. Cada
 * combinacion debe respetar todas las dependencias, gastar entre el 80% y el
 * 100% del presupuesto y alcanzar el nivel minimo de seguridad solicitado.
 * Todas las combinaciones que superan simultaneamente los tres filtros se
 * imprimen junto con sus totales.
 */
void listarPorPresupuestoYSeguridad(const int costos[],
                                    const int nivelesSeguridad[],
                                    const int dependencias[],
                                    int cantidadRecursos, int presupuesto,
                                    int seguridadMinima) {
    int totalCombinaciones = 1 << cantidadRecursos;
    int costoMinimo = (presupuesto * 80 + 99) / 100;
    bool existeCombinacion = false;

    cout << "\nCombinaciones validas (Costo entre " << costoMinimo
         << " y " << presupuesto << " miles y Nivel de seguridad >= "
         << seguridadMinima << "):\n";

    for (int mascara = 1; mascara < totalCombinaciones; mascara++) {
        int costoTotal = 0;
        int seguridadTotal = 0;
        bool dependenciasValidas = true;

        for (int recurso = 0; recurso < cantidadRecursos; recurso++) {
            if (mascara & (1 << recurso)) {
                costoTotal += costos[recurso];
                seguridadTotal += nivelesSeguridad[recurso];

                if ((mascara & dependencias[recurso]) !=
                    dependencias[recurso]) {
                    dependenciasValidas = false;
                }
            }
        }

        if (dependenciasValidas && costoTotal >= costoMinimo &&
            costoTotal <= presupuesto &&
            seguridadTotal >= seguridadMinima) {
            existeCombinacion = true;
            cout << "Combinacion " << mascara << ": Recursos:";

            for (int recurso = 0; recurso < cantidadRecursos; recurso++) {
                if (mascara & (1 << recurso)) {
                    cout << " R" << recurso + 1;
                }
            }

            cout << " | Costo: " << costoTotal << " miles"
                 << " | Nivel de Seguridad: " << seguridadTotal << '\n';
        }
    }

    if (!existeCombinacion) {
        cout << "No se encontraron combinaciones que cumplan con lo "
                "solicitado.\n";
    }
}

/*
 * Inicializa los datos de los diez recursos, solicita presupuesto y nivel
 * minimo de seguridad, y ejecuta la busqueda exhaustiva.
 */
int main() {
    const int cantidadRecursos = 10;
    int costos[cantidadRecursos] = {50, 40, 80, 70, 85,
                                    140, 55, 130, 30, 150};
    int nivelesSeguridad[cantidadRecursos] = {
        120, 110, 140, 130, 160, 250, 100, 240, 90, 300
    };

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
    int seguridadMinima;

    cout << "Ingrese el presupuesto (en miles de soles): ";
    if (!(cin >> presupuesto) || presupuesto < 0) {
        cout << "El presupuesto debe ser un entero no negativo.\n";
        return 1;
    }

    cout << "Ingrese el nivel de seguridad minimo requerido: ";
    if (!(cin >> seguridadMinima) || seguridadMinima < 0) {
        cout << "El nivel minimo debe ser un entero no negativo.\n";
        return 1;
    }

    listarPorPresupuestoYSeguridad(costos, nivelesSeguridad, dependencias,
                                   cantidadRecursos, presupuesto,
                                   seguridadMinima);

    return 0;
}
