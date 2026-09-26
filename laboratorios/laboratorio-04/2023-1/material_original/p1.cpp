#include "./ArbolesBinarios/funcionesArbolesBinarios.h"
#include "./ArbolesBinarios/funcionesArbolesBB.h"
#include <iostream>
using namespace std;

struct NodoPila {
  NodoArbol* elemento;
  NodoPila* sig = nullptr;
};

struct Pila {
  NodoPila* inicio = nullptr;
  NodoPila* fin = nullptr;
};

void insertarEnPila(Pila& cola, NodoArbol* elemento) {
  if (elemento == nullptr)  
    return;
  
  NodoPila* nodo = new NodoPila;
  nodo->elemento = elemento;
  if (cola.fin != nullptr)
    cola.fin->sig = nodo;
  cola.fin = nodo;
  if (cola.inicio == nullptr)
    cola.inicio = cola.fin;
}

NodoArbol* removerDePila(Pila& cola) {
  if (cola.inicio == nullptr)
    return nullptr;

  NodoPila* nodo = cola.inicio;
  if (cola.inicio == cola.fin)
    cola.fin = nullptr;
  cola.inicio = nodo->sig;
  NodoArbol* elemento = nodo->elemento;
  delete nodo;
  return elemento;
}

int convertirAElemento(char tipo, int ghz) {
  // Z: 0, E: 1, S: 2
  switch(tipo) {
    case 'Z':
      return 0 * 1000 + ghz;
    case 'E':
      return 1 * 1000 + ghz;
    case 'S':
      return 2 * 1000 + ghz;
  }
}
void convertirDeElemento(int elemento, char& tipo, int& ghz) {

  int n = elemento % 10000;

  switch (n/1000) {
    case 0:
      tipo = 'Z'; break;
    case 1:
      tipo = 'E'; break;
    case 2:
      tipo = 'S'; break;
  }
  ghz = n % 1000;
}

void insertarEnArbol(int* arr, int* arrOrden, int n, ArbolBinarioBusqueda& ABB) {

  for (int i=0; i<n; i++) {
    insertar(ABB, arrOrden[i] * 10000 + arr[i]);
  }

}

bool detectar(ArbolBinarioBusqueda& arbol) {

  Pila cola;

  insertarEnPila(cola, arbol.arbolBinario.raiz);

  int elemento = -1;

  while (true) {

    if (cola.inicio == nullptr)
      break;

    NodoArbol* nodoArbol = removerDePila(cola);
    char tipo;
    int ghz;
    convertirDeElemento(nodoArbol->elemento, tipo, ghz);
    if (tipo == 'S' && ghz == 200) {
      elemento = nodoArbol->elemento;
      break;
    }
    
    insertarEnPila(cola, nodoArbol->izquierda);
    insertarEnPila(cola, nodoArbol->derecha);
  }
  if (elemento == -1)
    return false;

  NodoArbol* nodo = arbol.arbolBinario.raiz;
  int nivel = 1;
  while (true) {
    if (nodo->elemento == elemento) {
      cout << "Nivel: " << nivel << endl;
      break;
    }
    else if (nodo->elemento < elemento)
      nodo = nodo->derecha;
    else
      nodo = nodo->izquierda;
    nivel++;
  }
  return true;
}

int main() {

  int arr[] = {convertirAElemento('Z', 100),
               
               convertirAElemento('Z', 50),
               convertirAElemento('E', 200),
               
               convertirAElemento('E', 100),
               convertirAElemento('S', 50),
               convertirAElemento('S', 200),
               convertirAElemento('S', 150),
               
               convertirAElemento('S', 50),
               convertirAElemento('Z', 200),
               convertirAElemento('S', 100),
               convertirAElemento('E', 200),
               
               convertirAElemento('E', 50),
               convertirAElemento('E', 100),

               };

  int arrOrden[] = {  32,
                    
                      16,
                      48,

                      8,
                      24,
                      40,
                      56,

                      4,
                      12,
                      36,
                      40,

                      2,
                      10
                    };
  int n = 13;

  ArbolBinarioBusqueda arbol;
  construir(arbol);

  insertarEnArbol(arr, arrOrden, n, arbol);

  recorrerEnOrden(arbol.arbolBinario);

  cout << endl << detectar(arbol) << endl;

  return 0;
}