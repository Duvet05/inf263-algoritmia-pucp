#include "../ArbolesBinarios/funcionesArbolesBinarios.h"
#include "../ArbolesBinarios/funcionesArbolesBB.h"
#include <iostream>
using namespace std;


bool similares(NodoArbol* r1, NodoArbol* r2) {

  if (r1 == nullptr && r2 == nullptr)
    return true;
  if (r1 == nullptr || r2 == nullptr)
    return false;

  return similares(r1->izquierda, r2->izquierda) && similares(r1->derecha, r2->derecha);

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
  insertar(b, 6);
  insertar(b, 3);
  insertar(b, 2);
  insertar(b, 4);
  insertar(b, 7);
  insertar(b, 8);


  ArbolBinarioBusqueda c;
  construir(c);
  insertar(c, 6);
  insertar(c, 3);

  cout << similares(a.arbolBinario.raiz, b.arbolBinario.raiz) << endl; 
  cout << similares(a.arbolBinario.raiz, c.arbolBinario.raiz) << endl; 

  return 0;
}