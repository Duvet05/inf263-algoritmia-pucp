#include <iostream>
using namespace std;

bool binary_search(int *arr, int start, int end, int k) {
  if (start > end)
    return false;
  int med = (start + end) / 2;
  if (arr[med] == k)
    return true;
  if (arr[med] < k)
    return binary_search(arr, med+1, end, k);
  return binary_search(arr, start, med-1, k);
}

int main() {

  int n = 10;
  int arr[] = {1, 2, 3, 7, 9, 11, 15, 100, 500, 999};

  cout << binary_search(arr, 0, n-1, 3) << endl;

  return 0;
}