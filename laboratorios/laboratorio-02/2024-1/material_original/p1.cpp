#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Paciente {
	char codigo[6];
	int fecha;
};

struct Nodo {
	Paciente paciente;
	Nodo* sig = NULL;
};

struct ColaPrioridad {
	Nodo *raiz = NULL;
	Nodo *maxima = NULL;
	Nodo *media = NULL;
	Nodo *minima = NULL;
};

int leerDatos(ColaPrioridad *cola);
int hallarPrioridadDePaciente(Paciente paciente);
void encolar(ColaPrioridad *cola, Nodo *nodo);
void imprimeCola(ColaPrioridad cola);

int main() {
	
	ColaPrioridad cola;
	leerDatos(&cola);
	imprimeCola(cola);
	
	return 0;
}

int leerDatos(ColaPrioridad *cola) {
	
	ifstream archivo("datos1.txt");
	if (!archivo) {
		cout << "Error al abrir el archivo datos1.txt" << endl;
		return 1;
	}

	int dia, mes, anho;
	
	while (true) {
		
		archivo >> dia;
		if (archivo.eof())
			break;
		
		Nodo* nuevoNodo = new Nodo;
		
		archivo.get();
		archivo >> mes;
		archivo.get();
		archivo >> anho;
		
		archivo >> nuevoNodo->paciente.codigo;
	
		nuevoNodo->paciente.fecha = anho * 10000 + mes * 100 + dia;
		
		encolar(cola, nuevoNodo);
	}

	archivo.close();
	return 0;
}

int hallarPrioridadDePaciente(Paciente paciente) {
	int fecha = paciente.fecha;
	int fechaActual = 20240924; // 24/09/2024
	double anhos = double(fechaActual - fecha) / 10000;
	if (anhos > 80)
		return 1;
	if (anhos < 10)
		return 2;
	return 3;
}

void encolar(ColaPrioridad *cola, Nodo *nodo) {

	int prioridad = hallarPrioridadDePaciente(nodo->paciente);
	
	if (prioridad == 1) {
		
		if (cola->maxima != NULL) {
			nodo->sig = cola->maxima->sig;
			cola->maxima->sig = nodo;
		}
		else {
			nodo->sig = cola->raiz;
			cola->raiz = nodo;
		}
		
		cola->maxima = nodo;
	}	
	if (prioridad == 2) {
		
		if (cola->media != NULL) {
			nodo->sig = cola->media->sig;
			cola->media->sig = nodo;
		}
		else {
			if (cola->maxima != NULL) {
				nodo->sig = cola->maxima->sig;
				cola->maxima->sig = nodo;
			}
			else {
				nodo->sig = cola->raiz;
				cola->raiz = nodo;
			}
		}
		cola->media = nodo;
	}
	if (prioridad == 3) {
		if (cola->minima != NULL) {
			cola->minima->sig = nodo;
		}
		else {
			if (cola->media != NULL) {
				cola->media->sig = nodo;
			}
			else if (cola->maxima != NULL) {
				cola->maxima->sig = nodo;
			}
		}
		cola->minima = nodo;
	}
	if (cola->raiz == NULL)
		cola->raiz = nodo;
}

void imprimeCola(ColaPrioridad cola) {
	for (Nodo* nodo = cola.raiz; nodo != NULL; nodo = nodo->sig) {
		Paciente paciente = nodo->paciente;
		int anho = paciente.fecha / 10000;
		int mes = (paciente.fecha % 10000) / 100;
		int dia = paciente.fecha % 100;
		cout << dia << "/" << mes << "/" << anho << " " << paciente.codigo << endl;
	}
}

