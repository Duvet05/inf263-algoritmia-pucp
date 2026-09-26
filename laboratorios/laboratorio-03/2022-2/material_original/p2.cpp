#include <iostream>
#include <fstream>
using namespace std;

struct SolucionA {
  int columna;
  int maxPotencia;
};

struct SolucionB {
  int fila;
  int maxPotencia;
};

bool leerDatos(int ***matriz, int *n, int *m) {

  ifstream archivo("p2.txt");
  
  if (!archivo) {
    cout << "ERROR: No se puede abrir el archivo p2.txt" << endl;
    return false;
  }

  archivo >> *n;
  archivo >> *m;

  cout << *n << endl;
  cout << *m << endl;

  *matriz = new int*[*m];

  for (int y=0; y<*m; y++) {
    (*matriz)[y] = new int[*n];
    for (int x=0; x<*n; x++) {
      archivo >> ((*matriz)[y])[x];
    }
  }

  archivo.close();
  return true;
} 

int maximoColumna(int **matriz, int n, int m) {
  int max = 0;
  for (int y=0; y<m; y++)
    if (matriz[y][n] > max)
      max = matriz[y][n];
  return max;
}

SolucionA resolverA(int **matriz, int ini, int fin, int m) {

  if (ini >= fin)
    return {ini, maximoColumna(matriz, ini, m)};

  int medio = (ini + fin) / 2;
  SolucionA izq = resolverA(matriz, ini, medio, m);
  SolucionA der = resolverA(matriz, medio+1, fin, m);

  if (izq.maxPotencia > der.maxPotencia)
    return izq;
  return der;
}

SolucionB resolverB(int **matriz, int n, int ini, int fin, int columna) {

  if (ini >= fin)
    return {ini, matriz[ini][columna]};
  
  int medio = (ini + fin) / 2;
  SolucionB izq = resolverB(matriz, n, ini, medio, columna);
  SolucionB der = resolverB(matriz, n, medio+1, fin, columna);

  if (izq.maxPotencia > der.maxPotencia)
    return izq;
  return der;
}

SolucionA resolverA_(int **matriz, int ini, int fin, int m) {

  if (ini >= fin)
    return {ini, maximoColumna(matriz, ini, m)};

  int medio = (ini + fin) / 2;

  int max = 0;
  bool izq = true;
  bool der = true;
  for (int y=0; y<m; y++) {
    if (matriz[y][medio-1] > max) {
      max = matriz[y][medio-1];
      der = false;
    }
    if (matriz[y][medio+1] > max) {
      max = matriz[y][medio+1];
      izq = false;
    }
  }

  return izq ? resolverA_(matriz, ini, medio, m) : resolverA_(matriz, medio+1, fin, m);
}

SolucionB resolverB_(int **matriz, int n, int ini, int fin, SolucionA solA) {

  if (ini >= fin)
    return {ini, matriz[ini][solA.columna]};

  int medio = (ini + fin) / 2;

  if (matriz[medio][solA.columna] == solA.maxPotencia)
    return {medio, matriz[ini][solA.columna]};

  if (matriz[medio-1][solA.columna] > matriz[medio+1][solA.columna]) {
    return resolverB_(matriz, n, ini, medio-1, solA);
  }
  return resolverB_(matriz, n, medio+1, fin, solA);
}

int main() {

  int **matriz;
  int n, m;

  leerDatos(&matriz, &n, &m);

  for (int y=0; y<m; y++) {
    for (int x=0; x<n; x++)
      cout << matriz[y][x] << " ";
    cout << endl;
  }
  cout << endl;

  SolucionA solA = resolverA_(matriz, 0, n-1, m);

  cout << "Columna: " << solA.columna << endl;
  cout << "Maxima potencia: " << solA.maxPotencia << endl;

  SolucionB solB = resolverB_(matriz, n, 0, m-1, solA);

  cout << "Fila: " << solB.fila << endl;

  return 0;
}

