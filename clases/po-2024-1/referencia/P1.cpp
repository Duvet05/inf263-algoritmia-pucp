#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

struct Guerrero {
	int poder;
	int tipos_de_armas[4] = {0};
};

struct Arma {
	char id;
	int poder;
	int tipo;
	char armas_prerequisitos[4] = {0};
};

int leerDatos(int &cantidad_guerreros, Guerrero* &guerreros, int &cantidad_armas, Arma* &armas);
bool encontrarArmasParaGuerrero(int cantidad_guerreros, Guerrero* guerreros, int cantidad_armas, Arma* armas, int* armas_utilizadas, int indice_guerrero);
void cargarCromosoma(int* cromosoma, int tamano_cromosoma, int i);
bool esCromosomaValido(int* cromosoma, int cantidad_armas, Arma* armas, Guerrero guerrero, int* armas_utilizadas);
void imprimirSolucion(int cantidad_guerreros, Guerrero* guerreros, int cantidad_armas, Arma* armas, int* armas_utilizadas);

int main() {
	
	int cantidad_guerreros;
	Guerrero* guerreros;
	
	int cantidad_armas;
	Arma* armas;
	
	if (leerDatos(cantidad_guerreros, guerreros, cantidad_armas, armas) == 1)
		return 1;
	
//	for (int i=0; i<cantidad_guerreros; i++) {
//		Guerrero guerrero = guerreros[i];
//		cout << guerrero.poder << endl;
//		for (int j=0; guerrero.tipos_de_armas[j]; j++)
//			cout << guerrero.tipos_de_armas[j] << " ";
//		cout << endl << endl;
//	}
//	for (int i=0; i<cantidad_armas; i++) {
//		Arma arma = armas[i];
//		cout << arma.id << " " << arma.poder << " " << arma.tipo << endl;
//		for (int j=0; arma.armas_prerequisitos[j]; j++)
//			cout << arma.armas_prerequisitos[j] << " ";
//		cout << endl << endl;
//	}
	
	int armas_utilizadas[12] = {0};
	
	if (encontrarArmasParaGuerrero(cantidad_guerreros, guerreros, cantidad_armas, armas, armas_utilizadas, 0)) {
		imprimirSolucion(cantidad_guerreros, guerreros, cantidad_armas, armas, armas_utilizadas);
	}
	else {
		cout << "No existe una solucion para este caso" << endl;
	}
	
	delete[] guerreros;
	delete[] armas;
	
	return 0;
}

int leerDatos(int &cantidad_guerreros, Guerrero* &guerreros, int &cantidad_armas, Arma* &armas) {
	
	ifstream archivo("datos1.txt");
	
	if (!archivo) {
		cout << "No se puede abrir el archivo datos1.txt" << endl;
		return 1;
	}
	
	// Lectura de guerreros
	archivo >> cantidad_guerreros;
	guerreros = new Guerrero[cantidad_guerreros];
	
	for (int i=0; i<cantidad_guerreros; i++) {
	
		archivo >> guerreros[i].poder;
	
		int cantidad_tipos_de_armas;
		archivo >> cantidad_tipos_de_armas;
	
		for (int j=0; j<cantidad_tipos_de_armas; j++)
			archivo >> guerreros[i].tipos_de_armas[j];
	}
	
	// Lectura de armas
	archivo >> cantidad_armas;
	armas = new Arma[cantidad_armas];
	
	for (int i=0; i<cantidad_armas; i++) {
		
		archivo >> armas[i].id;
		archivo >> armas[i].poder;
		archivo >> armas[i].tipo;
		
		int cantidad_armas_prerequisito;
		archivo >> cantidad_armas_prerequisito;
		
		for (int j=0; j<cantidad_armas_prerequisito; j++)
			archivo >> armas[i].armas_prerequisitos[j];
	}
	
	
	archivo.close();
	
	return 0;
}

