#include ".\ArbolBinarioBusqueda\BibliotecaArbolBinarioBusqueda\funcionesArbolBinarioBusqueda.h"
#include ".\ArbolBinarioBusqueda\BibliotecaArbolBinarioBusqueda\ArbolBinarioBusqueda.h"
#include ".\BibliotecaPila\funcionesPila.h"
#include ".\BibliotecaPila\Pila.h"
#include <iostream>
using namespace std;

NodoArbolBinarioBusqueda* encontrarNodoSkyNerd(ArbolBinarioBusqueda& arbol) {

  Pila pila;
  construir(pila);

  apilar(pila, {arbol.raiz});

  while (true) {

    if (esPilaVacia(pila)) {
      cout << "No se encontro un nodo con flag 'S' y id 'Nerd'" << endl;
      break;
    }

    NodoArbolBinarioBusqueda* nodoActual = desapilar(pila).nodo;

      cout << "Flag: " << nodoActual->elemento.flag << ", ID: " << nodoActual->elemento.id << endl;

    if (nodoActual->elemento.flag == 'S') {
      cout << "Nodo encontrado" << endl;
      return nodoActual;
    }

    if (nodoActual->derecha)
      apilar(pila, {nodoActual->derecha});
    
    if (nodoActual->izquierda)
      apilar(pila, {nodoActual->izquierda});

  }

}

bool esHoja(NodoArbolBinarioBusqueda* nodo) {
  return nodo != nullptr && (nodo->izquierda == nullptr) && (nodo->derecha == nullptr);
}

void eliminarHijos(NodoArbolBinarioBusqueda* nodo) {
  if (nodo == nullptr) return;

  Pila pila;
  construir(pila);

  if (nodo->derecha)
    apilar(pila, {nodo->derecha});

  if (nodo->izquierda)
    apilar(pila, {nodo->izquierda});

  while (true) {

    if (esPilaVacia(pila)) {
      cout << "Eliminacion de hijos completada." << endl;
      break;
    }

    NodoArbolBinarioBusqueda* nodoActual = cima(pila).nodo;

    if (esHoja(nodoActual)) {

      nodoActual = desapilar(pila).nodo;

      cout << "Eliminando hoja con ID: " << nodoActual->elemento.id << endl;

      // indicarle al nodo padre que su hijo ya no existe
      if (nodoActual->padre != nullptr) {

        cout << "Nodo padre existe" << endl;
        if (nodoActual->padre->izquierda == nodoActual) {
          nodoActual->padre->izquierda = nullptr;
        } else if (nodoActual->padre->derecha == nodoActual) {
          nodoActual->padre->derecha = nullptr;
        }
      }

      delete nodoActual;
    }
    else {
      if (nodoActual->derecha)
        apilar(pila, {nodoActual->derecha});
      
      if (nodoActual->izquierda)
        apilar(pila, {nodoActual->izquierda});
    }

  }



}

int main() {

  ArbolBinarioBusqueda arbol;
  construir(arbol);
  
  ElementoArbolBinarioBusqueda valores[] = {{'N', 100},
                                             
                                            {'N', 50},
                                            {'N', 150},
                                            
                                            {'N', 25},
                                            {'N', 75},
                                            {'S', 125},
                                            {'N', 175},
                                          
                                            {'N', 110},
                                            {'N', 140},
                                            {'N', 200},

                                            {'N', 105},
                                            {'N', 115},
                                            {'N', 130}
                                          };

    for (ElementoArbolBinarioBusqueda elemento : valores) {
        insertar(arbol, elemento);
    }

    // recorrerEnOrden(arbol);

    NodoArbolBinarioBusqueda *nodoSkyNerd = encontrarNodoSkyNerd(arbol);

    eliminarHijos(nodoSkyNerd);

    recorrerEnOrden(arbol);

  return 0;
}




