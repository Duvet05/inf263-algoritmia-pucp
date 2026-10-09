#include <iostream>
#include "..\ArbolesBinarios\funcionesArbolesBB.h"
#include "..\ArbolesBinarios\funcionesArbolesBinarios.h"
using namespace std;
#define N 8


void inserta_nodo(int* codigo, ArbolBinarioBusqueda& arbol) {

  for (int i=0; i<N; i++) {
    bool esta = buscaArbol(arbol, codigo[i]);
    if (esta) {
      int mayor = maximoNodoABB(arbol);
      insertar(arbol, codigo[i] + mayor);
    }
    else {
      insertar(arbol, codigo[i]);
    }
  }
}

void recorrerEnOrden(NodoArbol* nodo, int* nodos, int& n) {
    if (!nodo) return;
    recorrerEnOrden(nodo->izquierda, nodos, n);
    nodos[n] = nodo->elemento;
    n++;
    recorrerEnOrden(nodo->derecha, nodos, n);
}

NodoArbol* construirArbolBalanceado(int* nodos, int start, int end) {
    if (start > end) return nullptr;
    
    int mid = start + (end - start) / 2; // Calcular el punto medio
    NodoArbol* node = new NodoArbol; // Crear el nodo raíz
    node->elemento = nodos[mid];
    // Construir recursivamente los subárboles izquierdo y derecho
    node->izquierda = construirArbolBalanceado(nodos, start, mid - 1);
    node->derecha = construirArbolBalanceado(nodos, mid + 1, end);

    return node;
}

void balancea_arbol(ArbolBinarioBusqueda& arbol) {
  int cantidadNodos = numeroNodos(arbol.arbolBinario);
  int* nodos = new int[cantidadNodos];
  int n = 0;
  recorrerEnOrden(arbol.arbolBinario.raiz, nodos, n);
  destruirArbolBB(arbol);
  arbol.arbolBinario.raiz = construirArbolBalanceado(nodos, 0, cantidadNodos-1);
  delete[] nodos;
}

NodoArbol* suma_arboles_recursivo(NodoArbol* a, NodoArbol* b) {

  if (a == nullptr)
    return b;
  if (b == nullptr)
    return a;

  int suma = a->elemento + b->elemento;
  NodoArbol* nuevoNodo = new NodoArbol;
  nuevoNodo->elemento = suma;
  nuevoNodo->izquierda = suma_arboles_recursivo(a->izquierda, b->izquierda);
  nuevoNodo->derecha = suma_arboles_recursivo(a->derecha, b->derecha);
  return nuevoNodo;
}

bool esABB(NodoArbol* nodo) {
  if (nodo == nullptr)
    return true;
  bool izq = true, der = true;
  if (nodo->izquierda != nullptr)
    izq = nodo->elemento >= nodo->izquierda->elemento;
  if (nodo->derecha != nullptr)
    der = nodo->elemento <= nodo->derecha->elemento;
  return izq && der && esABB(nodo->izquierda) && esABB(nodo->derecha);
}

bool suma_arboles(ArbolBinarioBusqueda& a, ArbolBinarioBusqueda& b) {
  ArbolBinario suma;
  suma.raiz = suma_arboles_recursivo(a.arbolBinario.raiz, b.arbolBinario.raiz);
  return esABB(suma.raiz);
}

int main() {

  int codigo[] = {2, 5, 2, 1, 5, 6, 3, 4 };

  ArbolBinarioBusqueda arbol;
  construir(arbol.arbolBinario);

  inserta_nodo(codigo, arbol);

  recorrerEnOrden(arbol.arbolBinario);
  cout << endl << "raiz: " << arbol.arbolBinario.raiz->elemento << endl;

  balancea_arbol(arbol);
  recorrerEnOrden(arbol.arbolBinario);
  cout << endl << "raiz: " << arbol.arbolBinario.raiz->elemento << endl;
  
  ArbolBinarioBusqueda arbolAux;
  construir(arbolAux);

  insertar(arbolAux, 3);

  insertar(arbolAux, 1);
  insertar(arbolAux, 2);

  insertar(arbolAux, 5);
  insertar(arbolAux, 4);
  insertar(arbolAux, 6);
  insertar(arbolAux, 7);

  bool acceso = suma_arboles(arbol, arbolAux);

  if (acceso)
    cout << "Acceso otorgado" << endl;
  else
    cout << "Acceso denegado" << endl;

  return 0; 
}