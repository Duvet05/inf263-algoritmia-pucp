#include <iostream>
using namespace std;

int maximo(int A[], int ini, int fin)
{
  if (ini >= fin)
    return A[ini];

	int med = (ini + fin) / 2;

	if(A[med] <= A[med - 1] && A[med] >= A[med + 1])
		return A[med - 1];
	
	if (A[med - 1] <= A[med + 1])
		return maximo(A, med + 1, fin);
	return maximo(A, ini, med - 1);
}

int main() {

  int arr[] =  {8, 10, 20, 80, 100, 200, 400, 500, 3, 2, 1};
  int N = 11;

  cout << maximo(arr, 0, N-1) << endl;

  return 0;
}