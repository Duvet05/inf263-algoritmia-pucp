#include <iostream>
#include <climits>

using namespace std;

/*
 * Estrategia de fuerza bruta:
 * Cada tabla puede asignarse a cualquiera de los tres discos. Un numero en
 * base 3 representa una asignacion completa: cada digito indica el disco de
 * una tabla. Se prueban las 3^6 posibilidades y, para cada asignacion valida,
 * se calcula la menor velocidad restante del grupo. Se conserva la solucion
 * cuyo minimo sea el mayor de todos (criterio maximin).
 */
void buscarAsignacionOptima(const int demandaTablas[], int cantidadTablas,
                            const int velocidadDiscos[], int cantidadDiscos,
                            int asignacionActual[], int mejorAsignacion[],
                            int &mejorVelocidadMinima,
                            int &combinacionesEvaluadas) {
    int totalCombinaciones = 1;

    for (int tabla = 0; tabla < cantidadTablas; tabla++) {
        totalCombinaciones *= cantidadDiscos;
    }

    for (int codigo = 0; codigo < totalCombinaciones; codigo++) {
        int demandaAsignada[3] = {};
        int codigoRestante = codigo;
        bool asignacionValida = true;
        combinacionesEvaluadas++;

        for (int tabla = 0; tabla < cantidadTablas; tabla++) {
            int disco = codigoRestante % cantidadDiscos;
            codigoRestante /= cantidadDiscos;

            asignacionActual[tabla] = disco;
            demandaAsignada[disco] += demandaTablas[tabla];

            if (demandaAsignada[disco] > velocidadDiscos[disco]) {
                asignacionValida = false;
                break;
            }
        }

        if (!asignacionValida) {
            continue;
        }

        int velocidadMinima = INT_MAX;

        for (int disco = 0; disco < cantidadDiscos; disco++) {
            int velocidadRestante =
                velocidadDiscos[disco] - demandaAsignada[disco];

            if (velocidadRestante < velocidadMinima) {
                velocidadMinima = velocidadRestante;
            }
        }

        if (velocidadMinima > mejorVelocidadMinima) {
            mejorVelocidadMinima = velocidadMinima;

            for (int tabla = 0; tabla < cantidadTablas; tabla++) {
                mejorAsignacion[tabla] = asignacionActual[tabla];
            }
        }
    }
}

/*
 * Carga los datos del ejemplo, ejecuta la busqueda exhaustiva e imprime las
 * tablas de cada disco junto con su velocidad restante.
 */
int main() {
    const int cantidadTablas = 6;
    const int cantidadDiscos = 3;

    int demandaTablas[cantidadTablas] = {150, 100, 80, 50, 120, 10};
    int velocidadDiscos[cantidadDiscos] = {250, 200, 200};
    int asignacionActual[cantidadTablas] = {};
    int mejorAsignacion[cantidadTablas] = {};
    int mejorVelocidadMinima = INT_MIN;
    int combinacionesEvaluadas = 0;

    buscarAsignacionOptima(demandaTablas, cantidadTablas,
                           velocidadDiscos, cantidadDiscos,
                           asignacionActual, mejorAsignacion,
                           mejorVelocidadMinima, combinacionesEvaluadas);

    cout << "Asignacion optima:\n";

    for (int disco = 0; disco < cantidadDiscos; disco++) {
        int demandaTotal = 0;
        bool primeraTabla = true;

        cout << "Disco " << disco + 1 << " - Tablas: ";

        for (int tabla = 0; tabla < cantidadTablas; tabla++) {
            if (mejorAsignacion[tabla] == disco) {
                if (!primeraTabla) {
                    cout << ", ";
                }
                cout << tabla + 1;
                demandaTotal += demandaTablas[tabla];
                primeraTabla = false;
            }
        }

        if (primeraTabla) {
            cout << '-';
        }

        cout << " | Velocidad restante: "
             << velocidadDiscos[disco] - demandaTotal << " IOPs\n";
    }

    cout << "Velocidad minima del grupo: " << mejorVelocidadMinima
         << " IOPs\n";
    cout << "Combinaciones evaluadas: " << combinacionesEvaluadas << '\n';

    return 0;
}
