#include "../ArbolesBinarios/funcionesArbolesBinarios.h"
#include "../ArbolesBinarios/funcionesArbolesBB.h"
#include <iostream>
using namespace std;

bool contieneA(NodoArbol* a, NodoArbol* b) {

  if (b == nullptr)
    return true;
  if (a == nullptr)
    return false;

  if (a->elemento == b->elemento) {
    return contieneA(a->izquierda, b->izquierda) && contieneA(a->derecha, b->derecha);
  }
  else
    return contieneA(a->izquierda, b) || contieneA(a->derecha, b);
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

  ArbolBinarioBusqueda b;
  construir(b);
  insertar(b, 5);
  insertar(b, 2);
  insertar(b, 1);

  ArbolBinarioBusqueda c;
  construir(c);
  insertar(c, 2);
  insertar(c, 1);

  ArbolBinarioBusqueda d;
  construir(d);
  insertar(d, 5);
  insertar(d, 2);
  insertar(d, 10);

  cout << contieneA(a.arbolBinario.raiz, b.arbolBinario.raiz) << endl;
  cout << contieneA(a.arbolBinario.raiz, c.arbolBinario.raiz) << endl;
  cout << contieneA(a.arbolBinario.raiz, d.arbolBinario.raiz) << endl;

  return 0;
}
