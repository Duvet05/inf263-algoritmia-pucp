#include <iostream>
using namespace std;

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    // Arreglos temporales
    int* L = new int[n1];
    int* R = new int[n2];

    // Copiar datos a L[] y R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int i = 0; i < n2; i++)
        R[i] = arr[m + 1 + i];

    int i = 0, j = 0, k = l;

    // Mezclar los arreglos temporales de vuelta en arr[]
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copiar los elementos restantes
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    // Liberar memoria
    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}


int hallarCantidadParesAnomalos(int arr[], int ini, int fin) {

  if (ini >= fin) {
    return 0;
  }

  int med = (ini + fin) / 2;

  int izq = hallarCantidadParesAnomalos(arr, ini, med);
  int der = hallarCantidadParesAnomalos(arr, med + 1, fin);

  cout << "Cantidad de pares anómalos en izquierda: " << izq << endl;
  cout << "Cantidad de pares anómalos en derecha: " << der << endl;

  // ordenamiento de ambos arreglos por mergesort
  int arrIzq[med - ini + 1];
  int arrDer[fin - med];

  for (int i = 0; i < med - ini + 1; i++) {
    arrIzq[i] = arr[ini + i];
  }
  for (int i = 0; i < fin - med; i++) {
    arrDer[i] = arr[med + 1 + i];
  }

  mergeSort(arrIzq, 0, med-ini);
  mergeSort(arrDer, 0, fin-med-1);

  int i=0;
  int j=0;
  int contador = 0;

  while (i < med - ini + 1 && j < fin - med) {
    if (arrIzq[i] <= arrDer[j]) {
      i++;
    } else {
      j++;
      contador += j;
    }
  }

  cout << "Cantidad de pares anómalos entre ambos: " << contador << endl;

  return izq + der + contador;
}

int main() {

  int arr[] = {10, 12, 14, 13, 11, 15};
  int n = 6;

  int cantidadParesAnomalos = hallarCantidadParesAnomalos(arr, 0, n - 1);
  cout << "Cantidad de pares anómalos: " << cantidadParesAnomalos << endl;

  return 0;
}