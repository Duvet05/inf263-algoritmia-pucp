#include <iostream>
#include <cstring>
using namespace std;

void intercambiar(int *a, int i, int j) {
  int aux = a[i];
  a[i] = a[j];
  a[j] = aux;
}

void ordenar_por_seleccion(int* a, int n) {
  for (int i=0; i<n-1; i++) {
    int min = i;
    for (int j=i+1; j<n; j++) {
      if (a[j] < a[min]) {
        min = j;
      }
    }
    intercambiar(a, i, min);
  }
}

void ordenar_por_burbuja(int *a, int n) {
  for (int i=0; i<n-1; i++) {
    for (int j=0; j<n-1-i; j++) {
      if (a[j+1] < a[j]) {
        intercambiar(a, j, j+1);
      }
    }
  }
}

int busqueda_secuencial(int *a, int n, int x) {
  for (int i=0; i<n; i++) {
    if (a[i] == x)
      return i;
  }
  return -1;
}

int busqueda_patron_en_cadena(char* T, int n, char* P, int m) {
  
  for (int i=0; i<n-m+1; i++) {
    int j=0;
    while (j<m && P[j] == T[i+j]) {
      j++;
    }
    if (j == m) {
      return i;
    }
  }
  return -1;
}

void imprimir_arreglo(int* a, int n) {
  for (int i=0; i<n; i++) {
    cout << a[i] << " ";
  }
  cout << endl;
}

void closest_pair(int *x, int *y, int n, int& i1, int& i2) {
  
  int d_menor = 999999;
  for (int i=0; i<n-1; i++) {
    for (int j=i+1; j<n; j++) {
      int d = (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
      if (d < d_menor) {
        d_menor = d;
        i1 = i;
        i2 = j;
      }
    }
  }
}


int main() {

  int x[] = {0, 5, 1, 2};
  int y[] = {0, 4, 0, 1};
  int n = 4;
  // Tengo 4 puntos: (0, 0), (5, 4), (1, 0), (2, 1)
  int i1, i2;
  closest_pair(x, y, n, i1, i2);

  cout << i1 << " " << i2 << endl;

  return 0;
}