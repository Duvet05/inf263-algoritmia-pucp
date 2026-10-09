#include <iostream>
#include <fstream>
using namespace std;


struct Efectivo {
  int id;
  int grado;
  int tiempo;
};

struct Nodo {
  Efectivo efectivo;
  Nodo* sig = nullptr;
};

struct Pila {
  Nodo* cima = nullptr;
};

void push(Pila &pila, Efectivo efectivo)
{
    Nodo *nuevoNodo = new Nodo;
    nuevoNodo->efectivo = efectivo;
    nuevoNodo->sig = pila.cima;
    pila.cima = nuevoNodo;
}
Efectivo pop(Pila &pila)
{    
    Nodo *nodoEliminar;
    Efectivo efectivo;
    
    if (pila.cima) { 
        nodoEliminar = pila.cima;
        efectivo = nodoEliminar->efectivo; 
        pila.cima = nodoEliminar->sig; 
        delete nodoEliminar;
    }
    return efectivo;
}

void leerDatos(Efectivo*& efectivos, int& n) {
  ifstream archivo("lab2-p1.txt");

  archivo >> n;
  efectivos = new Efectivo[n];

  for (int i=0; i<n; i++)
    archivo >> efectivos[i].id >> efectivos[i].grado >> efectivos[i].tiempo;

  archivo.close();
}

int hallarCantidadGrupos(Efectivo* efectivos, int n) {

  int cant = 0;
  Pila pila;

  for (int i=n-1; i>=0; i--) {
    push(pila, efectivos[i]);
  }

  int gradoMax = 0;
  int tiempoMax = 0;

  while (pila.cima) {

    Efectivo efectivo = pop(pila);
    
    if (gradoMax > efectivo.grado || (gradoMax == efectivo.grado && tiempoMax > efectivo.tiempo))
      cant++;


    if (efectivo.grado > gradoMax)
      gradoMax = efectivo.grado;
    if (efectivo.tiempo > tiempoMax)
      tiempoMax = efectivo.tiempo;
  }

  return cant + n;
}

int main() {

  Efectivo* efectivos;
  int n = 0;

  leerDatos(efectivos, n);

  int cant = hallarCantidadGrupos(efectivos, n);

  cout << cant << endl;

  return 0;
}