#include <iostream>
using namespace std;

/*
Entrada: {1, 1, 3, 3, 4, 5, 5, 7, 7, 8, 8}
Salida: 4
*/

int resolver(int* arr, int ini, int fin) {

  int med = (ini + fin) / 2;
  cout << "ini: " << ini << endl;
  cout << "med: " << med << endl;
  cout << "fin: " << fin << endl << endl;


  if (med == ini) {
    if (arr[med] == arr[med+1])
      return resolver(arr, med+1, fin);
    return arr[med+1];
  } 
  if (med == fin) {
    if (arr[med-1] == arr[med])
      return resolver(arr, ini, med-1);
    return arr[med-1];
  }
  // punto intermedio
  if (arr[med] == arr[med+1]) {
    if ((med-ini) % 2 == 1)
      return resolver(arr, ini, med-1);
    return resolver(arr, med+1, fin);
  }
  if (arr[med-1] == arr[med]) {
    if ((med-ini) % 2 == 1)
      return resolver(arr, med+1, fin);
    return resolver(arr, ini, med-1);
  }
  return arr[med];
}

int main() {

  int arr[] = {1, 1, 3, 3, 4, 5, 5, 7, 7, 8, 8};
  int N = 11;
  
  cout << resolver(arr, 0, N-1) << endl;

  return 0;
}