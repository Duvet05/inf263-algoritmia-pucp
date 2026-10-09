#include <iostream>
#include <fstream>
using namespace std;

struct Nodo {
  int incidente;
  Nodo* sig = NULL;
};

struct Cola {
  Nodo* inicio = NULL;
  Nodo* fin = NULL;
  int longitud = 0;
};

struct Pila {
  Nodo* cima = NULL;
  int longitud = 0;
};

bool leerCola(Cola* cola);
bool leerPila(Pila* pila, const char* nombreArchivo);
void encolar(Cola* cola, Nodo* nodo);
Nodo* desencolar(Cola* cola);
void apilar(Pila* pila, Nodo* nodo);
Nodo* desapilar(Pila* pila);
void reiniciaCola(Cola* cola, int n, Pila* pila1, Pila* pila2);
void ordenarPila(Pila* pila, Pila* aux, int modo);
void reclasificaPilas(Pila* pila1, Pila* pila2);
void imprime(Cola *cola, Pila* pila1, Pila* pila2);

int main() {

  Cola cola;
  Pila pila1, pila2;

  if (!leerCola(&cola) || !leerPila(&pila1, "pila1.txt") || !leerPila(&pila2, "pila2.txt"))
    return 1;

  imprime(&cola, &pila1, &pila2);

  reiniciaCola(&cola, 8, &pila1, &pila2);
  imprime(&cola, &pila1, &pila2);
  
  reclasificaPilas(&pila1, &pila2);
  imprime(&cola, &pila1, &pila2);

  return 0;
}

bool leerCola(Cola* cola) {
  ifstream archivo("cola.txt");
  if(!archivo) {
    cout << "ERROR: No se puede abrir cola.txt" << endl;
    return false;
  }

  while (true) {
    int incidente;
    archivo >> incidente;
    if (archivo.eof())
      break;
    Nodo* nodo = new Nodo;
    nodo->incidente = incidente;
    encolar(cola, nodo);
  }

  archivo.close();
  return true;
}

bool leerPila(Pila* pila, const char* nombreArchivo) {
  ifstream archivo(nombreArchivo);
  if(!archivo) {
    cout << "ERROR: No se puede abrir cola.txt" << endl;
    return false;
  }

  while (true) {
    int incidente;
    archivo >> incidente;
    if (archivo.eof())
      break;
    Nodo* nodo = new Nodo;
    nodo->incidente = incidente;
    apilar(pila, nodo);
  }

  archivo.close();
  return true;
}

void encolar(Cola* cola, Nodo* nodo) {
  if (cola->inicio == NULL) {
    cola->inicio = nodo;
  }
  if (cola->fin != NULL) {
    cola->fin->sig = nodo;
  }
  cola->fin = nodo;
  (cola->longitud)++;
}

Nodo* desencolar(Cola* cola) {
  if (cola->inicio == NULL)
    return NULL;

  Nodo* nodo = cola->inicio;
  
  cola->inicio = nodo->sig;
  if (cola->inicio == cola->fin)
    cola->fin = NULL;
  
  nodo->sig = NULL;
  (cola->longitud)--;

  return nodo;
}

void apilar(Pila* pila, Nodo* nodo) {
  nodo->sig = pila->cima;
  pila->cima = nodo;
  (pila->longitud)++;
}

Nodo* desapilar(Pila* pila) {
  if (pila->cima == NULL)
    return NULL;

  Nodo* nodo = pila->cima;
  pila->cima = nodo->sig;
  
  nodo->sig = NULL;
  (pila->longitud)--;

  return nodo;
}

void reiniciaCola(Cola* cola, int n, Pila* pila1, Pila* pila2) {

  // Paso 1
  while (pila2->cima != NULL) {
    Nodo* nodo = desapilar(pila2);
    apilar(pila1, nodo);
  }
  // Paso 2
  ordenarPila(pila1, pila2, 0);
  // Paso 3
  int longitudCola = cola->longitud;
  int longitudPila1 = pila1->longitud;
  for (int i=0; i<longitudCola-longitudPila1; i++) {
    Nodo* nodo = desencolar(cola);
    encolar(cola, nodo);
  }
  for (int i=0; i<longitudPila1; i++) {
    Nodo* nodo = desencolar(cola);
    apilar(pila2, nodo);
  }
  for (int i=0; i<longitudPila1; i++) {
    Nodo* nodo = desapilar(pila1);
    encolar(cola, nodo);
  }
  for (int i=0; i<longitudCola-longitudPila1; i++) {
    Nodo* nodo = desencolar(cola);
    encolar(cola, nodo);
  }
}

