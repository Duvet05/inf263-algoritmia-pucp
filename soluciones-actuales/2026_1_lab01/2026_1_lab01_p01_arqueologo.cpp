#include <iostream>
#include <cmath>

using namespace std;

/*
 * Estrategia:
 * La funcion recorre recursivamente las posiciones del cuadrado de lado
 * (2 * alcance + 1) que rodea al punto inicial. Para cada posicion calcula
 * su desplazamiento vertical (df) y horizontal (dc).
 *
 * El robot puede revisar una celda cuando abs(dc) <= abs(df): esto forma
 * los dos triangulos del despliegue, uno hacia arriba y otro hacia abajo.
 * Si encuentra un artefacto lo cuenta y reemplaza la celda por '*'.
 * La funcion no contiene ninguna estructura iterativa.
 */
void buscar(char terreno[][100], int n, int m,
            int x, int y, int alcance, int pos, int &cantidad) {
    if (alcance < 0) {
        return;
    }

    int lado = 2 * alcance + 1;

    // Caso base: ya se evaluaron todas las posiciones del cuadrado.
    if (pos >= lado * lado) {
        return;
    }

    // Convertir la posicion lineal en desplazamientos desde el robot.
    int df = pos / lado - alcance;
    int dc = pos % lado - alcance;

    // En una matriz, y determina la fila y x determina la columna.
    int fila = y + df;
    int columna = x + dc;

    // Se procesa solamente una posicion valida y alcanzable por el robot.
    if (fila >= 0 && fila < n && columna >= 0 && columna < m &&
        abs(dc) <= abs(df)) {
        if (terreno[fila][columna] == 'A') {
            cantidad++;
        }
        terreno[fila][columna] = '*';
    }

    buscar(terreno, n, m, x, y, alcance, pos + 1, cantidad);
}

/*
 * Inicializa el caso presentado en el enunciado, ejecuta la unica funcion
 * recursiva y emplea iteraciones solamente para imprimir la matriz final.
 */
int main() {
    const int n = 10;
    const int m = 10;
    const int alcance = 3;
    const int x = 5;
    const int y = 5;

    char terreno[100][100] = {};

    // Artefactos mostrados en el terreno del enunciado.
    terreno[3][3] = 'A';
    terreno[3][4] = 'A';
    terreno[4][5] = 'A';
    terreno[5][4] = 'A';
    terreno[5][7] = 'A';
    terreno[7][5] = 'A';

    int cantidad = 0;
    buscar(terreno, n, m, x, y, alcance, 0, cantidad);

    cout << "El robot encontro " << cantidad
         << " artefactos, realizando la siguiente busqueda.\n\n";

    // El enunciado permite usar iteraciones unicamente para imprimir.
    for (int fila = 0; fila < n; fila++) {
        for (int columna = 0; columna < m; columna++) {
            if (terreno[fila][columna] == '\0') {
                cout << "  ";
            } else {
                cout << terreno[fila][columna] << ' ';
            }
        }
        cout << '\n';
    }

    return 0;
}
