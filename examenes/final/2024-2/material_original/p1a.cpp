#include <iostream>
using namespace std;

struct Lote {
  int id;
  int cantidad;
};

int hallarLoteInicial(Lote lotes[], int ini, int fin, int cantidadBuscada) {

  if (ini > fin) {
    return -1;  
  }

  int med = ini + (fin - ini) / 2;
  // comparamos la cantidad del lote en la posición media
  if (lotes[med].cantidad == cantidadBuscada) {
    // Si es igual, verificamos si es el primer lote con esa cantidad
    if (med == 0 || lotes[med - 1].cantidad < cantidadBuscada) {
      return lotes[med].id;  
    } else {
      return hallarLoteInicial(lotes, ini, med - 1, cantidadBuscada);  
    }
  } else if (lotes[med].cantidad < cantidadBuscada) {
    return hallarLoteInicial(lotes, med + 1, fin, cantidadBuscada);  
  } else {
    return hallarLoteInicial(lotes, ini, med - 1, cantidadBuscada);  
  }
}

int hallarLoteFinal(Lote lotes[], int ini, int fin, int cantidadBuscada) {

  if (ini > fin) {
    return -1;  
  }

  int med = ini + (fin - ini) / 2;
  // comparamos la cantidad del lote en la posición media
  if (lotes[med].cantidad == cantidadBuscada) {
    // Si es igual, verificamos si es el último lote con esa cantidad
    if (med == fin || lotes[med + 1].cantidad > cantidadBuscada) {
      return lotes[med].id;  
    } else {
      return hallarLoteFinal(lotes, med + 1, fin, cantidadBuscada);  
    }
  } else if (lotes[med].cantidad < cantidadBuscada) {
    return hallarLoteFinal(lotes, med + 1, fin, cantidadBuscada);  
  } else {
    return hallarLoteFinal(lotes, ini, med - 1, cantidadBuscada);  
  }
}

int main() {

  Lote lotes[] = {{15872, 3}, {15865, 4}, {15866, 4}, {14357, 6}, {14365, 6}, {14368, 6}, {14370, 6}, {19258, 8}, {19260, 8}};
  int cantidadLotes = 9;

  int loteBuscado = 8;

  int loteInicial = hallarLoteInicial(lotes, 0, cantidadLotes - 1, loteBuscado);  
  cout << "Lote inicial: " << loteInicial << endl;
  int loteFinal = hallarLoteFinal(lotes, 0, cantidadLotes - 1, loteBuscado);
  cout << "Lote final: " << loteFinal << endl;


  return 0;
}
