#include <iostream>
#include <fstream>
using namespace std;

#include "./Cola/BibliotecaCola/funcionesCola.h"
#include "./Pila/BibliotecaPila/funcionesPila.h"
#include "./Pila/BibliotecaPila/Pila.h"
#include "./Cola/BibliotecaCola/Cola.h"


bool leerCola(Cola* cola);
bool leerPila(Pila* pila, const char* nombreArchivo);

void reiniciaCola(Cola* cola, int n, Pila* pila1, Pila* pila2);
void ordenarPila(Pila* pila, Pila* aux, int modo);
void reclasificaPilas(Pila* pila1, Pila* pila2);

int main() {

  Cola cola;
  Pila pila1, pila2;
  construir(cola);
  construir(pila1);
  construir(pila2);

  if (!leerCola(&cola) || !leerPila(&pila1, "pila1.txt") || !leerPila(&pila2, "pila2.txt"))
    return 1;

  imprimir(cola);
  imprimir(pila1);
  imprimir(pila2);

  reiniciaCola(&cola, 8, &pila1, &pila2);
  cout << "Después de reiniciar la cola:" << endl;
  imprimir(cola);
  imprimir(pila1);
  imprimir(pila2);
  
  construir(pila1);
  reclasificaPilas(&pila1, &pila2);
  cout << "Después de reclasificar las pilas:" << endl;
  imprimir(cola);
  imprimir(pila1);
  imprimir(pila2);

  return 0;
}

bool leerCola(Cola* cola) {
  ifstream archivo("cola.txt");
  if(!archivo) {
    cout << "ERROR: No se puede abrir cola.txt" << endl;
    return false;
  }

  while (true) {
    int incidente;
    archivo >> incidente;
    if (archivo.eof())
      break;
    ElementoCola e;
    e.incidente = incidente;
    encolar(*cola, e);
  }

  archivo.close();
  return true;
}

bool leerPila(Pila* pila, const char* nombreArchivo) {
  ifstream archivo(nombreArchivo);
  if(!archivo) {
    cout << "ERROR: No se puede abrir cola.txt" << endl;
    return false;
  }

  while (true) {
    int incidente;
    archivo >> incidente;
    if (archivo.eof())
      break;
    ElementoPila e;
    e.incidente = incidente;
    apilar(*pila, e);
  }

  archivo.close();
  return true;
}


void reiniciaCola(Cola* cola, int n, Pila* pila1, Pila* pila2) {

  // Paso 1
  while (pila2->inicio != NULL) {
    ElementoPila e = desapilar(*pila2);
    apilar(*pila1, e);
  }
  // Paso 2
  ordenarPila(pila1, pila2, 0);

  // Paso 3
  int longitudCola = cola->longitud;
  int longitudPila1 = pila1->longitud;
  for (int i=0; i<longitudCola-longitudPila1; i++) {
    ElementoCola e = desencolar(*cola);
    encolar(*cola, e);
  }
  for (int i=0; i<longitudPila1; i++) {
    ElementoCola e = desencolar(*cola);
    ElementoPila ep;
    ep.incidente = e.incidente;
    apilar(*pila2, ep);
  }
  for (int i=0; i<longitudPila1; i++) {
    ElementoPila e = desapilar(*pila1);
    ElementoCola ec;
    ec.incidente = e.incidente;
    encolar(*cola, ec);
  }
  for (int i=0; i<longitudCola-longitudPila1; i++) {
    ElementoCola e = desencolar(*cola);
    encolar(*cola, e);
  }
}

void ordenarPila(Pila* pila, Pila* aux, int modo) {
int n = pila->longitud;
ElementoPila elementoAux, elementoAux2;
  for (int i=0; i<n-1; i++) {
    for (int j=0; j<n-i-1; j++) {
      if ((modo == 0 && pila->inicio->elemento.incidente%100 > pila->inicio->siguiente->elemento.incidente%100) ||
          (modo == 1 && pila->inicio->elemento.incidente > pila->inicio->siguiente->elemento.incidente)) {
        // Paso 1
        elementoAux = desapilar(*pila);
        elementoAux2 = desapilar(*pila);
        apilar(*pila, elementoAux);
      }
      else {
        // Paso 1
        elementoAux2 = desapilar(*pila);
      }
      // Paso 2
      for (int k=0; k<n-1; k++) {
        elementoAux = desapilar(*pila);
        apilar(*aux, elementoAux);
      }
      // Paso 3
      apilar(*pila, elementoAux2);
      // Paso 4
      for (int k=0; k<n-1; k++) {
        elementoAux = desapilar(*aux);
        apilar(*pila, elementoAux);
      }
    }
    for (int k=0; k<i+1; k++) {
      // Paso 1
      elementoAux2 = desapilar(*pila);
      // Paso 2
      for (int k=0; k<n-1; k++) {
        elementoAux = desapilar(*pila);
        apilar(*aux, elementoAux);
      }
      // Paso 3
      apilar(*pila, elementoAux2);
      // Paso 4
      for (int k=0; k<n-1; k++) {
        elementoAux = desapilar(*aux);
        apilar(*pila, elementoAux);
      }
    }
  }
}

void reclasificaPilas(Pila* pila1, Pila* pila2) {
  // Todos los nodos se pasan a la pila2
  while (pila1->inicio != NULL) {
    ElementoPila e = desapilar(*pila1);
    apilar(*pila2, e);
  }

  // Se ordena la pila2
  ordenarPila(pila2, pila1, 1);

  // Se crea la cola auxiliar
  Cola colaAux;
  construir(colaAux);
  while (pila2->inicio != NULL) {
    ElementoPila e = desapilar(*pila2);
    ElementoCola ec;
    ec.incidente = e.incidente;
    encolar(colaAux, ec);
  }

  while ((colaAux.inicio->elemento.incidente)/100 == 1) {
    ElementoCola e = desencolar(colaAux);
    ElementoPila ep;
    ep.incidente = e.incidente;
    apilar(*pila2, ep);
  }


  while (pila2->inicio != NULL) {
    ElementoPila e = desapilar(*pila2);
    apilar(*pila1, e);
  }

  while (colaAux.inicio != NULL) {
    ElementoCola e = desencolar(colaAux);
    ElementoPila ep;
    ep.incidente = e.incidente;
    apilar(*pila1, ep);
  }

  while ((pila1->inicio->elemento.incidente)/100 == 2) {
    ElementoPila e = desapilar(*pila1);
    apilar(*pila2, e);
  }
}
