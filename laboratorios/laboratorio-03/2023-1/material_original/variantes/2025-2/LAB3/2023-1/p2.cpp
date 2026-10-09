#include <iostream>
#include <fstream>
using namespace std;
#include "bibliotecas/Lista.h"
#include "bibliotecas/funcionesLista.h"

int leerDatos(Lista *lista, char* nombre);
void unir(Lista *destino, Lista *origen);

int main() {
	
	Lista A, B, C, D, E;
	construir(A);
	construir(B);
	construir(C);
	construir(D);
	construir(E);
	
	leerDatos(&A, "A.txt");
	leerDatos(&B, "B.txt");
	leerDatos(&C, "C.txt");
	leerDatos(&D, "D.txt");
	leerDatos(&E, "E.txt");

	unir(&A, &B);
	unir(&A, &C);
	unir(&A, &D);
	unir(&A, &E);
	
	imprimir(A);

	return 0;
}

int leerDatos(Lista *lista, char* nombre) {
	
	ifstream archivo(nombre);
	if (!archivo) {
		cout << "Error al abrir el archivo " << nombre << endl;
		return 1;
	}
	char categoria = nombre[0];
	while (true) {
		int impacto;
		archivo >> impacto;
		if (archivo.eof())
			break;
		ElementoLista elemento;
		elemento.ID = categoria;
		elemento.valor = impacto;
		insertarAlFinal(*lista, elemento);
	}
	
	archivo.close();
	return 0;
}

void unir(Lista *destino, Lista *origen) {
	
	// Verificar si puedo unir el final del destino con el inicio del origen
	if (destino->fin != NULL && origen->inicio != NULL) {
		if (destino->fin->elemento.valor > origen->inicio->elemento.valor ||
			(destino->fin->elemento.valor == origen->inicio->elemento.valor &&
				destino->fin->elemento.ID < origen->inicio->elemento.ID)) {
			destino->fin->siguiente = origen->inicio;
			destino->fin = origen->fin;
			origen->inicio = NULL;
			origen->fin = NULL;
			return;
		}
	}

	NodoLista *nodoDestino = destino->inicio;
	NodoLista *nodoOrigen = origen->inicio;
	NodoLista *prevDestino = NULL;
	NodoLista *sigOrigen = nodoOrigen->siguiente;

	while (nodoDestino != NULL && nodoOrigen != NULL) {
		if (nodoOrigen->elemento.valor > nodoDestino->elemento.valor ||
			(nodoOrigen->elemento.valor == nodoDestino->elemento.valor &&
				nodoOrigen->elemento.ID < nodoDestino->elemento.ID)) {
			// Insertar nodoOrigen antes de nodoDestino
			if (prevDestino)
				prevDestino->siguiente = nodoOrigen;
			else
				destino->inicio = nodoOrigen;
			nodoOrigen->siguiente = nodoDestino;
			prevDestino = nodoOrigen;
			nodoOrigen = sigOrigen;
			if (nodoOrigen)
				sigOrigen = nodoOrigen->siguiente;
		}
		else {
			// Avanzar en la lista destino
			prevDestino = nodoDestino;
			nodoDestino = nodoDestino->siguiente;
		}
	}

	// Si quedan nodos en origen, agregarlos al final de destino
	if (nodoOrigen != NULL) {
		if (prevDestino)
			prevDestino->siguiente = nodoOrigen;
		else
			destino->inicio = nodoOrigen;
		destino->fin = origen->fin;
	}

}


