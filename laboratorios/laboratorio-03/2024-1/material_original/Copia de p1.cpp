#include <iostream>
using namespace std;

struct Solucion {
  int ini;
  int fin;
  int suma;
};

Solucion resolver(int arr[], int ini, int fin) {

  if (ini == fin) {
    return {ini, fin, arr[ini]};
  }

  int medio = (ini + fin) / 2;
  Solucion izq = resolver(arr, ini, medio);
  Solucion der = resolver(arr, medio+1, fin);

  int sumaCombinada = izq.suma + der.suma;

  for (int i=izq.fin+1; i<der.ini; i++)
    sumaCombinada += arr[i];
  
  if (sumaCombinada < izq.suma && sumaCombinada < der.suma)
    return {izq.ini, der.fin, sumaCombinada};
  
  if (izq.suma < der.suma)
    return izq;

  return der;
}

int main() {

  int arr[] = {-4, 5, 6, -4, 3, -1, -5, 6 };

  Solucion sol = resolver(arr, 0, 7);

  std::cout << sol.ini << " " << sol.fin << " " << sol.suma << endl;

  return 0;
}