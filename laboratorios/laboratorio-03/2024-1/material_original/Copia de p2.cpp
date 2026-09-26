#include <iostream>
using namespace std;

struct Resultado {
  int posInicial;
  int maxPotencia;
};

int hallarPosInicial(int *arr, int ini, int fin) {

  if (ini >= fin)
    return ini;

  int med = (ini + fin) / 2;

  if (arr[med] > 0)
    return hallarPosInicial(arr, ini, med-1);
  return hallarPosInicial(arr, med+1, fin);
}

int hallarPotenciaMax(int* arr, int ini, int fin) {

  if (ini >= fin)
    return arr[ini];

  int med = (ini + fin) / 2;
  cout << "ini: " << ini << endl;
  cout << "med: " << med << endl;
  cout << "fin: " << fin << endl << endl;

  if (arr[med-1] < arr[med] && arr[med] > arr[med+1])
    return arr[med];
  
  if (med == 0 || (arr[med-1] <= arr[med] && arr[med] <= arr[med+1]))
    return hallarPotenciaMax(arr, med+1, fin);
  return hallarPotenciaMax(arr, ini, med-1);

}

int main() {

  int arr[] = {-1, 0, -1, 0, 1, 1, 2, 2, 3, 3, 4, 3, 3, 2, 2, 1 };
  int n = 16;

  cout << hallarPosInicial(arr, 0, n-1) << endl;
  cout << hallarPotenciaMax(arr, 0, n-1) << endl;

  return 0;
}