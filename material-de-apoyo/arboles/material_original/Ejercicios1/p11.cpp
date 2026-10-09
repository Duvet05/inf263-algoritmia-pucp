#include "../ArbolesBinarios/funcionesArbolesBinarios.h"
#include "../ArbolesBinarios/funcionesArbolesBB.h"
#include <iostream>
using namespace std;

void recorrer(NodoArbol* nodo, int* arr, int nivel) {

  if (nodo == nullptr)
    return;
  
  arr[nivel]++;

  recorrer(nodo->izquierda, arr, nivel+1);
  recorrer(nodo->derecha, arr, nivel+1);

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

  int niveles = altura(a.arbolBinario);
  int *arr = new int[niveles];

  for (int i=0; i<niveles; i++)
    arr[i] = 0;

  recorrer(a.arbolBinario.raiz, arr, 0);

  int max = 0;
  int nivel;
  for (int i=0; i<niveles; i++) {
    cout << arr[i] << endl;
    if (arr[i] > max) {
      max = arr[i];
      nivel = i;
    }
  }

  cout << "El nivel con mayor cantidad de nodos es: " << nivel << endl;

  return 0;
}


