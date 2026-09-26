#include <iostream>
#include <iomanip>

using namespace std;

/*
 * Estrategia recursiva:
 * Cuando buscarInicio es verdadero, la misma funcion localiza de abajo hacia
 * arriba la siguiente celda libre del borde izquierdo. Para perforar una
 * galeria marca temporalmente la celda actual e intenta moverse hacia abajo,
 * hacia la derecha y hacia arriba, en ese orden. Si ningun movimiento permite
 * llegar al borde derecho, desmarca la celda para probar otro camino.
 *
 * Al completar una galeria, conserva sus marcas y vuelve a invocarse en modo
 * buscarInicio para construir la siguiente. Las rocas (-1) y las galerias ya
 * terminadas (numeros positivos) nunca pueden atravesarse. Esta es la unica
 * funcion recursiva y no contiene iteraciones.
 */
bool perforarGalerias(int mina[][100], int n, int m,
                      int fila, int columna, int numeroGaleria,
                      int &totalGalerias, bool buscarInicio) {
        if (buscarInicio) {
            // Ya no quedan posibles puntos de partida en el borde izquierdo.
            if (fila < 0) {
                return false;
            }

            // Una roca o galeria previa ocupa este punto de partida.
            if (mina[fila][0] != 0) {
                return perforarGalerias(mina, n, m, fila - 1, 0,
                                        numeroGaleria, totalGalerias, true);
            }

            // Se intenta construir una galeria desde la celda libre actual.
        if (perforarGalerias(mina, n, m, fila, 0,
                             numeroGaleria, totalGalerias, false)) {
            return true;
        }

        // Si no llega al lado derecho, se prueba la siguiente fila superior.
        return perforarGalerias(mina, n, m, fila - 1, 0,
                                numeroGaleria, totalGalerias, true);
    }

    // Posicion invalida, roca o celda usada por una galeria.
    if (fila < 0 || fila >= n || columna < 0 || columna >= m ||
        mina[fila][columna] != 0) {
        return false;
    }

    mina[fila][columna] = numeroGaleria;

    // Una galeria se completa cuando alcanza el borde derecho.
    if (columna == m - 1) {
        totalGalerias = numeroGaleria;

        // Se buscan mas galerias sin borrar la que acaba de completarse.
        perforarGalerias(mina, n, m, n - 1, 0,
                         numeroGaleria + 1, totalGalerias, true);
        return true;
    }

    // Prioridad requerida para reproducir los mapas: abajo, derecha y arriba.
    if (perforarGalerias(mina, n, m, fila + 1, columna,
                         numeroGaleria, totalGalerias, false)) {
        return true;
    }

    if (perforarGalerias(mina, n, m, fila, columna + 1,
                         numeroGaleria, totalGalerias, false)) {
        return true;
    }

    if (perforarGalerias(mina, n, m, fila - 1, columna,
                         numeroGaleria, totalGalerias, false)) {
        return true;
    }

    // El camino no llego al lado derecho; se deshace para probar otro. 
    mina[fila][columna] = 0;
    return false;
}

/*
 * Carga una columna de rocas como en los ejemplos, ejecuta la unica funcion
 * recursiva e imprime la mina. Los ciclos se usan solo para cargar los datos
 * previos y para mostrar la matriz, tal como permite el enunciado.
 */
int main() {
    const int n = 6;
    const int m = 11;
    int mina[100][100] = {};
    int cantidadRocas;

    cout << "Ingrese la cantidad de rocas centrales (2 o 3): ";
    if (!(cin >> cantidadRocas) ||
        (cantidadRocas != 2 && cantidadRocas != 3)) {
        cout << "La cantidad de rocas debe ser 2 o 3.\n";
        return 1;
    }

    // Carga permitida antes de llamar a la funcion recursiva.
    for (int roca = 0; roca < cantidadRocas; roca++) {
        mina[n / 2 + roca][m / 2] = -1;
    }

    int totalGalerias = 0;
    perforarGalerias(mina, n, m, n - 1, 0, 1, totalGalerias, true);

    cout << "\nMina a imprimir con " << totalGalerias << " galerias:\n\n";

    // Iteraciones permitidas para imprimir la matriz.
    for (int fila = 0; fila < n; fila++) {
        for (int columna = 0; columna < m; columna++) {
            if (mina[fila][columna] == -1) {
                cout << setw(3) << '*';
            } else if (mina[fila][columna] == 0) {
                cout << setw(3) << ' ';
            } else {
                cout << setw(3) << mina[fila][columna];
            }
        }
        cout << '\n';
    }

    return 0;
}
