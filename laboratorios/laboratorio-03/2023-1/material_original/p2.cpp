#include <iostream>
#include <fstream>
using namespace std;

struct Nodo {
	char categoria;
	int impacto;
	Nodo* sig = NULL;	
};

struct Lista {
	Nodo *inicio = NULL;
	Nodo *fin = NULL;
	int longitud = 0;
};

int leerDatos(Lista *lista, char* nombre);
void insertarNodo(Lista *lista, Nodo *nodo);
Nodo* removerNodo(Lista *lista);
void unir(Lista *destino, Lista *origen);
void imprime(Lista *lista);

int main() {
	
	Lista A, B, C, D, E;
	
	leerDatos(&A, "A.txt");
	leerDatos(&B, "B.txt");
	leerDatos(&C, "C.txt");
	leerDatos(&D, "D.txt");
	leerDatos(&E, "E.txt");
	
	unir(&A, &B);
	unir(&A, &C);
	unir(&A, &D);
	unir(&A, &E);
	
	imprime(&A);
	
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
		Nodo* nodo = new Nodo;
		nodo->categoria = categoria;
		nodo->impacto = impacto;
		insertarNodo(lista, nodo);
	}
	
	archivo.close();
	return 0;
}

void insertarNodo(Lista *lista, Nodo *nodo) {
	if (lista->fin != NULL)
		lista->fin->sig = nodo;
	
	lista->fin = nodo;
	
	if (lista->inicio == NULL)
		lista->inicio = nodo;
	
	(lista->longitud)++;
}
Nodo* removerNodo(Lista *lista) {
	if (lista->inicio == NULL)
		return NULL;
		
	Nodo* nodo = lista->inicio;
	lista->inicio = nodo->sig;
	(lista->longitud)--;
	
	return nodo;
}

void insertarNodoEnFormaOrdenada(Lista *lista, Nodo *nuevoNodo) {
	
	if (lista->inicio == NULL) {
		lista->inicio = nuevoNodo;
		lista->fin = nuevoNodo;
	}
	else {
		Nodo *nodo=lista->inicio, *prev=NULL;
		while (nodo != NULL) {
			if (nuevoNodo->impacto > nodo->impacto ||
				(nuevoNodo->impacto == nodo->impacto && nuevoNodo->categoria < nodo->categoria)) {
				if (prev)
					prev->sig = nuevoNodo;
				else
					lista->inicio = nuevoNodo;
				nuevoNodo->sig = nodo;
				break;
			}
			prev = nodo;
			nodo = nodo->sig;
		}
		if (nodo == NULL) {
			lista->fin->sig = nuevoNodo;
			lista->fin = nuevoNodo;
		}
	}
	(lista->longitud)++;
}

void unir(Lista *destino, Lista *origen) {
	
	// Verificar si puedo unir el final del destino con el inicio del origen
	if (destino->fin != NULL && origen->inicio != NULL) {
		if (destino->fin->impacto > origen->inicio->impacto ||
			(destino->fin->impacto == origen->inicio->impacto && destino->fin->categoria < origen->inicio->categoria)) {
			destino->fin->sig = origen->inicio;
			destino->fin = origen->fin;
			destino->longitud += origen->longitud;
			origen->inicio = NULL;
			origen->fin = NULL;
			origen->longitud = 0;
			return;
		}
	}


	int n = origen->longitud;
	for (int i=0; i<n; i++) {
		Nodo* nodo = removerNodo(origen);
		insertarNodoEnFormaOrdenada(destino, nodo);
	}
}

void imprime(Lista *lista) {
	for (Nodo *nodo=lista->inicio; nodo != NULL; nodo=nodo->sig) {
		cout << nodo->categoria << " " << nodo->impacto << endl;
	}
	cout << endl;
}


