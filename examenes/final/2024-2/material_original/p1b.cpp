#include <iostream>
#include <string>
using namespace std;

struct Plato { 
  string nombre; 
  int cantidadDisponible; 
  int cantidadReservada; 
  double porcentajeReservas; 
}; 

void ordenamientoRapido(Plato* platos, int ini, int fin) {

  // Caso base: si el rango es inválido
  if (ini >= fin) return;

  double pivote = platos[fin].porcentajeReservas;

  Plato *menores = new Plato[fin - ini + 1];
  int cantidadMenores = 0;
  Plato *mayores = new Plato[fin - ini + 1];
  int cantidadMayores = 0;

  for (int i = ini; i < fin; i++) {
    if (platos[i].porcentajeReservas < pivote) {
      menores[cantidadMenores++] = platos[i];
    } else {
      mayores[cantidadMayores++] = platos[i];
    }
  }

  for (int i = 0; i < cantidadMayores; i++) {
    platos[ini + i] = mayores[i];
  }

  platos[ini + cantidadMayores] = platos[fin]; // Colocar el pivote en su posición final

  for (int i = 0; i < cantidadMenores; i++) {
    platos[ini + cantidadMayores + 1 + i] = menores[i];
  }

  delete[] menores;
  delete[] mayores;

  ordenamientoRapido(platos, ini, ini + cantidadMayores - 1); // Ordenar la parte izquierda
  ordenamientoRapido(platos, ini + cantidadMayores + 1, fin); // Ordenar la parte derecha
}


int main() {

  Plato platos[] = {
    {"Lomo Saltado", 50, 30 },
    {"Ceviche", 40, 35 },
    {"Ají de Gallina", 30, 10 },
    {"Causa Limeña", 20, 20 },
    {"Arroz con Pollo", 60, 45 }
  };

  // int n = sizeof(platos) / sizeof(platos[0]);
  int n = 5;

  for (int i = 0; i < n; i++) {
    platos[i].porcentajeReservas = (double)platos[i].cantidadReservada / platos[i].cantidadDisponible * 100;
  }

  ordenamientoRapido(platos, 0, n - 1);

  for (int i = 0; i < n; i++) {
    cout << platos[i].nombre << " - Porcentaje de reservas: " << platos[i].porcentajeReservas << "%" << endl;
  }


  return 0;
}
