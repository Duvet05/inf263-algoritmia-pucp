#include <iostream>
#include <climits>
using namespace std;

void merge(int *arr, int ini, int mid, int end) {

	int p=0,q=0;
	int left_arr_len = mid - ini + 1;
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
		else
			arr[m] = right_array[q++];

}

void merge_sort(int *arr, int ini, int end){
	if (ini == end) return;
	int mid = (ini + end) / 2;
	merge_sort(arr, ini, mid);
	merge_sort(arr, mid + 1, end);
	merge(arr, ini, mid, end); 
}

int main(){
	int arr[] = {5, 8, 2, 1, 666, 999, 4, 3, 696, 969};
	int n = 10;

	merge_sort(arr, 0, n-1);

	for (int i=0; i<n; i++)
		cout << arr[i] << " ";

  cout << endl;
	return 0;
}