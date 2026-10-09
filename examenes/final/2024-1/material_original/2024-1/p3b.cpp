#include <iostream>
using namespace std;

struct Nodo {
  int elemento;
  Nodo* sig = nullptr;
};

struct ListaCircular {
  Nodo* ini = nullptr;
  Nodo* fin = nullptr;
  int longitud = 0;
};

void insertar(ListaCircular& lista, int elemento) {
  Nodo* nodo = new Nodo;
  nodo->elemento = elemento;
  if (lista.ini == nullptr)
    lista.ini = nodo;
  if (lista.fin != nullptr)
    lista.fin->sig = nodo;
  lista.fin = nodo;
  nodo->sig = lista.ini;
  lista.longitud++;
}

void remover(ListaCircular& lista, Nodo* nodoPrevio) {
  
  if (nodoPrevio->sig == lista.ini)
    lista.ini = nodoPrevio->sig->sig;
  if (nodoPrevio->sig == lista.fin)
    lista.fin = nodoPrevio->sig->sig;
  
  Nodo* nodoAEliminar = nodoPrevio->sig;
  nodoPrevio->sig = nodoPrevio->sig->sig;
  delete nodoAEliminar;
  lista.longitud--;
}

int main() {

  ListaCircular lista;
  int cantidadEmpleados = 10;
  int k = 7;

  for (int i=0; i<cantidadEmpleados; i++)
    insertar(lista, i+1);

  Nodo* nodoPrevio = lista.ini;
  for (int i=0; i<k-2; i++)
    nodoPrevio = nodoPrevio->sig;

  while (lista.longitud > 1) {
    remover(lista, nodoPrevio);
    for (int i=0; i<k-1; i++)
      nodoPrevio = nodoPrevio->sig;
  }
  cout << "El elegido es: " << lista.ini->elemento << endl;

  return 0;
}


