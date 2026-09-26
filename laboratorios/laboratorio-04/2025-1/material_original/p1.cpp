#include <iostream>
using namespace std;

int hallar_pico(int ventas_original[7], int ini, int fin) {

  if (ini == fin) {
    cout << "Pico de ventas original: Día " << ini << " - Valor " << ventas_original[ini] << endl;
    return ventas_original[ini];
  }

  int mid = (ini + fin) / 2;

  // comparamos el punto medio con sus vecinos
  // si es creciente, buscamos en la mitad derecha
  if ((ventas_original[mid] >= ventas_original[mid - 1]) &&
      (ventas_original[mid] <= ventas_original[mid + 1])) {
    return hallar_pico(ventas_original, mid + 1, fin);
  }
  // si es decreciente, buscamos en la mitad izquierda
  else if ((ventas_original[mid] <= ventas_original[mid - 1]) &&
           (ventas_original[mid] >= ventas_original[mid + 1])) {
    return hallar_pico(ventas_original, ini, mid - 1);
  }
  // si es un pico, lo devolvemos
  else {
    cout << "Pico de ventas original: Día " << mid << " - Valor " << ventas_original[mid] << endl;
    return ventas_original[mid];
  }

}

int hallar_primer_dia_mayor_que_pico(int ventas_nueva[9], int ini, int fin, int pico) {

  if (ini == fin) {
    cout << "Primer día con ventas mayores que el pico: Día " << ini << " - Valor " << ventas_nueva[ini] << endl;
    return ventas_nueva[ini];
  }

  int mid = (ini + fin) / 2;

  // si el punto medio es menor o igual al pico, buscamos en la mitad derecha
  if (ventas_nueva[mid] <= pico) {
    return hallar_primer_dia_mayor_que_pico(ventas_nueva, mid + 1, fin, pico);
  }
  // si el punto medio es mayor que el pico, buscamos en la mitad izquierda
  else if (ventas_nueva[mid] > pico && ventas_nueva[mid - 1] > pico) {
    return hallar_primer_dia_mayor_que_pico(ventas_nueva, ini, mid, pico);
  }
  else {

    cout << "Primer día con ventas mayores que el pico: Día " << mid << " - Valor " << ventas_nueva[mid] << endl;

    return ventas_nueva[mid];
  }


}


int main() {

  int ventas_original[7] =  {50, 80, 120, 160, 210, 180, 140};
  int ventas_nueva[9] =  {300, 380, 450, 570, 620, 740, 860};

  int pico = hallar_pico(ventas_original, 0, 6);

  int primer_dia_mayor_que_pico = hallar_primer_dia_mayor_que_pico(ventas_nueva, 0, 8, pico); 





  return 0;
}
