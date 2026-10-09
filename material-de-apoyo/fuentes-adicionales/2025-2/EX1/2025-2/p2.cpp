#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
#include "./Pila/BibliotecaPila/funcionesPila.h"
#include "./Pila/BibliotecaPila/Pila.h"


// Función recursiva de Hanoi
void hanoi(int n, Pila& origen, Pila& auxiliar, Pila& destino) {
    
    if (n <= 0) return;

  
    if (n == 1) {
        ElementoPila disco = desapilar(origen);
        apilar(destino, disco);
        return;
    }

    // Mover n-1 discos de origen a auxiliar
    hanoi(n - 1, origen, destino, auxiliar);

    // Mover el disco más grande al destino
    ElementoPila disco = desapilar(origen);
    apilar(destino, disco);

    // Mover los n-1 discos de auxiliar a destino
    hanoi(n - 1, auxiliar, origen, destino);
}

void fusionar(Pila &a, Pila &b, Pila &c) {

  Pila aux;
  construir(aux);

  // Siempre se compara la cima de ambas pilas
  int n = 0;
  while (a.inicio != nullptr && b.inicio != nullptr) {
    cout << "Iteracion " << n+1 << endl;
    if (a.inicio->elemento.numero > b.inicio->elemento.numero) {
      // hanoi desde aux hasta c
      hanoi(n, aux, a, c);
      // movemos la cima de b a aux
      ElementoPila e = desapilar(b);
      apilar(aux, e);
      // hanoi desde c hasta aux
      hanoi(n, c, a, aux);
    } else {
      // hanoi desde aux hasta c
      hanoi(n, aux, b, c);
      // movemos la cima de a a aux
      ElementoPila e = desapilar(a);
      apilar(aux, e);
      // hanoi desde c hasta aux
      hanoi(n, c, b, aux);
    }
    n++;

    cout << "Pila A: ";
    imprimir(a);
    cout << "Pila B: ";
    imprimir(b);
    cout << "Pila auxiliar: ";
    imprimir(aux);
    cout << "Pila C: ";
    imprimir(c);

  }

  if (a.inicio != nullptr) {
    int nA = longitud(a);
    hanoi(nA, a, b, c);
    hanoi(n, aux, b, c);
  }
  else if (b.inicio != nullptr) {
    int nB = longitud(b);
    hanoi(nB, b, a, c);
    hanoi(n, aux, a, c);
  }


}

int main() {

  Pila a, b, c;
  construir(a);
  construir(b);
  construir(c);


  apilar(a, {20});
  apilar(a, {15});
  apilar(a, {5});

  apilar(b, {18});
  apilar(b, {12});
  apilar(b, {10});
  apilar(b, {2});

  imprimir(a);
  imprimir(b);

  fusionar(a, b, c);


  imprimir(c);



  return 0;
}


