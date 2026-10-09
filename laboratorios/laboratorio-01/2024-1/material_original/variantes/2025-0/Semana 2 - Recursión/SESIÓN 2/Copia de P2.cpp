#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

struct Posicion {
	int x, y;
};

int leerDatos(int &ancho, int &alto, int** &matriz, Posicion &pos);
void hallarLimites(int &filaInicio, int &filaFin, int &columnaInicio, int &columnaFin, Posicion pos, int alto);
void buscar(int ancho, int alto, int** matriz, int filaInicio, int filaFin, int colInicio, int colFin, int &suma);
void liberarMemoria(int alto, int** matriz);

int main() {
	
	int ancho, alto;
	int** matriz;
	Posicion pos;
	
	if (leerDatos(ancho, alto, matriz, pos) == 1)
		return 1;
	
	int filaInicio, filaFin, columnaInicio, columnaFin;

	hallarLimites(filaInicio, filaFin, columnaInicio, columnaFin, pos, alto);
	int suma = 0;
	buscar(ancho, alto, matriz, filaInicio, filaFin, columnaInicio, columnaFin, suma);
	
	cout << "Resultado de la busqueda: " << suma << endl;
	
	liberarMemoria(alto, matriz);
	
	return 0;
}

int leerDatos(int &ancho, int &alto, int** &matriz, Posicion &pos) {
	ifstream archivo("datos2.txt");
	
	if (!archivo) {
		cout << "No se puede abrir el archivo datos2.txt" << endl;
		return 1;
	}
	
	archivo >> ancho;
	archivo >> alto;
	
	matriz = new int*[alto];
	
	for (int x=0; x<alto; x++) {
		matriz[x] = new int[ancho];
		for (int y=0; y<ancho; y++)
			archivo >> matriz[x][y];
	}
	archivo >> pos.x;
	archivo >> pos.y;
	
	archivo.close();
	return 0;
}

void hallarLimites(int &filaInicio, int &filaFin, int &columnaInicio, int &columnaFin, Posicion pos, int alto) {
	
	int menor = alto - 1 - pos.x < pos.x ? alto - 1 - pos.x : pos.x;
	filaInicio = pos.x - menor;
	columnaInicio = pos.y - menor;
	filaFin = filaInicio + 2*menor;
	columnaFin = columnaInicio + 2*menor;
}

void buscar(int ancho, int alto, int** matriz, int filaInicio, int filaFin, int colInicio, int colFin, int &suma) {
		cout << "\nLlamada recursiva\n";
		cout << filaInicio << endl;
		cout << filaFin << endl;
		cout << colInicio << endl;
		cout << colFin << endl << endl;
 	// Caso base: si no hay m�s filas o columnas que recorrer
    if (filaInicio > filaFin || colInicio > colFin) {
        return;
    }

    // Recorrer la fila superior de izquierda a derecha
    for (int y = colInicio; y <= colFin; y++) {
        cout << matriz[filaInicio][y] << endl;
    	suma += matriz[filaInicio][y];
	}

    // Recorrer la columna derecha de arriba hacia abajo
    for (int x = filaInicio + 1; x <= filaFin; x++) {
        cout << matriz[x][colFin] << endl;
    	suma += matriz[x][colFin];
	}

    // Recorrer la fila inferior de derecha a izquierda, si a�n hay filas por recorrer
    if (filaInicio < filaFin) {
        for (int y = colFin - 1; y >= colInicio; y--) {
            cout << matriz[filaFin][y] << endl;
            suma += matriz[filaFin][y];
        }
    }

    // Recorrer la columna izquierda de abajo hacia arriba, si a�n hay columnas por recorrer
    if (colInicio < colFin) {
        for (int x = filaFin - 1; x > filaInicio; x--) {
            cout << matriz[x][colInicio] << endl;
            suma += matriz[x][colInicio];
        }
    }

    // Llamar recursivamente para la submatriz interna
    buscar(ancho, alto, matriz, filaInicio + 1, filaFin - 1, colInicio + 1, colFin - 1, suma);
}

void liberarMemoria(int alto, int** matriz) {
	for (int y=0; y<alto; y++) {
		delete[] matriz[y];
	}
	delete[] matriz;
}






