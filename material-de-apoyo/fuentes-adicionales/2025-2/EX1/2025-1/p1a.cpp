#include <iostream>
#include <fstream>
using namespace std;

bool estaEnElPatron(char c, char patron[100], int n, bool encontrados[100]) {
  for (int i = 0; i < n; i++) {
    if (c == patron[i]) {
      
      if (encontrados[i])
        return false; // Ya fue encontrado antes

      encontrados[i] = true;
      return true;
    }
  }
  return false;
} 

void ubicarExfiltraciones(char matriz[100][100], int r, int s, char patron[100], int n) {
  
  for (int i = 0; i <= r ; i++) {
    for (int j = 0; j <= s ; j++) {
      
      // Hallar todas las posibles combinaciones del patron partiendo de la posicion (i, j)
      // Hacia la derecha
      if (j + n <= s) {
        bool encontrados[100] = {false};
        bool esElPatron = true;
        for (int k = 0; k < n; k++) {
          if (!estaEnElPatron(matriz[i][j + k], patron, n, encontrados)) {
            esElPatron = false;
            break;
          }
        }
        if (esElPatron) {
          cout << "(" << i << ", " << j << ")" << endl;
        }
      }
      // Hacia la izquierda
      if (j - n + 1 >= 0) {
        bool encontrados[100] = {false};
        bool esElPatron = true;
        for (int k = 0; k < n; k++) {
          if (!estaEnElPatron(matriz[i][j - k], patron, n, encontrados)) {
            esElPatron = false;
            break;
          }
        }
        if (esElPatron) {
          cout << "(" << i << ", " << j << ")" << endl;
        }
      }
      // Hacia abajo
      if (i + n <= r) {
        bool encontrados[100] = {false};
        bool esElPatron = true;
        for (int k = 0; k < n; k++) {
          if (!estaEnElPatron(matriz[i + k][j], patron, n, encontrados)) {
            esElPatron = false;
            break;
          }
        }
        if (esElPatron) {
          cout << "(" << i << ", " << j << ")" << endl;
        }
      }
      // Hacia arriba
      if (i - n + 1 >= 0) {
        bool encontrados[100] = {false};
        bool esElPatron = true;
        for (int k = 0; k < n; k++) {
          if (!estaEnElPatron(matriz[i - k][j], patron, n, encontrados)) {
            esElPatron = false;
            break;
          }
        }
        if (esElPatron) {
          cout << "(" << i << ", " << j << ")" << endl;
        }
      }

      // Diagonal derecha abajo
      if (i + n <= r && j + n <= s) {
        bool encontrados[100] = {false};
        bool esElPatron = true;
        for (int k = 0; k < n; k++) {
          if (!estaEnElPatron(matriz[i + k][j + k], patron, n, encontrados)) {
            esElPatron = false;
            break;
          }
        }
        if (esElPatron) {
          cout << "(" << i << ", " << j << ")" << endl;
        }
      }

      // Diagonal izquierda abajo
      if (i + n <= r && j - n + 1 >= 0) {
        bool encontrados[100] = {false};
        bool esElPatron = true;
        for (int k = 0; k < n; k++) {
          if (!estaEnElPatron(matriz[i + k][j - k], patron, n, encontrados)) {
            esElPatron = false;
            break;
          }
        }
        if (esElPatron) {
          cout << "(" << i << ", " << j << ")" << endl;
        }
      }

      // Diagonal derecha arriba
      if (i - n + 1 >= 0 && j + n <= s) {
        bool encontrados[100] = {false};
        bool esElPatron = true;
        for (int k = 0; k < n; k++) {
          if (!estaEnElPatron(matriz[i - k][j + k], patron, n, encontrados)) {
            esElPatron = false;
            break;
          }
        }
        if (esElPatron) {
          cout << "(" << i << ", " << j << ")" << endl;
        }
      }

      // Diagonal izquierda arriba
      if (i - n + 1 >= 0 && j - n + 1 >= 0) {
        bool encontrados[100] = {false};
        bool esElPatron = true;
        for (int k = 0; k < n; k++) {
          if (!estaEnElPatron(matriz[i - k][j - k], patron, n, encontrados)) {
            esElPatron = false;
            break;
          }
        }
        if (esElPatron) {
          cout << "(" << i << ", " << j << ")" << endl;
        }
      }

      
    }
  }
}

int main() {

  char matriz[100][100] =  {{'C','E','N','Z','Y','X','A','U'}, 
                            {'D','Y','X','A','B','A','Y','U'}, 
                            {'A','Z','Y','A','X','B','C','U'}, 
                            {'B','Z','Z','A','E','E','Y','A'}, 
                            {'Y','Y','B','X','N','C','Z','Y'}, 
                            {'U','U','Y','Y','B','N','C','Z'}, 
                            {'Z','Y','A','A','U','Y','Y','E'}, 
                            {'Y','U','E','D','Z','B','B','N'}, 
                            {'Z','C','B','X','U','B','A','Z'}, 
                            {'N','Z','B','C','Y','Y','A','Y'}, 
                            {'X','A','E','Z','Z','A','U','Z'}, 
                            {'A','C','Z','X','X','Y','Y','Z'}};
  int r = 12;
  int s = 8;

  char patron[100] = {'C','E','N'};
  int n = 3;


  ubicarExfiltraciones(matriz, r, s, patron, n);

  return 0;
}