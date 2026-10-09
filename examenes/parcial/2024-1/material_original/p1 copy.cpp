#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
#include "./BibliotecaLista/funcionesLista.h"
#include "./BibliotecaLista/Lista.h"
#include "./BibliotecaLista/NodoLista.h"
#include "./BibliotecaLista/ElementoLista.h"

struct Listas {
  Lista* arreglo;
  int cantidad;
};

struct LineaFormula {
  char tipo;
  int cantidadProductos;
  int totalCaloriasMaxima;
  Lista lista;
};

struct Formula {
  LineaFormula* arreglo;
  int cantidad;
  Lista listaFinal;
};

bool leerDatos(Listas *listas);
bool leerFormula(Formula *formula);
bool determinarPosibleCombinacion(Listas listas, Formula* formula);
int cargarCromosoma(int* cromosoma, int tamano_cromosoma, int i);
bool verificarSumaDeCalorias(int *cromosoma, Lista lista, LineaFormula lf);
void guardarCombinacion(int *cromosoma, Lista lista, Formula* formula, int i);
void imprimeCombinaciones(Formula formula);
void crearListaFinal(Formula *formula);
void moverLista(Lista *destino, Lista *origen);
void moverListaFormaOrdenada(Lista *destino, Lista *origen);
NodoLista* removerNodo(Lista* lista);

int main() {

  Listas listas;
  Formula formula;

  if (!leerDatos(&listas))
    return 1;
  if (!leerFormula(&formula))
    return 1;

  // if (determinarPosibleCombinacion(listas, &formula)) {
  //   imprimeCombinaciones(formula);
  //   crearListaFinal(&formula);
  // }

  return 0;
}

bool leerDatos(Listas *listas) {

  ifstream archivo("p1.txt");

  if (!archivo) {
    cout << "ERROR: No se puede abrir el archivo p1.txt" << endl;
    return false;
  }

  archivo >> listas->cantidad;
  listas->arreglo = new Lista[listas->cantidad];

  for (int i=0; i<listas->cantidad; i++) {
    archivo >> listas->arreglo[i].tipo;
    while (true) {
      int calorias;
      archivo >> calorias;
      if (archivo.fail()) {
        archivo.clear();
        break;
      }
      // Nodo* nuevoNodo = new Nodo;
      // nuevoNodo->calorias = calorias;
      // insertarNodo(&(listas->arreglo[i]), nuevoNodo);
      ElementoLista elemento;
      elemento.codigo = calorias;
      insertarAlFinal(listas->arreglo[i], elemento);
    }
  }
  archivo.close();
  return true;
}

bool leerFormula(Formula *formula) {
  ifstream archivo("p1formula.txt");
  if (!archivo) {
    cout << "ERROR: No se puede abrir p1formula.txt" << endl;
    return false;
  }

  archivo >> formula->cantidad;
  formula->arreglo = new LineaFormula[formula->cantidad];

  for (int i=0; i<formula->cantidad; i++) {
    archivo >> formula->arreglo[i].tipo;
    archivo >> formula->arreglo[i].cantidadProductos;
    archivo >> formula->arreglo[i].totalCaloriasMaxima;
  }

  archivo.close();
  return true;
}

bool determinarPosibleCombinacion(Listas listas, Formula* formula) {

  for (int i=0; i<formula->cantidad; i++) {
    LineaFormula lf = formula->arreglo[i];
    
    // Encontrando la lista con el tipo
    Lista lista;
    for (int j=0; j<listas.cantidad; j++) {
      if (listas.arreglo[j].tipo == lf.tipo) {
        lista = listas.arreglo[j];
        break;
      }
    }
    // Algoritmo de fuerza bruta usando el cromosoma
    int longitud = longitudLista(lista);
    int *cromosoma = new int[longitud];
    int combinaciones = pow(2, longitud);
    int j;
    for (j=1; j<combinaciones; j++) {
      int cantidadUnos = cargarCromosoma(cromosoma, longitud, j);
      // El cromosoma tiene la cantidad de elementos igual a la cantidad de productos de la lineaFormula
      if (cantidadUnos == lf.cantidadProductos) {
        if (verificarSumaDeCalorias(cromosoma, lista, lf)) {
          guardarCombinacion(cromosoma, lista, formula, i);
          break;
        }
      }
    }
    if (j==combinaciones)
      return false;
    delete []cromosoma;
  }

  return true;
}

