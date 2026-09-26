#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;

void leerDatos(int &cantidad_niveles, int* &orden_niveles, int* &pesos_vidrios, int &cantidad_robots, int* &pesos_robots);
int leerDatosDeArchivo(int &cantidad_niveles, int* &orden_niveles, int* &pesos_vidrios, int &cantidad_robots, int* &pesos_robots);
void ordenarPesosVidrios(int cantidad_niveles, int* orden_niveles, int* pesos_vidrios);
int maximo(int tamano_arreglo, int* arreglo);
void ordenarPesosRobots(int cantidad_robots, int* pesos_robots);
void cargarCromosoma(int* cromosoma, int tamano_cromosoma, int i);
bool esCromosomaValido(int tamano_cromosoma, int* cromosoma, int cantidad_niveles, int *pesos_vidrios, int peso_maximo_robot);
void imprimirResultado(int tamano_cromosoma, int* cromosoma, int cantidad_soluciones);

int main(int argc, char** argv) {
	
	// Lectura de los datos
	int cantidad_niveles;
	int cantidad_robots;
	
	int* orden_niveles;
	int* pesos_vidrios;
	int* pesos_robots;
	
	if (leerDatosDeArchivo(cantidad_niveles, orden_niveles, pesos_vidrios, cantidad_robots, pesos_robots) == 1)
		return 1;
	ordenarPesosVidrios(cantidad_niveles, orden_niveles, pesos_vidrios);
	
//	for (int i=0; i<cantidad_niveles; i++) {
//		cout << orden_niveles[i] << endl;
//		cout << pesos_vidrios[i*2] << " " << pesos_vidrios[i*2+1] << endl << endl;
//	}
//	for (int i=0; i<cantidad_robots; i++) {
//		cout << pesos_robots[i] << endl;
//	}
//	
	// Busqueda de todas las soluciones	
    int tamano_cromosoma = cantidad_niveles;					
	int *cromosoma = new int[tamano_cromosoma];						// Arreglo que tiene la capacidad de guardar cualquier combinación de dirección (izquierda o derecha) para todos los niveles.
	int combinaciones = pow(2, tamano_cromosoma);					// Todas las posibles combinaciones.
    int cantidad_soluciones = 0;									// La cantidad de soluciones posibles
    
    // ITEM B
    int peso_maximo_robot = maximo(cantidad_robots, pesos_robots);	// El peso maximo de todos los pesos de los robots.
    cout << "Peso maximo robot: " << peso_maximo_robot << endl;	
    for (int i = 0; i < combinaciones; i++) {
    	cargarCromosoma(cromosoma, tamano_cromosoma, i);
    	if (esCromosomaValido(tamano_cromosoma, cromosoma, cantidad_niveles, pesos_vidrios, peso_maximo_robot)) {
    		imprimirResultado(tamano_cromosoma, cromosoma, cantidad_soluciones);
    		cantidad_soluciones++;
		}
	}
	// ITEM C
//	ordenarPesosRobots(cantidad_robots, pesos_robots);
//	int j = cantidad_robots - 1; // Se empieza con el robot mas pesado
//	while (cantidad_soluciones == 0 && 0 <= j) {
//		for (int i = 0; i < combinaciones; i++) {
//	    	cargarCromosoma(cromosoma, tamano_cromosoma, i);
//	    	if (esCromosomaValido(tamano_cromosoma, cromosoma, cantidad_niveles, pesos_vidrios, pesos_robots[j])) {
//	    		imprimirResultado(tamano_cromosoma, cromosoma, cantidad_soluciones);
//	    		cantidad_soluciones++;
//			}
//		}
//		// Si no se encuentra una solución, se pasa al siguiente robot mas pesado
//		if (cantidad_soluciones == 0)
//			j--;
//	}
	// Hay al menos un robot muy pesado para pasar
//	if (j < cantidad_robots - 1) {
//        cout << "\nLos pesos de los robots que no pueden pasar son los siguientes:\n";
//        for (int i = cantidad_robots - 1; i > j; i--) {
//            cout << pesos_robots[i] << "\n";
//        }
//    }
	
	// Liberando memoria dinámica
	delete[] orden_niveles;
    delete[] pesos_vidrios;
    delete[] pesos_robots;
	
	return 0;
}

