#include "./ArbolBinarioBusqueda/BibliotecaArbolBinarioBusqueda/funcionesArbolBinarioBusqueda.h"
#include "./ArbolBinarioBusqueda/BibliotecaArbolBinarioBusqueda/ArbolBinarioBusqueda.h"
#include "./Pila/BibliotecaPila/funcionesPila.h"
#include "./Pila/BibliotecaPila/Pila.h"
#include <iostream>
using namespace std;


int cantidadHijos(NodoArbolBinarioBusqueda* nodo) {
  int contador = 0;
  if (nodo->izquierda != nullptr) {
    contador++;
  }
  if (nodo->derecha != nullptr) {
    contador++;
  }
  return contador;
}

void procesarEliminacion(ArbolBinarioBusqueda &arbol) {

  Pila pila;
  construir(pila);

  NodoArbolBinarioBusqueda* nodo = arbol.raiz;
  apilar(pila, {nodo});

  while (true) {

    cout << "Pila actual: ";
    imprimir(pila);
    cout << endl;


    if (esPilaVacia(pila)) {
      break;
    }

    nodo = pila.inicio->elemento.nodo;

    int cantidad = cantidadHijos(nodo);

    if (cantidad == 2) {
      desapilar(pila);
      apilar(pila, {nodo->izquierda});
      apilar(pila, {nodo->derecha});
    }
    else if (cantidad == 1) {

      if (nodo->izquierda != nullptr) {
        cout << "Nodo con un hijo (izquierda): " << nodo->elemento.numero << endl;
        apilar(pila, {nodo->izquierda});
      }
      else {
        cout << "Nodo con un hijo (derecha): " << nodo->elemento.numero << endl;
        apilar(pila, {nodo->derecha});
      }
    }
    else {
      cout << "Nodo hoja: " << nodo->elemento.numero << endl;

      bool bandera = false;

      while (true) {

        NodoArbolBinarioBusqueda* nodoHoja = desapilar(pila).nodo;

        if (pila.inicio == nullptr) {
          return;
        }


        NodoArbolBinarioBusqueda* padre = pila.inicio->elemento.nodo;      


        if (padre->izquierda == nodoHoja) {
          padre->izquierda = nullptr;
          bandera = true;
        }
        else if (padre->derecha == nodoHoja) {
          padre->derecha = nullptr;
          bandera = true;
        }
        else {
          if (bandera)
            apilar(pila, {nodoHoja});
          break;
        }

        delete nodoHoja;
      }
    }
  }
}


int main() {

  ArbolBinarioBusqueda arbol;
  construir(arbol);

  insertar(arbol, {100});

  insertar(arbol, {50});
  insertar(arbol, {150});

  insertar(arbol, {25});
  insertar(arbol, {75});
  insertar(arbol, {125});
  insertar(arbol, {175});

  insertar(arbol, {30});
  insertar(arbol, {200});

  insertar(arbol, {28});

  recorrerEnOrden(arbol);

  procesarEliminacion(arbol);

  recorrerEnOrden(arbol);


  return 0;
}