int cargarCromosoma(int* cromosoma, int tamano_cromosoma, int i) {
	
  int cantidadUnos = 0;

	for (int j = 0; j < tamano_cromosoma; j++)
		cromosoma[j] = 0;
	
	for (int j = tamano_cromosoma - 1; i > 0; j--) { 
		cromosoma[j] = i % 2;
    cantidadUnos += (i % 2);		
		i /= 2;
	}
  return cantidadUnos;
}

bool verificarSumaDeCalorias(int *cromosoma, Lista lista, LineaFormula lf) {
  int sumaDeCalorias = 0;
  
  int i=0;
  for (NodoLista* nodo=lista.lista; nodo!=NULL; nodo=nodo->siguiente) {
    if (cromosoma[i])
      sumaDeCalorias += nodo->elemento.codigo;
    i++;
  }
  return sumaDeCalorias <= lf.totalCaloriasMaxima;
}

void guardarCombinacion(int *cromosoma, Lista lista, Formula* formula, int i) {
  int j=0;
  for (NodoLista* nodo=lista.lista; nodo!=NULL; nodo=nodo->siguiente) {
    if (cromosoma[j]) {
      // Nodo* nuevoNodo = new Nodo;
      // nuevoNodo->calorias = nodo->calorias;
      // insertarNodo(&(formula->arreglo[i].lista), nuevoNodo);
      ElementoLista elemento;
      elemento.codigo = nodo->elemento.codigo;
      insertarAlFinal(formula->arreglo[i].lista, elemento);
    }
    j++;
  }
  formula->arreglo[i].lista.tipo = lista.tipo;
}

void imprimeCombinaciones(Formula formula) {
  for (int i=0; i<formula.cantidad; i++) {
    LineaFormula lf = formula.arreglo[i];
    cout << lf.tipo << endl;
    imprimir(lf.lista);
    cout << endl << endl;
  }
}

void crearListaFinal(Formula *formula) {

  moverLista(&(formula->listaFinal), &(formula->arreglo[0].lista));
  formula->listaFinal.tipo = formula->arreglo[0].lista.tipo;

  for (int i=1; i<formula->cantidad; i++) {
    moverListaFormaOrdenada(&(formula->listaFinal), &(formula->arreglo[i].lista));
    cout << "Combinando la lista " << formula->listaFinal.tipo << " con la lista " << formula->arreglo[i].lista.tipo << endl;
    imprimir(formula->listaFinal);
    cout << endl << endl;
  }

}

void moverLista(Lista *destino, Lista *origen) {

  while (true) {
    NodoLista* nodoRemovido = removerNodo(origen);
    if (nodoRemovido == NULL)
      break;
    nodoRemovido->siguiente = NULL;
    // insertarNodo(destino, nodoRemovido);
    ElementoLista elemento;
    elemento.codigo = nodoRemovido->elemento.codigo;
    insertarAlFinal(*destino, elemento);
  }
}

void moverListaFormaOrdenada(Lista *destino, Lista *origen) {
  NodoLista* nodoDestinoAnt = NULL;
  NodoLista* nodoDestino = destino->lista;
  NodoLista *nodoOrigen = origen->lista;
  while (nodoOrigen != NULL && nodoDestino != NULL) {
    // Si se cumple la condicion, se hace el cambio del nodoOrigen del origen al destino
    if (nodoOrigen->elemento.codigo <= nodoDestino->elemento.codigo) {
      NodoLista* nodo = nodoOrigen;
      nodoOrigen = nodo->siguiente;
      // Primer nodo
      if (nodoDestinoAnt == NULL) {
        nodo->siguiente = nodoDestino;
        nodoDestinoAnt = nodo;
        destino->lista = nodo;
      }
      // Nodo intermedio
      else {
        nodo->siguiente = nodoDestino;
        nodoDestinoAnt->siguiente = nodo;
        nodoDestinoAnt = nodo;
      }
    }
    else {
      nodoDestinoAnt = nodoDestino;
      nodoDestino = nodoDestino->siguiente;
    }
  }
  // El ultimo nodo del origen va a al final de destino
  if (nodoOrigen != NULL && nodoDestino == NULL) {


    // Moverme al final de destino
    for ( ; nodoDestinoAnt->siguiente != NULL; nodoDestinoAnt = nodoDestinoAnt->siguiente);
    nodoDestinoAnt->siguiente = nodoOrigen;

    // destino->fin->sig = nodoOrigen;
    // destino->fin = nodoOrigen;
    
  
  }

  construir(*origen);
}

NodoLista* removerNodo(Lista* lista) {
  if (lista->lista == NULL)
    return NULL;
  
  NodoLista* nodo = lista->lista;
  lista->lista = nodo->siguiente;

  return nodo;
}
