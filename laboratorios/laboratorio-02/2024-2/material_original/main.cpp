#include <iostream>
using namespace std;

struct Nodo {
  int n;
  Nodo* sig = nullptr;
};

struct Lista {
  Nodo* ini = nullptr;
  Nodo* fin = nullptr;
  int longitud = 0;
};

void insertar(Lista& lista, Nodo* nodo) {

  if (lista.longitud == 0) {
    lista.ini = nodo;
  }
  else {
    lista.fin->sig = nodo;
  }
  lista.fin = nodo;
  (lista.longitud)++;
}

void unirDeFormaOrdenada(Lista& A, Lista& B) {
  
  Nodo* prevA = nullptr;
  Nodo* nodoA = A.ini;
  Nodo* prevB = nullptr;
  Nodo* nodoB = B.ini;
  
  while (nodoA != nullptr && nodoB != nullptr) {
    if (nodoA->n < nodoB->n) {
      prevA = nodoA;
      nodoA = nodoA->sig;
    }
    else {
      Nodo* nextB = nodoB->sig;

      if (prevA == nullptr) {
        A.ini = nodoB;
      }
      else {
        prevA->sig = nodoB;
      }

      nodoB->sig = nodoA;
      prevA = nodoB;

      nodoB = nextB;

      if (prevB == nullptr) {
        B.ini = nodoB;
      }

      (A.longitud)++;
      (B.longitud)--;
    }
  }

  // Unir el resto de B al final de A
  if (nodoB != nullptr) {
    if (A.fin != nullptr) {
      A.fin->sig = nodoB;
    }
    else {
      A.ini = nodoB;
    }
    A.fin = B.fin;
    A.longitud += B.longitud;
    B.ini = nullptr;
    B.fin = nullptr;
    B.longitud = 0;
  }

}

void imprime(const Lista& lista) {
  for (Nodo* r = lista.ini; r; r = r->sig) {
    cout << r->n << " ";
  }
  cout << endl;
}

int main() {

  Lista A, B;

  insertar(A, new Nodo{1});
  insertar(A, new Nodo{3});
  insertar(A, new Nodo{5});

  insertar(B, new Nodo{2});
  insertar(B, new Nodo{4});
  insertar(B, new Nodo{6});

  unirDeFormaOrdenada(A, B);

  imprime(A);

  return 0;
}

