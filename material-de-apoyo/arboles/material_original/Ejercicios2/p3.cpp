#include "../ArbolesBinarios/funcionesArbolesBinarios.h"
#include "../ArbolesBinarios/funcionesArbolesBB.h"
#include <iostream>
#include <climits>
using namespace std;

int hallarHojaDeMenorNivel(NodoArbol* nodo, int &nivel) {

  if (nodo == nullptr) {
    nivel = INT_MAX;
    return -1;
  }

  if (nodo->izquierda == nullptr && nodo->derecha == nullptr)
    return nodo->elemento;

  nivel++;

  int nivelIzq = nivel;
  int nivelDer = nivel;
  int izq = hallarHojaDeMenorNivel(nodo->izquierda, nivelIzq);
  int der = hallarHojaDeMenorNivel(nodo->derecha, nivelDer);

  if (nivelIzq <= nivelDer) {
    nivel = nivelIzq;
    return izq;
  }
  nivel = nivelDer;
  return der;
}


int hallarHojaDeMayorNivel(NodoArbol* nodo, int &nivel) {

  if (nodo == nullptr) {
    nivel = INT_MIN;
    return -1;
  }

  if (nodo->izquierda == nullptr && nodo->derecha == nullptr)
    return nodo->elemento;

  nivel++;

  int nivelIzq = nivel;
  int nivelDer = nivel;
  int izq = hallarHojaDeMayorNivel(nodo->izquierda, nivelIzq);
  int der = hallarHojaDeMayorNivel(nodo->derecha, nivelDer);

  if (nivelIzq >= nivelDer) {
    nivel = nivelIzq;
    return izq;
  }
  nivel = nivelDer;
  return der;
}

int main() {

  ArbolBinarioBusqueda a;
  construir(a);
  insertar(a, 50);
  insertar(a, 40);
  insertar(a, 80);
  insertar(a, 15);
  insertar(a, 70);
  insertar(a, 52);
  insertar(a, 77);
  insertar(a, 92);
  insertar(a, 73);
  insertar(a, 98);

  int nivel = 0;
  int hoja = hallarHojaDeMenorNivel(a.arbolBinario.raiz, nivel);
  
  cout << "Menor nivel:" << endl;
  cout << "Hoja: " << hoja << endl;
  cout << "Nivel: " << nivel << endl;

  nivel = 0;
  hoja = hallarHojaDeMayorNivel(a.arbolBinario.raiz, nivel);

  cout << "Mayor nivel:" << endl;
  cout << "Hoja: " << hoja << endl;
  cout << "Nivel: " << nivel << endl;

  return 0;
}