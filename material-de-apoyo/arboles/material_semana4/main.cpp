#include "arbol.h"
#include <iostream>
using namespace std;

int main() {

  TArbol arbol = nullptr;

  inserta_nodo(&arbol, 5);
  inserta_nodo(&arbol, 3);
  inserta_nodo(&arbol, 2);
  inserta_nodo(&arbol, 6);

  en_orden(arbol);
  cout << endl;

  arbol = remover(arbol, 5);

  en_orden(arbol);
  cout << endl;

  TNodoArbol* nodo = buscar(arbol, 6);

  cout << nodo->valor << endl;

  cout << "Altura: " << altura(arbol) << endl;
  cout << "Cantidad de nodos: " << nodos(arbol) << endl;


  return 0;
}