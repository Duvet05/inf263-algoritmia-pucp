#include "../ArbolesBinarios/funcionesArbolesBinarios.h"
#include "../ArbolesBinarios/funcionesArbolesBB.h"
#include <iostream>
using namespace std;

NodoArbol* combinar(NodoArbol* a, NodoArbol* b) {

  if (a == nullptr)
    return b;
  if (b == nullptr)
    return a;

  NodoArbol* nodo = crearNuevoNodoArbol(combinar(a->izquierda, b->izquierda),
                                        a->elemento + b->elemento,
                                        combinar(a->derecha, b->derecha));

  return nodo;

}

bool esABB(NodoArbol* nodo) {

  if (nodo == nullptr)
    return true;

  bool izq = true;
  if (nodo->izquierda != nullptr)
    izq = nodo->elemento >= nodo->izquierda->elemento;
  
  bool der = true;
  if (nodo->derecha != nullptr)
    der = nodo->elemento <= nodo->derecha->elemento;

  return izq && der && esABB(nodo->izquierda) && esABB(nodo->derecha);
}

int main() {

  ArbolBinarioBusqueda a;
  construir(a);
  insertar(a, 10);
  insertar(a, 7);
  insertar(a, 15);
  insertar(a, 21);
  insertar(a, 40);

  ArbolBinarioBusqueda b;
  construir(b);
  insertar(b, 12);
  insertar(b, 1);
  insertar(b, 31);
  insertar(b, 23);
  insertar(b, 18);
  insertar(b, 40);

  ArbolBinarioBusqueda c;
  c.arbolBinario.raiz = combinar(a.arbolBinario.raiz, b.arbolBinario.raiz);

  recorrerEnOrden(c.arbolBinario);

  cout << endl << esABB(c.arbolBinario.raiz) << endl;

  return 0;
}


