
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
#include "./ListaSimplementeEnlazada/BibliotecaLista/funcionesLista.h"
#include "./ListaSimplementeEnlazada/BibliotecaLista/Lista.h"

  char posiciones[4][30] = {"Portero", "Defensa", "Mediocampista", "Delantero"};

int longitudLista(const Lista & lista) {
  int longitud = 0;
  struct NodoLista * recorrido = lista.lista;
  while (recorrido != nullptr) {
    longitud++;
    recorrido = recorrido->siguiente;
  }
  return longitud;
}


int compararPosiciones(char pos1[30], char pos2[30], char posiciones[4][30]) {

  int indice1 = -1, indice2 = -1;
  for (int i = 0; i < 4; i++) {
    if (strcmp(pos1, posiciones[i]) == 0) {
      indice1 = i;
    }
    if (strcmp(pos2, posiciones[i]) == 0) {
      indice2 = i;
    }
  }
  
  return indice1 - indice2; // Retorna negativo si pos1 < pos2, positivo si pos1 > pos2, 0 si son iguales
}

int comparar(NodoLista * nodo1, NodoLista * nodo2) {
  int cmp = compararPosiciones(nodo1->elemento.posicion, nodo2->elemento.posicion, posiciones);

  if (cmp != 0) return cmp;
  return nodo1->elemento.codigo - nodo2->elemento.codigo;

}

void ordenarLista(Lista & lista) {
  // Implementar el algoritmo de ordenamiento (por ejemplo, burbuja)
  int n = longitudLista(lista);
  struct NodoLista * actual = lista.lista;
  struct NodoLista * siguiente;

  for (int i=0; i<n-1; i++) {
    siguiente = actual->siguiente;

    for (int j=0; j<n-i-1; j++) {
      if (comparar(actual, siguiente) > 0) {
        // Intercambiar los elementos
        ElementoLista temp = actual->elemento;
        actual->elemento = siguiente->elemento;
        siguiente->elemento = temp;
      }
      siguiente = siguiente->siguiente;
    }
    actual = actual->siguiente;
  }
} 

int main() {

  Lista lista;
  construir(lista);

  insertarAlFinal(lista, {3, "Carlos", "Delantero", 5});
  insertarAlFinal(lista, {1, "Ana", "Portero", 4});
  insertarAlFinal(lista, {4, "Luis", "Defensa", 3});
  insertarAlFinal(lista, {2, "Bea", "Defensa", 2});
  insertarAlFinal(lista, {5, "Eva", "Delantero", 1});

  ordenarLista(lista);

  imprimir(lista);

  return 0;
}


















