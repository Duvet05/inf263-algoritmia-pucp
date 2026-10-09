#include <iostream>
#include <fstream>
using namespace std;

struct Riesgo {
  int id;
  int impacto;
  int riesgo;
};

void merge(Riesgo arr[], int ini, int mid, int end, int modo);
void merge_sort(Riesgo arr[], int ini, int end, int modo);
bool leerDatos(Riesgo **riesgos, int* cantidadRiesgos);
void imprimeRiesgos(Riesgo *riesgos, int cantidadRiesgos);

int main() {

  Riesgo *riesgos;
  int cantidadRiesgos;

  if (!leerDatos(&riesgos, &cantidadRiesgos))
    return 1;

  merge_sort(riesgos, 0, cantidadRiesgos-1, 0);
  imprimeRiesgos(riesgos, cantidadRiesgos);

  merge_sort(riesgos, 0, cantidadRiesgos-1, 1);
  imprimeRiesgos(riesgos, cantidadRiesgos);

  merge_sort(riesgos, 0, cantidadRiesgos-1, 2);
  imprimeRiesgos(riesgos, cantidadRiesgos);

  return 0;
}

void merge(Riesgo arr[], int ini, int mid, int end, int modo){
	int p=0,q=0;
	int left_arr_len = mid - ini + 1; //{0,1,2,3}
	int right_arr_len = end - mid;
	Riesgo left_array[left_arr_len + 1];
	Riesgo right_array[right_arr_len + 1];

	for (int i=ini; i<=mid; i++)
		left_array[i-ini] = arr[i];

	for (int i=mid+1; i<=end; i++)
		right_array[i-mid-1] = arr[i];

	if (modo == 0) {
    left_array[left_arr_len].id = INT_MAX;
    right_array[right_arr_len].id = INT_MAX;
  }
  if (modo == 1) {
    left_array[left_arr_len].impacto = INT_MAX;
    right_array[right_arr_len].impacto = INT_MAX;
  }
  if (modo == 2) {
    left_array[left_arr_len].riesgo = INT_MAX;
    right_array[right_arr_len].riesgo = INT_MAX;
  }
    

	for (int m= ini; m<= end; m++)
		if ((modo == 0 && left_array[p].id < right_array[q].id) ||
        (modo == 1 && left_array[p].impacto < right_array[q].impacto) ||
        (modo == 2 && left_array[p].riesgo < right_array[q].riesgo)) {
        arr[m] = left_array[p++];
    }
		else
			arr[m] = right_array[q++];
}

void merge_sort(Riesgo arr[], int ini, int end, int modo){
	if (ini == end) return;
	int mid = (ini + end) / 2;
	merge_sort(arr, ini, mid, modo);
	merge_sort(arr, mid + 1, end, modo);
	merge(arr, ini, mid, end, modo); 
}

bool leerDatos(Riesgo **riesgos, int* cantidadRiesgos) {
  ifstream archivo("p3.txt");

  if (!archivo) {
    cout << "ERROR: No se puede abrir el archivo p3.txt" << endl;
    return false;
  }
  archivo >> *cantidadRiesgos;
  *riesgos = new Riesgo[*cantidadRiesgos];

  for (int i=0; i<*cantidadRiesgos; i++) {
    archivo >> (*riesgos)[i].id;
    archivo >> (*riesgos)[i].impacto;
    archivo >> (*riesgos)[i].riesgo;
  }

  archivo.close();
  return true;
}

void imprimeRiesgos(Riesgo *riesgos, int cantidadRiesgos) {
  for (int i=0; i<cantidadRiesgos; i++) {
    cout << riesgos[i].id << "-" << riesgos[i].impacto << "-" << riesgos[i].riesgo << "  ";
  }
  cout << endl;
}