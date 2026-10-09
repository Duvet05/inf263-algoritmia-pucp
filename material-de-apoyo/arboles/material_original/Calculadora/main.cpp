#include "../ArbolesBinarios/funcionesArbolesBinarios.h"
#include <iostream>
#include <cstdlib>
using namespace std;

struct NodoPila {
  NodoArbol* elemento;
  NodoPila* sig = NULL;
};

struct Pila {
  NodoPila* cima = NULL;
};

void apilar(Pila& pila, NodoArbol* elemento) {
  NodoPila* nodo = new NodoPila;
  nodo->elemento = elemento;
  nodo->sig = pila.cima;
  pila.cima = nodo;
}

NodoArbol* desapilar(Pila& pila) {

  if (pila.cima == NULL)
    return NULL;

  NodoPila* nodo = pila.cima;
  pila.cima = nodo->sig;
  NodoArbol* elemento = nodo->elemento;
  delete nodo;
  return elemento;
}

int recorrerEnOrdenRecursivoCalculadora(struct NodoArbol * nodo){
    if(not esNodoVacio(nodo)){
        int izq = recorrerEnOrdenRecursivoCalculadora(nodo->izquierda);
        int der = recorrerEnOrdenRecursivoCalculadora(nodo->derecha);
        if (not esNodoVacio(nodo->izquierda) && not esNodoVacio(nodo->derecha))
          switch(nodo->elemento) {
            case -1:
              return izq + der;
            case -2:
              return izq - der;
            case -3:
              return izq * der;
            case -4:
              return izq / der;
          }
        return nodo->elemento;
    }
    return 0;
}


int main() {

  struct ArbolBinario arbol;
  construir(arbol);
  
  struct Pila pila;

  // lectura de datos
  while (true) {
    cout << "Ingrese un operando u operador (+, -, *, /): ";
    char c = cin.get();
    if (c == '0')
      break;
    if (c == '+' || c == '-' || c == '*' || c == '/') {
      int elemento;
      switch (c) {
        case '+':
          elemento = -1;  break;
        case '-':
          elemento = -2;  break;
        case '*':
          elemento = -3;  break;
        case '/':
          elemento = -4;  break;
      }

      NodoArbol* operador2 = desapilar(pila);
      NodoArbol* operador1 = desapilar(pila);
      plantarArbolBinario(arbol, operador1, elemento, operador2);
      apilar(pila, arbol.raiz);

    }
    else {
      cin.unget();
      int elemento;
      cin >> elemento;
      plantarArbolBinario(arbol, NULL, elemento, NULL);
      apilar(pila, arbol.raiz);

    }
    // Lee enter
    cin.get();
  }

  // impresion en pre orden
  cout << endl;
  recorrerEnOrden(arbol);
  
  // resultado
  cout << endl;
  cout << "Resultado: " << recorrerEnOrdenRecursivoCalculadora(arbol.raiz) << endl;

  destruirArbolBinario(arbol);
  return 0;
}


