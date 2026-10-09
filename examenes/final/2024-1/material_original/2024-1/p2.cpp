#include <iostream>
#include <fstream>
using namespace std;
#include "..\ArbolesBinarios\funcionesArbolesBB.h"
#include "..\ArbolesBinarios\funcionesArbolesBinarios.h"

void leerDatos(int**& emociones, int& cantidadEmociones, int**& combinaciones, int& cantidadCombinaciones) {

  ifstream archivo("p2.txt");

  if (!archivo) {
    cout << "ERROR: No se puede abrir el archivo p2.txt" << endl;
    exit(1);
  }

  archivo >> cantidadEmociones;
  emociones = new int*[cantidadEmociones];
  for (int i=0; i<cantidadEmociones; i++) {
    emociones[i] = new int[3];
    for (int j=0; j<3; j++)
      archivo >> emociones[i][j];
  }
  archivo >> cantidadCombinaciones;
  combinaciones = new int*[cantidadCombinaciones];
  for (int i=0; i<cantidadCombinaciones; i++) {
    combinaciones[i] = new int[3];
    for (int j=0; j<3; j++)
      archivo >> combinaciones[i][j];
  }
}

bool verificarCombinacion(NodoArbol* nodo, int* combinacion, int indiceCombinacion,
                          int** emociones) {

  if (indiceCombinacion == 3)
    return true;

  if (nodo == nullptr)
    return false;

  // Buscar la emocion en la matriz de pesos de emociones
  int emocion = combinacion[indiceCombinacion];
  int peso = nodo->elemento;

  int* emocionPesos = emociones[emocion-1];
  for (int i=0; i<3; i++)
    if (emocionPesos[i] == peso) {
      return  verificarCombinacion(nodo->izquierda, combinacion, indiceCombinacion+1, emociones) ||
              verificarCombinacion(nodo->derecha, combinacion, indiceCombinacion+1, emociones);
    }
  return false;
}

void hallarCantidadDeCombinaciones(NodoArbol* nodo, int* niveles, int nivel,
                                        int** emociones,
                                        int** combinaciones, int cantidadCombinaciones) {
  
  if (nodo == nullptr)
    return;

  int suma = 0;
  for (int i=0; i<cantidadCombinaciones; i++) {
    int* combinacion = combinaciones[i];
    if (verificarCombinacion(nodo, combinacion, 0, emociones))
      suma++;
  }
  niveles[nivel] += suma;
  hallarCantidadDeCombinaciones(nodo->izquierda, niveles, nivel+1, emociones, combinaciones, cantidadCombinaciones);
  hallarCantidadDeCombinaciones(nodo->derecha, niveles, nivel+1, emociones, combinaciones, cantidadCombinaciones);
}


int main() {

  int** emociones;
  int cantidadEmociones;
  int** combinaciones;
  int cantidadCombinaciones;

  leerDatos(emociones, cantidadEmociones, combinaciones, cantidadCombinaciones);

  ArbolBinarioBusqueda ABB;
  construir(ABB.arbolBinario);

  insertar(ABB, 180);

  insertar(ABB, 120);
  insertar(ABB, 250);
  
  insertar(ABB, 100);
  insertar(ABB, 150);
  insertar(ABB, 230);
  insertar(ABB, 280);

  insertar(ABB, 80);
  insertar(ABB, 140);
  insertar(ABB, 160);
  insertar(ABB, 200);
  insertar(ABB, 240);
  insertar(ABB, 260);
  
  insertar(ABB, 90);

  recorrerEnOrden(ABB.arbolBinario);

  int cantidadDeNiveles = altura(ABB.arbolBinario);
  
  int* niveles = new int[cantidadDeNiveles];
  for (int i=0; i<cantidadDeNiveles; i++)
    niveles[i] = 0;

  hallarCantidadDeCombinaciones(ABB.arbolBinario.raiz, niveles, 0, emociones, combinaciones, cantidadCombinaciones);

  for (int i=0; i<cantidadDeNiveles; i++) {
    cout << "Nivel " << i+1 << " - " << niveles[i] << " combinaciones" << endl;
  }

  return 0;
}




