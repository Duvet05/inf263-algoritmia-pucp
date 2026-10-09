#include "../ArbolesBinarios/funcionesArbolesBinarios.h"
#include "../ArbolesBinarios/funcionesArbolesBB.h"
#include <iostream>
using namespace std;

void perimetroIzq(NodoArbol* nodo) {

  if (nodo == nullptr || nodo->izquierda == nullptr)
    return;
  
  cout << nodo->elemento << " ";

  perimetroIzq(nodo->izquierda);
}

void perimetroDer(NodoArbol* nodo) {

  if (nodo == nullptr || nodo->derecha == nullptr)
    return;
  
  cout << nodo->elemento << " ";

  perimetroDer(nodo->derecha);
}

void perimetroHojas(NodoArbol* nodo) {

  if (nodo == nullptr)
    return;

  perimetroHojas(nodo->izquierda);

  if (nodo->izquierda == nullptr && nodo->derecha == nullptr)
    cout << nodo->elemento << " ";

  perimetroHojas(nodo->derecha);
}

void perimetro(ArbolBinarioBusqueda ABB) {

  perimetroIzq(ABB.arbolBinario.raiz);
  perimetroHojas(ABB.arbolBinario.raiz);
  perimetroDer(ABB.arbolBinario.raiz->derecha);

}

int main() {

  ArbolBinarioBusqueda a;
  construir(a);
  insertar(a, 5);
  insertar(a, 2);
  insertar(a, 1);
  insertar(a, 3);
  insertar(a, 6);
  insertar(a, 7);

  perimetro(a);

  return 0;
}
