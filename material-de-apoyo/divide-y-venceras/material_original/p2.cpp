#include <iostream>
using namespace std;

/*
  Entrada: {1, 1, 1, 0, 0, 0, 0}
  Output: 4

  Entrada: {1, 1, 1, 1, 1}
  Salida: 0
*/

int resolver(int *arr, int ini, int fin) {

  if (ini >= fin)
    return 1 - arr[ini];

  int med = (ini + fin) / 2;

  if (arr[med] == 0)
    return fin - med + 1 + resolver(arr, ini, med-1);

  return resolver(arr, med+1, fin);
}

int main() {

  int arr[] = {1, 1, 1, 1, 1};
  int N = 5;
  
  cout << resolver(arr, 0, N-1) << endl;


  return 0;
}