#include "./ListaSimplementeEnlazada/BibliotecaLista/funcionesLista.h"
#include "./ListaSimplementeEnlazada/BibliotecaLista/Lista.h"
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

void leerArchivoJugadores(Lista & lista) {

  ifstream archivo("jugadores.csv");
  if (!archivo.is_open()) {
    cout << "No se pudo abrir el archivo." << endl;
    return;
  }

  // 7,Martínez,Delantero 
  int pos=1;
  while (true) {

    ElementoLista elemento;
    archivo >> elemento.codigo;
    if (archivo.eof()) break;
    archivo.ignore(); // Ignorar la coma
    archivo.getline(elemento.nombre, 30, ',');
    archivo.getline(elemento.posicion, 30);
    elemento.orden = pos;
    insertarAlFinal(lista, elemento);
    pos++;
  }

  archivo.close();
} 

void leerArchivoPosiciones(char posiciones[4][30]) {

  ifstream archivo("posiciones.txt");
  if (!archivo.is_open()) {
    cout << "No se pudo abrir el archivo." << endl;
    return;
  }

  for (int i = 0; i < 4; i++) {
    archivo.getline(posiciones[i], 30);
  }

  archivo.close();
}

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


void intercambiarNodos(struct NodoLista * nodo1, struct NodoLista * nodo2) {
  ElementoLista temp;
  temp.codigo = nodo1->elemento.codigo;
  temp.orden = nodo1->elemento.orden;
  strcpy(temp.nombre, nodo1->elemento.nombre);
  strcpy(temp.posicion, nodo1->elemento.posicion);

  nodo1->elemento.codigo = nodo2->elemento.codigo;
  nodo1->elemento.orden = nodo2->elemento.orden;
  strcpy(nodo1->elemento.nombre, nodo2->elemento.nombre);
  strcpy(nodo1->elemento.posicion, nodo2->elemento.posicion);

  nodo2->elemento.codigo = temp.codigo;
  nodo2->elemento.orden = temp.orden;
  strcpy(nodo2->elemento.nombre, temp.nombre);
  strcpy(nodo2->elemento.posicion, temp.posicion);
}

void reordenaFormacion(Lista &lista, char posiciones[4][30]) {
  
  int n = longitudLista(lista);
  struct NodoLista * actual = lista.lista;
  struct NodoLista * siguiente;

  // ordenamiento burbuja para ordenar la lista
  for (int i=0; i<n-1; i++) {
    siguiente = actual->siguiente;

    for (int j=0; j<n-i-1; j++) {

      int cmp = compararPosiciones(actual->elemento.posicion, siguiente->elemento.posicion, posiciones);

      cout << "Comparando: " << actual->elemento.nombre << " (" << actual->elemento.posicion << ")"
           << " con " << siguiente->elemento.nombre << " (" << siguiente->elemento.posicion << ")"
           << " => Resultado: " << cmp << endl;

      if (cmp > 0 || (cmp == 0 && actual->elemento.orden > siguiente->elemento.orden)) {
        intercambiarNodos(actual, siguiente);
        cout << "  Intercambiando: " << actual->elemento.nombre << " <=> " << siguiente->elemento.nombre << endl;
      }

      siguiente = siguiente->siguiente;

    }
    actual = actual->siguiente;


    cout << "Iteracion " << i+1 << ": ";
    imprimir(lista);

  }

}

int main() {

  Lista lista;
  construir(lista);
  
  char posiciones[4][30];

  leerArchivoJugadores(lista);
  leerArchivoPosiciones(posiciones);

  cout << "Posiciones de juego en orden: " << endl;
  for (int i = 0; i < 4; i++) {
    cout << i+1 << ". " << posiciones[i] << endl;
  }

  reordenaFormacion(lista, posiciones);

  imprimir(lista);
  
  return 0;
}

