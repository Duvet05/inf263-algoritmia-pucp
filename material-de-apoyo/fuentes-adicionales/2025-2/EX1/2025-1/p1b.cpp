#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

#define L 9

int contarPalets(char matriz[100][100], char palet, int i, int j, const char *direccion) {
  
  if (i < 0 || i >= L || j < 0 || j >= L) {
    return 0;
  }

  int nuevoI = i;
  int nuevoJ = j;

  if (strcmp(direccion, "arriba") == 0) {
    nuevoI = i - 1;
  } else if (strcmp(direccion, "abajo") == 0) {
    nuevoI = i + 1;
  } else if (strcmp(direccion, "izquierda") == 0) {
    nuevoJ = j - 1;
  } else if (strcmp(direccion, "derecha") == 0) {
    nuevoJ = j + 1;
  } else if (strcmp(direccion, "diagonal_arriba_izquierda") == 0) {
    nuevoI = i - 1;
    nuevoJ = j - 1;
  } else if (strcmp(direccion, "diagonal_arriba_derecha") == 0) {
    nuevoI = i - 1;
    nuevoJ = j + 1;
  } else if (strcmp(direccion, "diagonal_abajo_izquierda") == 0) {
    nuevoI = i + 1;
    nuevoJ = j - 1;
  } else if (strcmp(direccion, "diagonal_abajo_derecha") == 0) {
    nuevoI = i + 1;
    nuevoJ = j + 1;
  }

  int cuentaActual = (matriz[i][j] == palet) ? 1 : 0;
  cout << "At (" << i << ", " << j << ") cuentaActual: " << cuentaActual << endl;

  return cuentaActual + contarPalets(matriz, palet, nuevoI, nuevoJ, direccion);

}

void eliminarPalets(char matriz[100][100], char palet, int i, int j, const char *direccion) {

  if (i < 0 || i >= L || j < 0 || j >= L) {
    return;
  }

  if (matriz[i][j] == palet) {
    matriz[i][j] = '*';
  }
  
  int nuevoI = i;
  int nuevoJ = j;

  if (strcmp(direccion, "arriba") == 0) {
    nuevoI = i - 1;
  } else if (strcmp(direccion, "abajo") == 0) {
    nuevoI = i + 1;
  } else if (strcmp(direccion, "izquierda") == 0) {
    nuevoJ = j - 1;
  } else if (strcmp(direccion, "derecha") == 0) {
    nuevoJ = j + 1;
  } else if (strcmp(direccion, "diagonal_arriba_izquierda") == 0) {
    nuevoI = i - 1;
    nuevoJ = j - 1;
  } else if (strcmp(direccion, "diagonal_arriba_derecha") == 0) {
    nuevoI = i - 1;
    nuevoJ = j + 1;
  } else if (strcmp(direccion, "diagonal_abajo_izquierda") == 0) {
    nuevoI = i + 1;
    nuevoJ = j - 1;
  } else if (strcmp(direccion, "diagonal_abajo_derecha") == 0) {
    nuevoI = i + 1;
    nuevoJ = j + 1;
  }

  eliminarPalets(matriz, palet, nuevoI, nuevoJ, direccion);

}

