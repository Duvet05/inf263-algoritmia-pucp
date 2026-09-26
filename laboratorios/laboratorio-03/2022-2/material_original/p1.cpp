#include <iostream>
using namespace std;
#define N 30

struct Solucion {
  int ini;
  int fin;
  int numero;
};

struct Dias {
  int ini;
  int fin;
  int cantidad;
};

void leerDatos(int *arr) {

  cout << "Ingrese las evaluaciones del paciente día por día, desde el día 1 al día 30:" << endl;
  for (int i=0; i<N; i++)
    cin >> arr[i];
  
}

Solucion resolver(int *arr, int ini, int fin) {

  if (ini == fin)
    return {ini, fin, arr[ini]};
  
  int mitad = (ini+fin) / 2;
  Solucion izq = resolver(arr, ini, mitad);
  Solucion der = resolver(arr, mitad+1, fin);

  if (izq.numero < der.numero)
    return izq;
  if (der.numero < izq.numero)
    return der;
  

  for (int i=izq.fin+1; i<der.ini; i++)
    if (arr[i] != izq.numero) {
      int izqLon = izq.fin - izq.ini;
      int derLon = der.fin - der.ini;
      if (izqLon < derLon)
        return der;
      return izq;
    }
    else
      izq.fin++;

  return {izq.ini, der.fin, izq.numero};
}

int hallarMenor(int *arr, int ini, int fin) {

  if (ini == fin)
    return arr[ini];

  int mitad = (ini + fin) / 2;
  int izq = hallarMenor(arr, ini, mitad);
  int der = hallarMenor(arr, mitad + 1, fin);

  return izq < der ? izq : der;
}

Dias hallarCantidadDias(int *arr, int ini, int fin, int menor) {

  if (ini == fin)
    return {ini, fin, arr[ini] == menor ? 1 : 0};

  int mitad = (ini + fin) / 2;
  Dias izq = hallarCantidadDias(arr, ini, mitad, menor);
  Dias der = hallarCantidadDias(arr, mitad + 1, fin, menor);


  for (int i=izq.fin+1; i<der.ini; i++)
    if (arr[i] != menor) {
      int izqLon = izq.fin - izq.ini;
      int derLon = der.fin - der.ini;
      if (izqLon < derLon)
        return der;
      return izq;
    }
    else {
      izq.fin++;
      izq.cantidad++;
    }

  return {izq.ini, der.fin, izq.cantidad + der.cantidad};

}


int main() {

  int arr[30];

  leerDatos(arr);

  Solucion sol = resolver(arr, 0, N-1);

  cout << "El menor peso fue de " << sol.numero <<". El rango de días en que lo obtuvo fue del " << sol.ini+1 << " al " << sol.fin+1 << "." << endl;


  return 0;
}


