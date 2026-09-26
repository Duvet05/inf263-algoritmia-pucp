#include <iostream>
#include <fstream>
using namespace std;

struct Nodo {
	int calidad;
	int peso;
	Nodo* sig = NULL;
};

struct Lista {
	Nodo* inicio = NULL;
	Nodo* fin = NULL;
};

struct Pila {
	Nodo* inicio = NULL;
};

int leerDatos(Lista *lista);
void insertarEnLista(Lista *lista, Nodo* nuevoNodo);
void insertarListaEnPila(Lista *lista, Pila *pila);
void insertarNodoEnPila(Pila *pila, Nodo* nuevoNodo);
int hallarUbicacionEnPila(Pila pila, Nodo* nuevoNodo);
void mover(int n, Pila *origen, Pila *destino, Pila *auxiliar);
void imprimirPila(Pila pila);

int main() {
	
	Lista lista;
	Pila pila;
	
	leerDatos(&lista);
	insertarListaEnPila(&lista, &pila);
	imprimirPila(pila);
	
	return 0;
}

int leerDatos(Lista *lista) {
	
	ifstream archivo("datos2.txt");
	if (!archivo) {
		cout << "Error al abrir el archivo datos2.txt" << endl;
		return 1;
	}
	
	while (true) {
		
		int calidad, peso;
		archivo >> calidad;
		if (archivo.eof())
			break;
		archivo >> peso;
		
		Nodo* nuevoNodo = new Nodo;
		nuevoNodo->calidad = calidad;
		nuevoNodo->peso = peso;
		insertarEnLista(lista, nuevoNodo);
	}
	
	archivo.close();
	return 0;
}

void insertarEnLista(Lista *lista, Nodo* nuevoNodo) {
	
	if (lista->inicio == NULL) {
		lista->inicio = nuevoNodo;
	}
	else {	
		lista->fin->sig = nuevoNodo;
	}
	lista->fin = nuevoNodo;
}

void insertarListaEnPila(Lista *lista, Pila *pila) {
	
	for (Nodo* nodo = lista->inicio; nodo != NULL; ) {
		Nodo* nodoSig = nodo->sig; 
		insertarNodoEnPila(pila, nodo);	
		nodo = nodoSig;
	}
	lista->inicio = NULL;
	lista->fin = NULL;
}

void insertarNodoEnPila(Pila *pila, Nodo* nuevoNodo) {

	Pila auxiliar, destino;
	int n = hallarUbicacionEnPila(*pila, nuevoNodo);
	
	mover(n, pila, &destino, &auxiliar);
	
	nuevoNodo->sig = pila->inicio;
	pila->inicio = nuevoNodo;
	
	mover(n, &destino, pila, &auxiliar);
}

int hallarUbicacionEnPila(Pila pila, Nodo* nuevoNodo) {
	int n = 0;
	for (Nodo* nodo = pila.inicio; nodo != NULL; nodo = nodo->sig) {
		if (nodo->peso == nuevoNodo->peso) {
			if (nodo->calidad > nuevoNodo->calidad) {
				break;
			}
		}
		else if (nodo->peso > nuevoNodo->peso) {
			break;
		}
		n++;
	}
	return n;
}

void mover(int n, Pila *origen, Pila *destino, Pila *auxiliar) {
	if (0 < n) {
		mover(n-1, origen, auxiliar, destino);
		
		Nodo* nodo = origen->inicio;
		origen->inicio = nodo->sig;
		nodo->sig = destino->inicio;
		destino->inicio = nodo;
		
		mover(n-1, auxiliar, destino, origen);
	}
}

void imprimirPila(Pila pila) {
	for (Nodo* nodo = pila.inicio; nodo != NULL; nodo = nodo->sig) {
		cout << nodo->calidad << " - " << nodo->peso << endl;
	}
	cout << endl;
}



