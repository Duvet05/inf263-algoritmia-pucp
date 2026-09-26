#include <iostream>
#include <fstream>
using namespace std;
#define N 10

void leerDatos(int**& matriz) {

  ifstream archivo("p2.txt");
  if (!archivo) {
    cout << "ERROR: No se puede abrir el archivo p2.txt" << endl;
    exit(1);
  }

  matriz = new int*[N];
  for (int i=0; i<N; i++) {
    matriz[i] = new int[N];
    for (int j=0; j<N; j++)
      archivo >> matriz[i][j];
  }

  archivo.close();
}

int hallarMaximaPurezaEnFila(int* muestra, int ini, int fin) {

  if (ini == fin) {
    return muestra[ini];
  }

  int med = (ini + fin) / 2;

  int valor = muestra[med];
  int izq = med > 0 ? muestra[med-1] : -1;
  int der = med < N-1 ? muestra[med+1] : -1;

  if (izq < valor && valor > der)
    return valor;

  if (izq == valor && valor == der) {
    int limIzq = muestra[0];
    if (limIzq != 0)
      return hallarMaximaPurezaEnFila(muestra, ini, med-1);
    return hallarMaximaPurezaEnFila(muestra, med+1, fin);
  }
  
  if (der >= valor && valor >= izq)
    return hallarMaximaPurezaEnFila(muestra, med+1, fin);
  
  return hallarMaximaPurezaEnFila(muestra, ini, med-1); 
}

void hallarMaximaPureza(int** matriz) {
  int maxPureza = 0;
  for (int i=0; i<N; i++) {
    int maxPurezaMuestra = hallarMaximaPurezaEnFila(matriz[i], 0, N-1);
    if (maxPurezaMuestra > maxPureza)
      maxPureza = maxPurezaMuestra;
  }
  cout << "La maxima pureza de las muestras es: " << maxPureza << endl;
}

int hallarCantidadDeNoMinerales(int* muestra, int ini, int fin) {

  if (ini == fin)
    return muestra[ini] > 0 ? 0 : 1;

  int med = (ini + fin) / 2;
  int limIzq = muestra[ini];
  int limDer = muestra[fin];

  if (muestra[med] != 0) {
    if (limIzq == 0)
      return hallarCantidadDeNoMinerales(muestra, ini, med-1);
    if (limDer == 0)
      return hallarCantidadDeNoMinerales(muestra, med+1, fin);
  }
  else {
    if (limIzq == 0)
      return med - ini + 1 + hallarCantidadDeNoMinerales(muestra, med+1, fin);
    if (limDer == 0)
      return fin - med + 1 + hallarCantidadDeNoMinerales(muestra, ini, med-1);
  }
  return 0;
}

void hallarMaximaCantidadEstratos(int** matriz) {
  int maxCantidadEstratos = 0;
  for (int i=0; i<N; i++) {
    int cantidadMinerales = 10 - hallarCantidadDeNoMinerales(matriz[i], 0, N-1);
    if (cantidadMinerales > maxCantidadEstratos)
      maxCantidadEstratos = cantidadMinerales;
  }
  cout << "Las muestras con mayor cantidad de niveles con minerales son: ";
  for (int i=0; i<N; i++) {
    int cantidadMinerales = 10 - hallarCantidadDeNoMinerales(matriz[i], 0, N-1);
    if (cantidadMinerales == maxCantidadEstratos)
      cout << i+1 << " "; 
  }
  cout << "ambos con " << maxCantidadEstratos << " estratos de minerales" << endl;
}

int main() {

  int** matriz;
  leerDatos(matriz);

  hallarMaximaPureza(matriz);
  hallarMaximaCantidadEstratos(matriz);

  return 0;
}
