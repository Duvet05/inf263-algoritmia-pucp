#include <iostream>
#include <fstream>
using namespace std;

struct Nodo {
  int nivel;
  Nodo* sig = NULL;
};
struct Pila {
  Nodo* cima = NULL;
};

void apilar(Pila* pila, Nodo* nuevoNodo);
Nodo* desapilar(Pila* pila);
bool leerDatos(char **direcciones, int *cantidadDirecciones);
void resolver(char *direcciones, int cantidadDirecciones, Pila* pila);
void imprimePila(Pila pila);

int main() {

  char *direcciones;
  int cantidadDirecciones;

  leerDatos(&direcciones, &cantidadDirecciones);

  Pila solucion;

  resolver(direcciones, cantidadDirecciones, &solucion);

  imprimePila(solucion);

  return 0;
}

void apilar(Pila* pila, Nodo* nuevoNodo) {
  nuevoNodo->sig = pila->cima;
  pila->cima = nuevoNodo;
}

Nodo* desapilar(Pila* pila) {
  if (pila->cima == NULL)
    return NULL;
  Nodo* nodo = pila->cima;
  pila->cima = nodo->sig;
  return nodo;
}

bool leerDatos(char **direcciones, int *cantidadDirecciones) {
  ifstream archivo("p2.txt");
  if (!archivo) {
    cout << "ERROR: No se puede abrir el archivo p2.txt" << endl;
    return false;
  }

  archivo >> (*cantidadDirecciones);
  *direcciones = new char[*cantidadDirecciones];

  for (int i=0; i<*cantidadDirecciones; i++) {
    archivo >> (*direcciones)[i];
  }

  archivo.close();
  return true;
}

void resolver(char *direcciones, int cantidadDirecciones, Pila* pila) {
  int cantidadBs = 0;

  Nodo* nuevosNodos[2];
  nuevosNodos[0] = new Nodo;
  nuevosNodos[1] = new Nodo;
  if (direcciones[0] == 'S') {
    nuevosNodos[0]->nivel = 1;
    nuevosNodos[1]->nivel = 2;
  }
  else {
    nuevosNodos[0]->nivel = 2;
    nuevosNodos[1]->nivel = 1;
    cantidadBs++;
  }
  apilar(pila, nuevosNodos[0]);
  apilar(pila, nuevosNodos[1]);

  int n = 3;
  for (int i=1; i<cantidadDirecciones; i++) {
    Nodo* nuevoNodo = new Nodo;
    nuevoNodo->nivel = n;

    char direccion = direcciones[i];
    if (direccion == 'S') {
      apilar(pila, nuevoNodo);
      cantidadBs = 0;
    }
    else {
      cantidadBs++;
      for (int j=0; j<cantidadBs; j++) {
        Nodo* nodo = desapilar(pila);
        delete nodo;
      }
      apilar(pila, nuevoNodo);
      for (int j=0; j<cantidadBs; j++) {
        Nodo* nuevoNodo = new Nodo;
        nuevoNodo->nivel = n-j-1;
        apilar(pila, nuevoNodo);
      }
    }
    n++;
  }
}

void imprimePila(Pila pila) {
  for (Nodo* nodo=pila.cima; nodo!=NULL; nodo=nodo->sig) {
    cout << nodo->nivel << endl;
  }
}
