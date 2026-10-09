#include <iostream>
using namespace std;
#include "../ArbolesBinarios/funcionesArbolesBinarios.h"

// 14 -> 1110
// 7
// 3
// 1
// 0
void convertirABinario(int numero, int arreglo[], int &indice) {
  if (numero == 0) return;
  convertirABinario(numero / 2, arreglo, indice);
  arreglo[indice++] = numero % 2;
}

bool hallarNumeroRecursivo(NodoArbol* nodo, int numero, int arreglo[], int indice, int n) {

  if (indice >= n) return true;
  if (nodo == nullptr) return false;

  if (nodo->izquierda && arreglo[indice] == nodo->izquierda->elemento) {
    return hallarNumeroRecursivo(nodo->izquierda, numero, arreglo, indice+1, n);
  }
  else if (nodo->derecha && arreglo[indice] == nodo->derecha->elemento) {
    return hallarNumeroRecursivo(nodo->derecha, numero, arreglo, indice+1, n);
  }
  return false;
}

bool hallarNumero(NodoArbol* nodo, int numero) {

  if (nodo == nullptr) return false;

  int arreglo[32];
  int n = 0;
  int indice = 0;

  convertirABinario(numero, arreglo, n);

  return hallarNumeroRecursivo(nodo, numero, arreglo, indice, n);
}



int main() {

  ArbolBinario arbol;
  arbol.raiz = nullptr;


  NodoArbol* A = crearNuevoNodoArbol(nullptr, 0, nullptr);
  NodoArbol* B = crearNuevoNodoArbol(nullptr, 1, nullptr);

  NodoArbol* C = crearNuevoNodoArbol(nullptr, 1, A);
  NodoArbol* D = crearNuevoNodoArbol(nullptr, 1, nullptr);
  NodoArbol* E = crearNuevoNodoArbol(B, 0, nullptr);

  NodoArbol* F = crearNuevoNodoArbol(C, 1, nullptr);
  NodoArbol* G = crearNuevoNodoArbol(D, 0, E);

  NodoArbol* H = crearNuevoNodoArbol(F, 1, G);
  NodoArbol* I = crearNuevoNodoArbol(nullptr, 0, nullptr);

  arbol.raiz = crearNuevoNodoArbol(H, 0, I);

  if (hallarNumero(arbol.raiz, 25)) {
    cout << "El numero 25 se encuentra en el arbol." << endl;
  } else {
    cout << "El numero 25 no se encuentra en el arbol." << endl;
  }


  return 0;
}
