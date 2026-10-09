#include <iostream>
using namespace std;

int Minimo(int A[], int ini, int fin)
{
	int med = (ini + fin) / 2;

	if(med > 0 && A[med] < A[med - 1] && A[med] < A[med + 1])
		return A[med];
	
	if (med > 0 && A[med - 1] < A[med + 1])
		return Minimo(A, ini, med - 1);
	return Minimo(A, med + 1, fin);
}

int main() {

  int arr[] =  {5, 6, 1, 2, 3, 4};
  int N = 6;

  cout << Minimo(arr, 0, N-1) << endl;

  return 0;
}