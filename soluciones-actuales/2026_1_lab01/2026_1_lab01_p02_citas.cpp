#include <iostream>

using namespace std;

/*
 * Estrategia de fuerza bruta:
 * Cada combinacion se representa como un numero en base 4. Cada digito
 * indica que un diente no se atiende (0) o se asigna a una de las citas
 * (1, 2 o 3). Se enumeran las 4^8 combinaciones mediante iteraciones y se
 * conserva la asignacion valida que produzca la mayor ganancia.
 *
 * No se usan variables globales. El arreglo plan guarda 0 si el diente no
 * se atiende y 1, 2 o 3 segun la cita elegida.
 */
void planificarFuerzaBruta(int numeroDientes,
                           const int tipos[], const int caries[],
                           const int duracionPorTipo[],
                           const int gananciaPorTipo[],
                           const int limites[], int &mejorGanancia,
                           int mejorPlan[]) {
    const int opcionesPorDiente = 4;
    int totalCombinaciones = 1;

    for (int i = 0; i < numeroDientes; i++) {
        totalCombinaciones *= opcionesPorDiente;
    }

    for (int codigo = 0; codigo < totalCombinaciones; codigo++) {
        int planActual[8] = {};
        int tiemposCitas[3] = {};
        int gananciaActual = 0;
        int numeroBase4 = codigo;
        bool planValido = true;

        for (int diente = 0; diente < numeroDientes; diente++) {
            int cita = numeroBase4 % opcionesPorDiente; // 0, 1 ,2 ,3
            numeroBase4 /= opcionesPorDiente;

            // Los dientes sin caries no requieren una cita.
            if (caries[diente] == 0) {
                planActual[diente] = 0;
                continue;
            }

            planActual[diente] = cita;

            if (cita != 0) {
                int indiceTipo = tipos[diente] - 1;
                int tiempoDiente =
                    caries[diente] * duracionPorTipo[indiceTipo];

                tiemposCitas[cita - 1] += tiempoDiente;

                if (tiemposCitas[cita - 1] > limites[cita - 1]) {
                    planValido = false;
                    break;
                }

                gananciaActual +=
                    caries[diente] * gananciaPorTipo[indiceTipo];
            }
        }

        if (planValido && gananciaActual > mejorGanancia) {
            mejorGanancia = gananciaActual;

            for (int diente = 0; diente < numeroDientes; diente++) {
                mejorPlan[diente] = planActual[diente];
            }
        }
    }
}

/*
 * Inicializa las tablas proporcionadas en el enunciado, ejecuta la busqueda
 * exhaustiva y muestra los dientes asignados y el tiempo usado en cada cita.
 */
int main() {
    const int numeroDientes = 8;
    const int numeroCitas = 3;

    int tipos[numeroDientes] = {1, 1, 2, 3, 3, 4, 4, 4};
    int caries[numeroDientes] = {3, 1, 0, 1, 2, 1, 2, 3};
    int duracionPorTipo[4] = {5, 7, 10, 12};
    int gananciaPorTipo[4] = {20, 30, 35, 42};
    int limites[numeroCitas] = {60, 45, 50};

    int mejorPlan[numeroDientes] = {};
    int mejorGanancia = -1;

    planificarFuerzaBruta(numeroDientes, tipos, caries,
                          duracionPorTipo, gananciaPorTipo, limites,
                          mejorGanancia, mejorPlan);

    int tiemposMejorPlan[numeroCitas] = {};

    for (int cita = 1; cita <= numeroCitas; cita++) {
        for (int diente = 0; diente < numeroDientes; diente++) {
            if (mejorPlan[diente] == cita) {
                int indiceTipo = tipos[diente] - 1;
                tiemposMejorPlan[cita - 1] +=
                    caries[diente] * duracionPorTipo[indiceTipo];
                cout << "Cita: " << cita
                     << " Diente: " << diente + 1 << '\n';
            }
        }
        cout << "Tiempo usado: " << tiemposMejorPlan[cita - 1]
             << "/" << limites[cita - 1] << " minutos\n\n";
    }

    cout << "La ganancia maxima es: " << mejorGanancia << '\n';

    return 0;
}
