#include <iostream>
#include <cstring>
using namespace std;

int factorial(int n) {
  if (n == 0)
    return 1;
  else
    return n * factorial(n-1);
}

int fibonacci(int n) {
  if (n == 1)
    return 0;
  else if (n == 2)
    return 1;
  else
    return fibonacci(n-2) + fibonacci(n-1);
}

// cuando tenemos un arreglo en la funcion recursiva, el caso base (generalmente) es cuando solo hay un elemento en el arreglo
int mayor(int *a, int n) {
  if (n == 1)
    return a[0];
  else {
    int valor = a[n-1];
    int mayor_valor_hasta_n_menos_1 = mayor(a, n-1);
    if (valor > mayor_valor_hasta_n_menos_1)
      return valor;
    else
      return mayor_valor_hasta_n_menos_1;
  }
}

bool hallar(int *a, int n, int x) {

  if (n == 1)
    return a[0] == x;
  else
    return a[n-1] == x || hallar(a, n-1, x);
}

void imprime_en_base_2(int n) {
  // n = 6 -> 110
  // n % 2 = 0
  // n /= 2
  // n % 2 = 1
  // n /= 2
  // n % 2 = 1
  if (n == 0)
    return;
  else {
    imprime_en_base_2(n/2);
    cout << n%2;
  } 
}


bool es_palindromo(char *cadena, int start, int end) {
  // level -> es palindromo

  if (start == end)
    return true;
  if (start == end-1)
    return cadena[start] == cadena[end];
  return cadena[start] == cadena[end] && es_palindromo(cadena, start+1, end-1);

}

int main() {
  
  char *cadena = "aa";

  cout << es_palindromo(cadena, 0, strlen(cadena) - 1) << endl;

  return 0;
}