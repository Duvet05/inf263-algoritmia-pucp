#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

struct Nodo {
  int calorias;
  Nodo* sig = NULL;
};

struct Lista {
  Nodo* inicio = NULL;
  Nodo* fin = NULL;
  char tipo;
  int longitud = 0;
};

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
void insertarNodo(Lista *lista, Nodo* nodo);
void imprimeLista(Lista lista);
bool leerFormula(Formula *formula);
bool determinarPosibleCombinacion(Listas listas, Formula* formula);
int cargarCromosoma(int* cromosoma, int tamano_cromosoma, int i);
bool verificarSumaDeCalorias(int *cromosoma, Lista lista, LineaFormula lf);
void guardarCombinacion(int *cromosoma, Lista lista, Formula* formula, int i);
void imprimeCombinaciones(Formula formula);
void crearListaFinal(Formula *formula);
void moverLista(Lista *destino, Lista *origen);
Nodo* removerNodo(Lista* lista);
void moverListaFormaOrdenada(Lista *destino, Lista *origen);

int main() {

  Listas listas;
  Formula formula;

  if (!leerDatos(&listas))
    return 1;
  if (!leerFormula(&formula))
    return 1;

  if (determinarPosibleCombinacion(listas, &formula)) {
    imprimeCombinaciones(formula);
    crearListaFinal(&formula);
  }

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
      Nodo* nuevoNodo = new Nodo;
      nuevoNodo->calorias = calorias;
      insertarNodo(&(listas->arreglo[i]), nuevoNodo);
    }
  }
  archivo.close();
  return true;
}

void insertarNodo(Lista *lista, Nodo* nuevoNodo) {

  if (lista->inicio == NULL) {
    lista->inicio = nuevoNodo;
  }
  else {
    lista->fin->sig = nuevoNodo;
  }
  lista->fin = nuevoNodo;
  (lista->longitud)++;
}

void imprimeLista(Lista lista) {
  cout << lista.tipo << endl;
  for (Nodo* nodo = lista.inicio; nodo != NULL; nodo = nodo->sig) {
    cout << nodo->calorias << " ";
  }
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
    int *cromosoma = new int[lista.longitud];
    int combinaciones = pow(2, lista.longitud);
    int j;
    for (j=1; j<combinaciones; j++) {
      int cantidadUnos = cargarCromosoma(cromosoma, lista.longitud, j);
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
  for (Nodo* nodo=lista.inicio; nodo!=NULL; nodo=nodo->sig) {
    if (cromosoma[i])
      sumaDeCalorias += nodo->calorias;
    i++;
  }
  return sumaDeCalorias <= lf.totalCaloriasMaxima;
}

void guardarCombinacion(int *cromosoma, Lista lista, Formula* formula, int i) {
  int j=0;
  for (Nodo* nodo=lista.inicio; nodo!=NULL; nodo=nodo->sig) {
    if (cromosoma[j]) {
      Nodo* nuevoNodo = new Nodo;
      nuevoNodo->calorias = nodo->calorias;
      insertarNodo(&(formula->arreglo[i].lista), nuevoNodo);
    }
    j++;
  }
  formula->arreglo[i].lista.tipo = lista.tipo;
}

void imprimeCombinaciones(Formula formula) {
  for (int i=0; i<formula.cantidad; i++) {
    LineaFormula lf = formula.arreglo[i];
    cout << lf.tipo << endl;
    for (Nodo* nodo = lf.lista.inicio; nodo != NULL; nodo = nodo->sig) {
      cout << nodo->calorias << " ";
    }
    cout << endl << endl;
  }
}

void crearListaFinal(Formula *formula) {

  moverLista(&(formula->listaFinal), &(formula->arreglo[0].lista));
  formula->listaFinal.tipo = formula->arreglo[0].lista.tipo;

  for (int i=1; i<formula->cantidad; i++) {
    moverListaFormaOrdenada(&(formula->listaFinal), &(formula->arreglo[i].lista));
    cout << "Combinando la lista " << formula->listaFinal.tipo << " con la lista " << formula->arreglo[i].lista.tipo << endl;
    imprimeLista(formula->listaFinal);
    cout << endl << endl;
  }

}

void moverLista(Lista *destino, Lista *origen) {

  while (true) {
    Nodo* nodoRemovido = removerNodo(origen);
    if (nodoRemovido == NULL)
      break;
    nodoRemovido->sig = NULL;
    insertarNodo(destino, nodoRemovido);
  }
}

Nodo* removerNodo(Lista* lista) {
  if (lista->inicio == NULL)
    return NULL;
  
  Nodo* nodo = lista->inicio;
  lista->inicio = nodo->sig;
  if (lista->longitud == 1) {
    lista->fin = NULL;
  }
  (lista->longitud)--;

  return nodo;
}

void moverListaFormaOrdenada(Lista *destino, Lista *origen) {
  Nodo* nodoDestinoAnt = NULL;
  Nodo* nodoDestino = destino->inicio;
  Nodo *nodoOrigen = origen->inicio;
  while (nodoOrigen != NULL && nodoDestino != NULL) {
    // Si se cumple la condicion, se hace el cambio del nodoOrigen del origen al destino
    if (nodoOrigen->calorias <= nodoDestino->calorias) {
      Nodo* nodo = nodoOrigen;
      nodoOrigen = nodo->sig;
      // Primer nodo
      if (nodoDestinoAnt == NULL) {
        nodo->sig = nodoDestino;
        nodoDestinoAnt = nodo;
        destino->inicio = nodo;
      }
      // Nodo intermedio
      else {
        nodo->sig = nodoDestino;
        nodoDestinoAnt->sig = nodo;
        nodoDestinoAnt = nodo;
      }
    }
    else {
      nodoDestinoAnt = nodoDestino;
      nodoDestino = nodoDestino->sig;
    }
  }
  // El ultimo nodo del origen va a al final de destino
  if (nodoOrigen != NULL && nodoDestino == NULL) {
    destino->fin->sig = nodoOrigen;
    destino->fin = nodoOrigen;
  }

  (destino->longitud) += (origen->longitud);
  origen->longitud = 0;
  origen->inicio = NULL;
  origen->fin = NULL;
}
