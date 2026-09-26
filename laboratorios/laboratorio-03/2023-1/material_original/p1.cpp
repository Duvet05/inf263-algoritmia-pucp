#include <iostream>
#include <fstream>
using namespace std;

struct Nodo {
	int nivel_de_ataque;
	Nodo* sig = NULL;	
};

struct Pila {
	Nodo* inicio = NULL;
	int longitud = 0;
};

int cargarPila(Pila *pila, char* nombre);
void moverNodos(int cantidad, Pila *origen, Pila* destino);
void ordenar(Pila *pila);
void mover(Pila *origen, Pila* destino);
void imprime(Pila *pila);

int main() {
	
	Pila kupa1, kupa2, mundo_champinhon;
	
	cargarPila(&kupa1, "kupa1.txt");
	cargarPila(&kupa2, "kupa2.txt");
	
	imprime(&kupa1);
	imprime(&kupa2);
	
	moverNodos(kupa2.longitud, &kupa2, &kupa1);
	
	imprime(&kupa1);
	
	ordenar(&kupa1);
	
	imprime(&kupa1);
	
	mover(&kupa1, &mundo_champinhon);
	
	imprime(&mundo_champinhon);
	
	return 0;
}

int cargarPila(Pila *pila, char* nombre) {
	
	ifstream archivo(nombre);
	if (!archivo) {
		cout << "Error al abrir el archivo " << nombre << endl;
		return 1;
	}
	
	while (true) {
		int nivel_de_ataque;
		archivo >> nivel_de_ataque;
		
		if (archivo.eof())
			break;
		
		Nodo *nodo = new Nodo;
		nodo->nivel_de_ataque = nivel_de_ataque;
		nodo->sig = pila->inicio;
		pila->inicio = nodo;
		(pila->longitud)++;
	}
	
	archivo.close();
	return 0;
}

void moverNodos(int cantidad, Pila *origen, Pila* destino) {
	
	Nodo *nodo = origen->inicio;
	for (int i=0; i<cantidad; i++) {
		
		Nodo* nodoSig = nodo->sig;
		
		nodo->sig = destino->inicio;
		destino->inicio = nodo;
		(destino->longitud)++;
		
		origen->inicio = nodoSig;
		(origen->longitud)--;
		
		nodo = nodoSig;
	}
}

void ordenar(Pila *pila) {
	
	Pila aux;
	
	for (int i=0; i<pila->longitud; i++) {
		Nodo *nodo = pila->inicio;
		for (int j=0; j<pila->longitud-i-1; j++) {
			if (nodo->nivel_de_ataque < nodo->sig->nivel_de_ataque) {
				
				moverNodos(j+1, pila, &aux);
				
				Nodo *nodoAux = pila->inicio;
				pila->inicio = nodoAux->sig;
				(pila->longitud)--;
				
				moverNodos(1, &aux, pila);
				
				nodoAux->sig = pila->inicio;
				pila->inicio = nodoAux;
				(pila->longitud)++;
				
				moverNodos(j, &aux, pila);
			}
			else
				nodo = nodo->sig;
		}
	}
}

void mover(Pila *origen, Pila* destino) {
	
	int n = origen->longitud;
	for (int i=n-1; i>=0; i--) {
		
		moverNodos(i, origen, destino);
		
		Nodo* nodoAux = origen->inicio;
		origen->inicio = nodoAux->sig;
		(origen->longitud)--;
		
		moverNodos(i, destino, origen);
		
		nodoAux->sig = destino->inicio;
		destino->inicio = nodoAux;
		(destino->longitud)++;
	}
}

void imprime(Pila *pila) {
	for (Nodo *nodo=pila->inicio; nodo != NULL; nodo=nodo->sig) {
		cout << nodo->nivel_de_ataque << " -> ";
	}
	cout << endl;
}

