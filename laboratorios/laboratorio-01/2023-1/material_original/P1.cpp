#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;

void leerDatos(int &cantidad_camiones, int* &capacidades_camiones, int &cantidad_paquetes, int* &pesos_paquetes);
int leerDatosDesdeArchivo(int &cantidad_camiones, int* &capacidades_camiones, int &cantidad_paquetes, int* &pesos_paquetes);
void cargarCromosoma(int* cromosoma, int tamano_cromosoma, int i);
bool esCromosomaValido(	int* cromosoma,
						int* capacidades_camiones, int* cargas_camiones, int cantidad_camiones,
						int* pesos_paquetes, int cantidad_paquetes, bool ningun_camion_sin_carga);
void verificarMejorCombinacion(	int* capacidades_camiones, int* cargas_camiones, int cantidad_camiones,
								int &mejor_combinacion, int &menor_diferencia, int i);
void imprimirResultado(int* cromosoma, int tamano_cromosoma, int cantidad_paquetes, int diferencia_maxima);
						
int main(int argc, char** argv) {
	
	// Lectura de los datos
	int cantidad_camiones; // M
    int cantidad_paquetes; // N

    int* capacidades_camiones; 	// Arreglo con las capacidades de los camiones (en kg)
	int* pesos_paquetes; 		// Arreglo con los pesos de los paquetes (en kg)
    
    if (leerDatosDesdeArchivo(cantidad_camiones, capacidades_camiones, cantidad_paquetes, pesos_paquetes) == 1)
    	return 1;
//	leerDatos(cantidad_camiones, capacidades_camiones, cantidad_paquetes, pesos_paquetes);
    
//    for (int i=0; i<cantidad_camiones; i++) {
//    	cout << capacidades_camiones[i] << endl;
//	}
//	for (int i=0; i<cantidad_paquetes; i++) {
//    	cout << pesos_paquetes[i] << endl;
//	}
//	return 0;
    
    // Búsqueda de la mejor combinación
    int tamano_cromosoma = cantidad_camiones * cantidad_paquetes;
	int* cromosoma = new int[tamano_cromosoma]; 		// Arreglo que tiene la capacidad de guardar cualquier combinación de paquetes con camiones.
	int combinaciones = pow(2, tamano_cromosoma); 		// Todas las posibles combinaciones de paquetes con camiones.
    int mejor_combinacion; 								// La mejor combinación.
    int diferencia_maxima = 9999;						// La diferencia entre el espacio no utilizado máximo y mínimo.
    int cargas_camiones[cantidad_camiones];				// Arreglo que guarda las cargas de los camiones.
    
	for (int i = 0; i < combinaciones; i++) {
		cargarCromosoma(cromosoma, tamano_cromosoma, i);
		if (!esCromosomaValido(	cromosoma,
								capacidades_camiones, cargas_camiones, cantidad_camiones,
								pesos_paquetes, cantidad_paquetes, true))
			continue;
		verificarMejorCombinacion(capacidades_camiones, cargas_camiones, cantidad_camiones, mejor_combinacion, diferencia_maxima, i);
	}
	
	// Impresión de la mejor combinación
	cargarCromosoma(cromosoma, tamano_cromosoma, mejor_combinacion);
	imprimirResultado(cromosoma, tamano_cromosoma, cantidad_paquetes, diferencia_maxima);

	// Liberando memoria dinámica
	delete[] capacidades_camiones;
    delete[] pesos_paquetes;
    delete[] cromosoma;
	
	return 0;
}

void leerDatos(int &cantidad_camiones, int* &capacidades_camiones, int &cantidad_paquetes, int* &pesos_paquetes) {
	
	cout << "Ingrese la cantidad de camiones: ";
    cin >> cantidad_camiones;
    
    cout << "Ingrese las capacidades en kg:\n";
    capacidades_camiones = new int[cantidad_camiones];
    for (int i = 0; i < cantidad_camiones; i++) {
        cout << "Ingrese la capacidad del camion " << i+1 << ": ";
		cin >> capacidades_camiones[i];
    }
    
	cout << "\nIngrese la cantidad de paquetes: ";
    cin >> cantidad_paquetes;
    
    cout << "Ingrese los pesos en kg:\n";
    pesos_paquetes = new int[cantidad_paquetes];
    for (int i = 0; i < cantidad_paquetes; i++) {
        cout << "Ingrese el peso del paquete " << i+1 << ": ";
		cin >> pesos_paquetes[i];
    }
}