void leerDatos(int &cantidad_niveles, int* &orden_niveles, int* &pesos_vidrios, int &cantidad_robots, int* &pesos_robots) {
	
	cout << "Ingrese la cantidad de niveles que tiene el puente: ";
    cin >> cantidad_niveles;
    
    orden_niveles = new int[cantidad_niveles];
    pesos_vidrios = new int[2 * cantidad_niveles]; // 2 pesos (izquierda y derecha) por cada nivel
	
	for (int i = 0; i < cantidad_niveles; i++) {
		cout << "\nIngrese el nivel: ";
		cin >> orden_niveles[i];
		cout << "Ingrese el peso maximo que puede soportar el vidrio en la izquierda: ";
		cin >> pesos_vidrios[i*2];
		cout << "Ingrese el peso maximo que puede soportar el vidrio en la derecha: ";
		cin >> pesos_vidrios[i*2 + 1];
	}
	
	cout << "\nIngrese la cantidad de robots: ";
    cin >> cantidad_robots;
    
    pesos_robots = new int[cantidad_robots];
	
	cout << endl;
	for (int i = 0; i < cantidad_robots; i++) {
		cout << "Ingrese el peso del robot " << i+1 << ": ";
		cin >> pesos_robots[i];
	}
}

int leerDatosDeArchivo(int &cantidad_niveles, int* &orden_niveles, int* &pesos_vidrios, int &cantidad_robots, int* &pesos_robots) {
	
	// Abriendo el archivo
	ifstream archivo("datos2.txt");
    
	// Verificando si el archivo fue abierto correctamente
	if (!archivo) {
        cerr << "No se pudo abrir el archivo." << endl;
        return 1;
    }
    
    archivo >> cantidad_niveles;
    
    orden_niveles = new int[cantidad_niveles];
    pesos_vidrios = new int[2 * cantidad_niveles]; // 2 pesos (izquierda y derecha) por cada nivel
    
    for (int i = 0; i < cantidad_niveles; i++) {
		archivo >> orden_niveles[i];
		archivo >> pesos_vidrios[i*2];
		archivo >> pesos_vidrios[i*2 + 1];
	}
    
    archivo >> cantidad_robots;
    
    pesos_robots = new int[cantidad_robots];
    for (int i = 0; i < cantidad_robots; i++) {
    	archivo >> pesos_robots[i];
	}
    
    archivo.close();
    return 0;
}

void ordenarPesosVidrios(int cantidad_niveles, int* orden_niveles, int* pesos_vidrios) {
	
	for (int i = 0; i < cantidad_niveles - 1; i++) {
	    for (int j = i + 1; j < cantidad_niveles; j++) {
            if (orden_niveles[j] < orden_niveles[i]) {
                // Intercambiamos el orden de los niveles
                int aux = orden_niveles[i];
                orden_niveles[i] = orden_niveles[j];
                orden_niveles[j] = aux;
                // Intercambiamos los pesos de los vidrios
                aux = pesos_vidrios[2*i];
			    pesos_vidrios[2*i] = pesos_vidrios[2*j];
			    pesos_vidrios[2*j] = aux;
			    aux = pesos_vidrios[2*i + 1];
			    pesos_vidrios[2*i + 1] = pesos_vidrios[2*j + 1];
			    pesos_vidrios[2*j + 1] = aux;
            }
        }
    }
}

int maximo(int tamano_arreglo, int* arreglo) {
	int max = -9999;
	for (int i = 0; i < tamano_arreglo; i++) {
		if (max < arreglo[i])
			max = arreglo[i];
	}
	return max;
}

void ordenarPesosRobots(int cantidad_robots, int* pesos_robots) {
	
	for (int i = 0; i < cantidad_robots - 1; i++) {
	    for (int j = i + 1; j < cantidad_robots; j++) {
            if (pesos_robots[j] < pesos_robots[i]) {
                // Intercambiamos los pesos de los robots
                int aux = pesos_robots[i];
                pesos_robots[i] = pesos_robots[j];
                pesos_robots[j] = aux;
            }
        }
    }
}

void cargarCromosoma(int* cromosoma, int tamano_cromosoma, int i) {
	
	for (int j = 0; j < tamano_cromosoma; j++)
		cromosoma[j] = 0;
	
	for (int j = tamano_cromosoma - 1; i > 0; j--) { 
		cromosoma[j] = i % 2;			
		i /= 2;
	}
}

bool esCromosomaValido(int tamano_cromosoma, int* cromosoma, int cantidad_niveles, int *pesos_vidrios, int peso_maximo_robot) {
	
	for (int i = 0; i < tamano_cromosoma; i++) {
		// izquierda
		if (cromosoma[i] == 0 && pesos_vidrios[2*i] < peso_maximo_robot)
			return false;
		// derecha
		if (cromosoma[i] == 1 && pesos_vidrios[2*i + 1] < peso_maximo_robot)
			return false;
	}
	return true;
}

void imprimirResultado(int tamano_cromosoma, int* cromosoma, int cantidad_soluciones) {
	
	cout << "\nSolucion " << cantidad_soluciones+1 << ":" << endl;
	for (int i = 0; i < tamano_cromosoma; i++) {
		cout << "Nivel " << i+1 << ":";
		if (cromosoma[i] == 0)
			cout << "Izquierda" << endl;
		if (cromosoma[i] == 1)
			cout << "Derecha" << endl;	
	}
}

