#include "../ArbolesBinarios/funcionesArbolesBinarios.h"
#include "../ArbolesBinarios/funcionesArbolesBB.h"
#include <iostream>
using namespace std;

NodoArbol* insertarArreglo(int *arr, int n, int nivel, int i) {

  if (n < nivel)
    return nullptr;

  NodoArbol* izq = insertarArreglo(arr, n, nivel+1, 0);
  NodoArbol* der = insertarArreglo(arr, n, nivel+1, 1);

  if (nivel == 0)
    return crearNuevoNodoArbol(izq, 0, der);

  return crearNuevoNodoArbol(izq, arr[nivel-1] * 10 + i, der);
}

int hallarCantidadCombinaciones(NodoArbol* nodo, int pesoTotal, int sumaAcum) {

  if (nodo == nullptr)
    return 0;

  int incremento = nodo->elemento % 10 ? ((nodo->elemento) / 10) : 0;
  
  if (sumaAcum + incremento == pesoTotal)
    return 1;
  
  if (sumaAcum + incremento < pesoTotal)
    sumaAcum += incremento;

  int izq = hallarCantidadCombinaciones(nodo->izquierda, pesoTotal, sumaAcum);
  int der = hallarCantidadCombinaciones(nodo->derecha, pesoTotal, sumaAcum);
  
  return izq + der;
}

int main() {

  int arr[] = {10, 50, 20, 30, 40};
  int n = 5;

  ArbolBinario arbol;
  arbol.raiz = insertarArreglo(arr, n, 0, 0);

  recorrerEnOrden(arbol);

  int cantidadCombinaciones = hallarCantidadCombinaciones(arbol.raiz, 70, 0);
  cout << endl << cantidadCombinaciones << endl;

  return 0;
}