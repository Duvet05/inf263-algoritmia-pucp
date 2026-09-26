#include <iostream>

using namespace std;

/*
 * Estrategia de fuerza bruta:
 * Cada subconjunto de controles se representa mediante una mascara de bits.
 * El bit i vale 1 cuando el control i fue seleccionado. Se prueban todos los
 * subconjuntos no vacios, se calculan sus tres totales y se muestran aquellos
 * que cumplen simultaneamente las restricciones P, B y F.
 */
void mostrarOpciones(const int costos[], const int beneficios[],
                     const int falsosNegativos[], int cantidadControles,
                     int presupuesto, int beneficioMinimo,
                     int maximoFalsosNegativos) {
    int totalSubconjuntos = 1;
    for (int control = 0; control < cantidadControles; control++) {
        totalSubconjuntos *= 2;
    }
    bool existeOpcion = false;

    for (int mascara = 1; mascara < totalSubconjuntos; mascara++) {
        int costoTotal = 0;
        int beneficioTotal = 0;
        int falsosNegativosTotal = 0;

        for (int control = 0; control < cantidadControles; control++) {
            if (mascara & (1 << control)) {
                costoTotal += costos[control];
                beneficioTotal += beneficios[control];
                falsosNegativosTotal += falsosNegativos[control];
            }
        }

        // Los ejemplos del PDF consideran valido beneficioTotal == B.
        if (costoTotal <= presupuesto &&
            beneficioTotal >= beneficioMinimo &&
            falsosNegativosTotal <= maximoFalsosNegativos) {
            existeOpcion = true;
            bool primerControl = true;

            cout << "Recursos: {";
            for (int control = 0; control < cantidadControles; control++) {
                if (mascara & (1 << control)) {
                    if (!primerControl) {
                        cout << ',';
                    }
                    cout << control + 1;
                    primerControl = false;
                }
            }

            cout << "}, Costo total: " << costoTotal
                 << ", Beneficio: " << beneficioTotal
                 << ", Falsos Negativos: " << falsosNegativosTotal << '\n';
        }
    }

    if (!existeOpcion) {
        cout << "No se pueden seleccionar controles de seguridad que cumplan "
                "todas las restricciones.\n";
    }
}

/*
 * Inicializa los ocho controles indicados en el enunciado, solicita las tres
 * restricciones al usuario y ejecuta la busqueda exhaustiva.
 */
int main() {
    const int cantidadControles = 8;

    int costos[cantidadControles] = {
        35000, 24000, 30000, 27000, 10000, 7000, 6000, 40000
    };
    int beneficios[cantidadControles] = {80, 60, 70, 48, 20, 35, 10, 40};
    int falsosNegativos[cantidadControles] = {1, 3, 2, 1, 1, 2, 1, 3};

    int presupuesto;
    int beneficioMinimo;
    int maximoFalsosNegativos;

    cout << "Ingrese P, B y F: ";
    if (!(cin >> presupuesto >> beneficioMinimo >> maximoFalsosNegativos)) {
        cout << "Los datos ingresados no son validos.\n";
        return 1;
    }

    if (presupuesto < 0 || beneficioMinimo < 0 ||
        maximoFalsosNegativos < 0) {
        cout << "P, B y F no pueden ser negativos.\n";
        return 1;
    }

    mostrarOpciones(costos, beneficios, falsosNegativos,
                    cantidadControles, presupuesto, beneficioMinimo,
                    maximoFalsosNegativos);

    return 0;
}
