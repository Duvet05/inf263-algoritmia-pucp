#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Avion {
  int numero;
  char horaLlegada[6];
  char nuevaHoraLlegada[6];
};  

struct Nodo {
  Avion avion;
  Nodo* sig = NULL;
};

struct Cola {
  Nodo* inicio = NULL;
  Nodo* fin = NULL;
  int longitud = 0;
};

void encolar(Cola* cola, Nodo* nodo);
Nodo* desencolar(Cola* cola);
bool leerDatos(Cola* aviones);
void imprimeAviones(Cola aviones);
void ordenarCola(Cola *aviones, int modo);

int main() {

  Cola aviones;

  if (!leerDatos(&aviones))
    return 1;

  imprimeAviones(aviones);
  
  ordenarCola(&aviones, 0);
  imprimeAviones(aviones);

  ordenarCola(&aviones, 1);
  imprimeAviones(aviones);

  return 0;
}

void encolar(Cola* cola, Nodo* nodo) {
  if (cola->inicio == NULL) {
    cola->inicio = nodo;
  }
  if (cola->fin != NULL) {
    cola->fin->sig = nodo;
  }
  cola->fin = nodo;
  (cola->longitud)++;
}

Nodo* desencolar(Cola* cola) {
  if (cola->inicio == NULL)
    return NULL;

  Nodo* nodo = cola->inicio;
  
  cola->inicio = nodo->sig;
  if (cola->inicio == cola->fin)
    cola->fin = NULL;
  (cola->longitud)--;
  
  nodo->sig = NULL;
  return nodo;
}

bool leerDatos(Cola* aviones) {

  ifstream archivo("p3b.txt");
  if (!archivo) {
    cout << "ERROR: No se puede abrir el archivo p3b.txt" << endl;
    return false;
  } 

  while (true) {

    Avion avion;
    archivo >> avion.numero;
    if (archivo.eof())
      break;
    archivo >> avion.horaLlegada;
    archivo >> avion.nuevaHoraLlegada;
  
    Nodo *nodo = new Nodo;
    nodo->avion = avion;
    
    encolar(aviones, nodo);
  }

  archivo.close();
  return true;
}

void imprimeAviones(Cola aviones) {
  for (Nodo *nodo=aviones.inicio; nodo!=NULL; nodo=nodo->sig) {
    cout << nodo->avion.numero << " " << nodo->avion.horaLlegada << " " << nodo->avion.nuevaHoraLlegada << endl;
  }
  cout << endl;
}

void ordenarCola(Cola *aviones, int modo) {
  int n = aviones->longitud;
  for (int i=0; i<n-1; i++) {
    for (int j=0; j<n-i-1; j++) {
      if ((modo == 0 && strcmp(aviones->inicio->avion.horaLlegada, aviones->inicio->sig->avion.horaLlegada) > 0) ||
          (modo == 1 && strcmp(aviones->inicio->avion.nuevaHoraLlegada, aviones->inicio->sig->avion.nuevaHoraLlegada) > 0)) {

        Nodo* nodoAux, *nodoAux2;
        // Paso 1
        nodoAux = desencolar(aviones);
        nodoAux2 = desencolar(aviones);
        encolar(aviones, nodoAux2);
        encolar(aviones, nodoAux);

        // Paso 2
        for (int k=0; k<n-1; k++) {
          nodoAux2 = desencolar(aviones);
          encolar(aviones, nodoAux2);
        }
      }
      else {
        Nodo* nodoAux = desencolar(aviones);
        encolar(aviones, nodoAux);
      }
    }
    for (int k=0; k<i+1; k++) {
      Nodo* nodoAux = desencolar(aviones);
      encolar(aviones, nodoAux);
    }
    // imprimeAviones(*aviones);
  }
}

