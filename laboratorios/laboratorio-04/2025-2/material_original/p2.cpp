#include "./ArbolBinario/BibliotecaArbolBinario/funcionesArbolBinario.h"
#include "./ArbolBinario/BibliotecaArbolBinario/ArbolBinario.h"
#include "./ArbolBinario/BibliotecaCola/funcionesCola.h"
#include "./ArbolBinario/BibliotecaCola/Cola.h"

#include <iostream>
using namespace std;

void verificarOrden(NodoArbolBinario* nodo) {


  while (nodo->padre != nullptr && nodo->elemento.numero < nodo->padre->elemento.numero) {
    // Intercambiar los valores
    int temp = nodo->elemento.numero;
    nodo->elemento.numero = nodo->padre->elemento.numero;
    nodo->padre->elemento.numero = temp;

    // Moverse al padre
    nodo = nodo->padre;
  }
  

}

void insertarEnArbolBinarioCumulosMinimo(ArbolBinario &arbol, int valor, Cola &cola) {
  

  // caso base: si el árbol está vacío, plantamos el nuevo nodo
  if (esArbolVacio(arbol)) {

    plantarNodoArbolBinario(arbol.raiz, nullptr, {valor}, nullptr);
    // Encolamos el nuevo nodo en la cola
    encolar(cola, {arbol.raiz});
    return;
  }

  // Desencolamos el primer nodo de la cola

  NodoArbolBinario *nodoActual = cola.inicio->elemento.nodoArbol;

  if (nodoActual->izquierda == nullptr) {

    plantarNodoArbolBinario(nodoActual->izquierda, nullptr, {valor}, nullptr);
    nodoActual->izquierda->padre = nodoActual;

    encolar(cola, {nodoActual->izquierda});

    verificarOrden(nodoActual->izquierda);

  }
  else if (nodoActual->derecha == nullptr) {

    plantarNodoArbolBinario(nodoActual->derecha, nullptr, {valor}, nullptr);
    nodoActual->derecha->padre = nodoActual;

    // Si el nodo actual ya tiene ambos hijos, lo desencolamos

    desencolar(cola);
    encolar(cola, {nodoActual->derecha});

    verificarOrden(nodoActual->derecha);
  }

  




}

void crearArbolBinarioCumulosMinimo(ArbolBinario &arbol, int arr[], int n) {

  Cola cola;
  construir(cola);


  for (int i = 0; i < n; i++) {
    
    cout << endl << "Insertando " << arr[i] << " en el arbol." << endl;
    
    insertarEnArbolBinarioCumulosMinimo(arbol, arr[i], cola);
    
    recorrerEnOrden(arbol);

    cout << endl << endl;

  }

}

int main() {

  int arr[] =  {3, 5, 7, 9, 8, 6, 2};
  int n = 7;

  ArbolBinario arbol;
  construir(arbol);


  crearArbolBinarioCumulosMinimo(arbol, arr, n);

  


  return 0;
}