void resolver(char matriz[100][100], char palet, int i, int j) {
  
  int maxPalets = 0;
  char direccionAEliminar[30];

  int paletsDerecha = contarPalets(matriz, palet, i, j+1, "derecha");
  cout << "Palets derecha: " << paletsDerecha << endl;
  if (paletsDerecha > maxPalets) {
    maxPalets = paletsDerecha;
    strcpy(direccionAEliminar, "derecha");
  }
  
  int paletsAbajo = contarPalets(matriz, palet, i+1, j, "abajo");
  cout << "Palets abajo: " << paletsAbajo << endl;
  if (paletsAbajo > maxPalets) {
    maxPalets = paletsAbajo;
    strcpy(direccionAEliminar, "abajo");
  }

  int paletsDiagonalAbajoDerecha = contarPalets(matriz, palet, i+1, j+1, "diagonal_abajo_derecha");
  cout << "Palets diagonal abajo derecha: " << paletsDiagonalAbajoDerecha << endl;
  if (paletsDiagonalAbajoDerecha > maxPalets) {
    maxPalets = paletsDiagonalAbajoDerecha;
    strcpy(direccionAEliminar, "diagonal_abajo_derecha");
  }

  int paletsDiagonalAbajoIzquierda = contarPalets(matriz, palet, i+1, j-1, "diagonal_abajo_izquierda");
  cout << "Palets diagonal abajo izquierda: " << paletsDiagonalAbajoIzquierda << endl;
  if (paletsDiagonalAbajoIzquierda > maxPalets) {
    maxPalets = paletsDiagonalAbajoIzquierda;
    strcpy(direccionAEliminar, "diagonal_abajo_izquierda");
  }

  int paletsIzquierda = contarPalets(matriz, palet, i, j-1, "izquierda");
  cout << "Palets izquierda: " << paletsIzquierda << endl;
  if (paletsIzquierda > maxPalets) {
    maxPalets = paletsIzquierda;
    strcpy(direccionAEliminar, "izquierda");
  }

  int paletsArriba = contarPalets(matriz, palet, i-1, j, "arriba");
  cout << "Palets arriba: " << paletsArriba << endl;
  if (paletsArriba > maxPalets) {
    maxPalets = paletsArriba;
    strcpy(direccionAEliminar, "arriba");
  }

  int paletsDiagonalArribaIzquierda = contarPalets(matriz, palet, i-1, j-1, "diagonal_arriba_izquierda");
  cout << "Palets diagonal arriba izquierda: " << paletsDiagonalArribaIzquierda << endl;
  if (paletsDiagonalArribaIzquierda > maxPalets) {
    maxPalets = paletsDiagonalArribaIzquierda;
    strcpy(direccionAEliminar, "diagonal_arriba_izquierda");
  }

  int paletsDiagonalArribaDerecha = contarPalets(matriz, palet, i-1, j+1, "diagonal_arriba_derecha");
  cout << "Palets diagonal arriba derecha: " << paletsDiagonalArribaDerecha << endl;
  if (paletsDiagonalArribaDerecha > maxPalets) {
    maxPalets = paletsDiagonalArribaDerecha;
    strcpy(direccionAEliminar, "diagonal_arriba_derecha");
  }

  cout << "Max palets to remove: " << maxPalets << " in direction " << direccionAEliminar << endl;

  if (strcmp(direccionAEliminar, "abajo") == 0) {
    eliminarPalets(matriz, palet, i+1, j, "abajo");
  } else if (strcmp(direccionAEliminar, "derecha") == 0) {
    eliminarPalets(matriz, palet, i, j+1, "derecha");
  } else if (strcmp(direccionAEliminar, "diagonal_abajo_derecha") == 0) {
    eliminarPalets(matriz, palet, i+1, j+1, "diagonal_abajo_derecha");
  } else if (strcmp(direccionAEliminar, "diagonal_abajo_izquierda") == 0) {
    eliminarPalets(matriz, palet, i+1, j-1, "diagonal_abajo_izquierda");
  } else if (strcmp(direccionAEliminar, "izquierda") == 0) {
    eliminarPalets(matriz, palet, i, j-1, "izquierda");
  } else if (strcmp(direccionAEliminar, "arriba") == 0) {
    eliminarPalets(matriz, palet, i-1, j, "arriba");
  } else if (strcmp(direccionAEliminar, "diagonal_arriba_izquierda") == 0) {
    eliminarPalets(matriz, palet, i-1, j-1, "diagonal_arriba_izquierda");
  } else if (strcmp(direccionAEliminar, "diagonal_arriba_derecha") == 0) {
    eliminarPalets(matriz, palet, i-1, j+1, "diagonal_arriba_derecha");
  }


}

int main() {


  char matriz[100][100] = {
    {'*', '*', '*', '*', '*', '*', '*', '*', '*'},
    {'*', 'A', '*', '*', '*', 'B', '*', '*', '*'},
    {'*', '*', 'V', 'A', '*', '*', '*', '*', '*'},
    {'*', 'B', '*', 'D', '*', 'V', 'B', 'A', '*'},
    {'*', '*', 'B', 'B', '*', '*', '*', '*', '*'},
    {'*', 'A', '*', 'B', '*', '*', '*', '*', '*'},
    {'*', '*', '*', '*', '*', 'B', 'A', '*', '*'},
    {'*', '*', '*', 'V', '*', '*', '*', '*', '*'},
    {'*', '*', '*', 'B', '*', '*', '*', '*', 'A'},
  };


  char palet = 'B';

  resolver(matriz, palet, 3, 3);

  // imprimir matriz resultante
  for (int i = 0; i < L; i++) {
    for (int j = 0; j < L; j++) {
      cout << matriz[i][j] << " ";
    }
    cout << endl;
  }


  return 0;
}