int leerDatosDesdeArchivo(int &cantidad_camiones, int* &capacidades_camiones, int &cantidad_paquetes, int* &pesos_paquetes) {
	
	// Abriendo el archivo
	ifstream archivo("datos1.txt");
    
	// Verificando si el archivo fue abierto correctamente
	if (!archivo) {
        cerr << "No se pudo abrir el archivo." << endl;
        return 1;
    }
    
    archivo >> cantidad_camiones;
    capacidades_camiones = new int[cantidad_camiones];
    for (int i = 0; i < cantidad_camiones; i++) {
    	archivo >> capacidades_camiones[i];
	}
	
	archivo >> cantidad_paquetes;
    pesos_paquetes = new int[cantidad_paquetes];
    for (int i = 0; i < cantidad_paquetes; i++) {
    	archivo >> pesos_paquetes[i];
	}
	
	archivo.close();
	return 0;
}

void cargarCromosoma(int* cromosoma, int tamano_cromosoma, int i) {
	
	for (int j = 0; j < tamano_cromosoma; j++)
		cromosoma[j] = 0;
	
	for (int j = tamano_cromosoma - 1; i > 0; j--) { 
		cromosoma[j] = i % 2;			
		i /= 2;
	}
}

bool esCromosomaValido(	int* cromosoma,
						int* capacidades_camiones, int* cargas_camiones, int cantidad_camiones,
						int* pesos_paquetes, int cantidad_paquetes, bool ningun_camion_sin_carga) {
	
	// 1. Un camión puede cargar como máximo su capacidad maxima.
	for (int i = 0; i < cantidad_camiones; i++) {
		cargas_camiones[i] = 0;
		for (int j = 0; j < cantidad_paquetes; j++) {
			int valor = cromosoma[i * cantidad_paquetes + j];
			if (valor)
				cargas_camiones[i] += pesos_paquetes[j];
		}
		if (cargas_camiones[i] > capacidades_camiones[i] || (ningun_camion_sin_carga && cargas_camiones[i] == 0))
			return false;
	}
	// 2. Un paquete sólo puede estar en un camión a la vez.
	for (int j = 0; j < cantidad_paquetes; j++) {
		int repeticiones_del_paquete = 0;
		for (int i = 0; i < cantidad_camiones; i++) {
			int valor = cromosoma[i * cantidad_paquetes + j];
			if (valor)
				repeticiones_del_paquete++;
		}
		if (repeticiones_del_paquete != 1)
			return false;
	}
	return true;
}

void verificarMejorCombinacion(	int* capacidades_camiones, int* cargas_camiones, int cantidad_camiones,
								int &mejor_combinacion, int &diferencia_maxima, int i) {
	int minimo = 9999;
	int maximo = 0;
	
	for (int i = 0; i < cantidad_camiones; i++) {
		int capacidad_restante_camion = capacidades_camiones[i] - cargas_camiones[i];
		if (capacidad_restante_camion < minimo)
			minimo = capacidad_restante_camion;
		if (maximo < capacidad_restante_camion)
			maximo = capacidad_restante_camion;
	}
	
	if (maximo - minimo < diferencia_maxima) {
		mejor_combinacion = i;
		diferencia_maxima = maximo - minimo;
	}
}

void imprimirResultado(int* cromosoma, int tamano_cromosoma, int cantidad_paquetes, int diferencia_maxima) {
    
	cout << endl;
    for (int j = 0; j < cantidad_paquetes; j++) {
    	for (int i = 0; i < tamano_cromosoma; i++) {
	        if (cromosoma[i] && j == i % cantidad_paquetes)
	        	cout << "Paquete: " << (j + 1) << " Camion: " << (i / cantidad_paquetes + 1) << "\n";
    	}
	}
    cout << "\nDiferencia maxima: " << diferencia_maxima << "\n";
}

