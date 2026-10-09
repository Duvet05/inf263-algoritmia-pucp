#include <iostream>
#include <fstream>
using namespace std;
#include "./Cola/BibliotecaCola/funcionesCola.h"
#include "./Cola/BibliotecaCola/Cola.h"


void agregarTemperatura(int k, Cola &cola, double temperatura, double &sumaTemperaturas) {

  if (cola.longitud == k) {
    ElementoCola elem = desencolar(cola);
    sumaTemperaturas -= elem.temperatura;
  }

  ElementoCola elem;
  elem.temperatura = temperatura;
  encolar(cola, elem);
  sumaTemperaturas += temperatura;

}

double calcularPromedio(const Cola &cola, double sumaTemperaturas) {

  if (cola.longitud == 0) {
    return 0.0; 
  }

  return sumaTemperaturas / cola.longitud;
}



int main() {

  Cola cola;
  construir(cola);

  int k;
  cout << "Ingrese el valor de k: ";
  cin >> k;

  double sumaTemperaturas = 0.0;
  
  if (k <= 0)
    return 0;
  
  while (true) {

    cout << "Ingrese la temperatura (o -1 para terminar): ";
    double temperatura;
    cin >> temperatura;

    if (temperatura == -1) {
      break;
    }

    agregarTemperatura(k, cola, temperatura, sumaTemperaturas);

    double promedio = calcularPromedio(cola, sumaTemperaturas);

    cout << "Promedio: " << promedio << endl;

  }

  return 0;
}

