#include <iostream>
using namespace std;

struct Nodo {
  int elemento;
  Nodo* sig = nullptr;
};

struct Pila {
  Nodo* cima = nullptr;
};

void apilar(Nodo*& cima, int elemento) {

  Nodo* nodo = new Nodo;
  nodo->elemento = elemento;
  nodo->sig = cima;
  cima = nodo;
}

int desapilar(Nodo*& cima) {

  if (cima == nullptr)
    return -1;

  Nodo* nodo = cima;
  cima = nodo->sig;
  int elemento = nodo->elemento;
  delete nodo;
  return elemento;
}

void mostrar(Pila& pila) {
  for (Nodo* nodo = pila.cima; nodo != nullptr; nodo = nodo->sig)
    cout << nodo->elemento << " ";
  cout << endl;
}

void copiar(Nodo*& copia, Nodo*& original) {

  if (original == nullptr) {
    return;
  }
  
  int elemento = desapilar(original);

  copiar(copia, original);

  apilar(copia, elemento);
  apilar(original, elemento);
}

int main() {

  Pila original;

  apilar(original.cima, 4);
  apilar(original.cima, 3);
  apilar(original.cima, 2);
  apilar(original.cima, 1);

  mostrar(original);

  Pila copia;

  copiar(copia.cima, original.cima);

  mostrar(copia);

  return 0;
}