void ordenarPila(Pila* pila, Pila* aux, int modo) {
int n = pila->longitud;
Nodo* nodoAux, *nodoAux2;
  for (int i=0; i<n-1; i++) {
    for (int j=0; j<n-i-1; j++) {
      if ((modo == 0 && pila->cima->incidente%100 > pila->cima->sig->incidente%100) ||
          (modo == 1 && pila->cima->incidente > pila->cima->sig->incidente)) {
        // Paso 1
        nodoAux = desapilar(pila);
        nodoAux2 = desapilar(pila);
        apilar(pila, nodoAux);
      }
      else {
        // Paso 1
        nodoAux2 = desapilar(pila);
      }
      // Paso 2
      for (int k=0; k<n-1; k++) {
        nodoAux = desapilar(pila);
        apilar(aux, nodoAux);
      }
      // Paso 3
      apilar(pila, nodoAux2);
      // Paso 4
      for (int k=0; k<n-1; k++) {
        nodoAux = desapilar(aux);
        apilar(pila, nodoAux);
      }
    }
    for (int k=0; k<i+1; k++) {
      // Paso 1
      nodoAux2 = desapilar(pila);
      // Paso 2
      for (int k=0; k<n-1; k++) {
        nodoAux = desapilar(pila);
        apilar(aux, nodoAux);
      }
      // Paso 3
      apilar(pila, nodoAux2);
      // Paso 4
      for (int k=0; k<n-1; k++) {
        nodoAux = desapilar(aux);
        apilar(pila, nodoAux);
      }
    }
  }
}

void reclasificaPilas(Pila* pila1, Pila* pila2) {
  // Todos los nodos se pasan a la pila2
  while (pila1->cima != NULL) {
    Nodo* nodoAux = desapilar(pila1);
    apilar(pila2, nodoAux);
  }
  // Se ordena la pila2
  ordenarPila(pila2, pila1, 1);
  // Se crea la cola auxiliar
  Cola colaAux;
  while (pila2->cima != NULL) {
    Nodo* nodoAux = desapilar(pila2);
    encolar(&colaAux, nodoAux);
  }
  
  while ((colaAux.inicio->incidente)/100 == 1) {
    Nodo* nodoAux = desencolar(&colaAux);
    apilar(pila2, nodoAux);
  }
  
  while (pila2->cima != NULL) {
    Nodo* nodoAux = desapilar(pila2);
    apilar(pila1, nodoAux);
  }
  while (colaAux.inicio != NULL) {
    Nodo* nodoAux = desencolar(&colaAux);
    apilar(pila1, nodoAux);
  }
  while ((pila1->cima->incidente)/100 == 2) {
    Nodo* nodoAux = desapilar(pila1);
    apilar(pila2, nodoAux);
  }
}

void imprime(Cola *cola, Pila* pila1, Pila* pila2) {
  cout << "Cola: ";
  for (Nodo* nodo=cola->inicio; nodo!=NULL; nodo=nodo->sig)
    cout << nodo->incidente << " ";
  cout << endl << endl;
  
  cout << "Pila 1: ";
  if (pila1->cima == NULL)
    cout << "La pila esta vacia";
  else for (Nodo* nodo=pila1->cima; nodo!=NULL; nodo=nodo->sig)
    cout << nodo->incidente << " ";
  cout << endl << endl;
  
  cout << "Pila 2: ";
  if (pila2->cima == NULL)
    cout << "La pila esta vacia";
  else for (Nodo* nodo=pila2->cima; nodo!=NULL; nodo=nodo->sig)
    cout << nodo->incidente << " ";
  cout << endl << endl;
}