bool encontrarArmasParaGuerrero(int cantidad_guerreros, Guerrero* guerreros, int cantidad_armas, Arma* armas,
								int* armas_utilizadas, int indice_guerrero) {
	
	// Se verifica si se llego al final del arreglo de guerreros
	if (indice_guerrero == cantidad_guerreros)
		return true;
	
	// Se prueban todas las combinaciones posibles
	int* cromosoma = new int[cantidad_armas];
	int combinaciones = pow(2, cantidad_armas); 
	
	for (int i=0; i<combinaciones; i++) {
		
		cargarCromosoma(cromosoma, cantidad_armas, i);
		// Se verifica que el cromosoma sea valido
		if (esCromosomaValido(cromosoma, cantidad_armas, armas, guerreros[indice_guerrero], armas_utilizadas)) {
			// Se cargan las armas utilizadas para el guerrero
			for (int j=0; j<cantidad_armas; j++)
				if (cromosoma[j])
					armas_utilizadas[j] = indice_guerrero+1;
			// Se verifica que el siguiente guerrero tambien se pueda combatir con las armas restantes
			if (encontrarArmasParaGuerrero(cantidad_guerreros, guerreros, cantidad_armas, armas, armas_utilizadas, indice_guerrero+1)) {
				delete[] cromosoma;
				return true;
			}
			// Si no se puede, se descargan las armas utilizadas para el guerrero y se prueba la siguiente combinacion
			for (int j=0; j<cantidad_armas; j++)
				if (cromosoma[j])
					armas_utilizadas[j] = 0;
		}
	}
	delete[] cromosoma;
	return false;
}

void cargarCromosoma(int* cromosoma, int tamano_cromosoma, int i) {
	
	for (int j = 0; j < tamano_cromosoma; j++)
		cromosoma[j] = 0;
	
	for (int j = tamano_cromosoma - 1; i > 0; j--) { 
		cromosoma[j] = i % 2;			
		i /= 2;
	}
}

bool esCromosomaValido(int* cromosoma, int cantidad_armas, Arma* armas, Guerrero guerrero, int* armas_utilizadas) {
	
	// 1. Verificar que las armas no han sido utilizadas todavía
	for (int i=0; i<cantidad_armas; i++)
		if (cromosoma[i] && armas_utilizadas[i])
			return false;
	
	// 2. Verificar las armas prerequisitos
	for (int i=0; i<cantidad_armas; i++)
		if (cromosoma[i]) {
			Arma arma = armas[i];
			for (int j=0; arma.armas_prerequisitos[j]; j++) {
				for (int k=0; k<cantidad_armas; k++)
					if (armas[k].id == arma.armas_prerequisitos[j]) {
						if (cromosoma[k] == 0)
							return false;
						break;
					}
			}
		}
	
	// 3. Verificar que las armas seleccionadas pueden derrotar al guerrero
	int suma_poder = 0;
	for (int i=0, j; i<cantidad_armas; i++)
		if (cromosoma[i]) {
			Arma arma = armas[i];
			for (j=0; guerrero.tipos_de_armas[j]; j++) {
				if (arma.tipo == guerrero.tipos_de_armas[j])
					break;
			}
			if (guerrero.tipos_de_armas[j] == 0)
				return false;
			suma_poder += arma.poder;
		}
	if (suma_poder < guerrero.poder)
		return false;
	
	return true;
}

void imprimirSolucion(int cantidad_guerreros, Guerrero* guerreros, int cantidad_armas, Arma* armas, int* armas_utilizadas) {
	for (int i=0; i<cantidad_guerreros; i++) {
		Guerrero guerrero = guerreros[i];
		cout << "Guerrero " << i+1 << endl;
		cout << "Poder: " << guerrero.poder << endl;
		cout << "Armas en mochila para vencerlo: ";
		for (int j=0; j<cantidad_armas; j++) {
			if (armas_utilizadas[j] == i+1) {
				Arma arma = armas[j];
				cout << arma.id << " ";
			}
		}
		cout << endl << endl;
	}
}


