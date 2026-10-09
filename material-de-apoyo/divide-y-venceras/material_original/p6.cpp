#include <iostream>
#include <fstream>
#include <climits>
using namespace std;

int merge(int arr[], int ini, int mid, int end){
  int intercambios = 0;
	int p=0,q=0;
	int left_arr_len = mid - ini + 1; //{0,1,2,3}
	int right_arr_len = end - mid;
	int left_array[left_arr_len + 1];
	int right_array[right_arr_len + 1];

	for (int i=ini; i<=mid; i++)
		left_array[i-ini] = arr[i];
	left_array[left_arr_len] = INT_MAX;

	for (int i=mid+1; i<=end; i++)
		right_array[i-mid-1] = arr[i];
	right_array[right_arr_len] = INT_MAX;

	for (int m= ini; m<= end; m++)
		if (left_array[p] < right_array[q])
			arr[m] = left_array[p++];
		else {
      arr[m] = right_array[q++];
      if (p < left_arr_len)
        intercambios += left_arr_len - p;
    }
  return intercambios;
}

int merge_sort(int arr[], int ini, int end){
	if (ini == end) return 0;
	int mid = (ini + end) / 2;
	int izq = merge_sort(arr, ini, mid);
	int der = merge_sort(arr, mid + 1, end);
  cout << "ini: " << ini << endl;
  cout << "end: " << end << endl;
  cout << "izq: " << izq << endl;
  cout << "der: " << der << endl << endl;


	return izq + der + merge(arr, ini, mid, end); 
}

void leerDatos(int **arr, int *n) {

  ifstream archivo("p6.txt");
  if (!archivo) {
    cout << "ERROR: No se puede abrir el archivo p6.txt" << endl;
    exit(-1);
  }
  archivo >> *n;
  *arr = new int[*n];
  for (int i=0; i<*n; i++) {
    archivo >> (*arr)[i];
  }
  archivo.close();
}

int main() {

  int *arr;
  int n;

  leerDatos(&arr, &n);

  int resultado = merge_sort(arr, 0, n-1);

  cout << resultado << endl;

  return 0;
}
