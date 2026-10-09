#include <iostream>
using namespace std;
#include "Pilas.h"

bool es_digito(char c) {
  return '0' <= c && c <= '9';
}

bool es_operador(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/';
}

int convertir_caracter_a_digito(char c) {
  // '0' -> 48
  // '1' -> 49
  // '2' -> 50
  return c - '0';
}

int operar(int n1, char c, int n2) {
  switch(c) {
    case '+':
      return n1 + n2;
    case '-':
      return n1 - n2;
    case '*':
      return n1 * n2;
    case '/':
      return n1 / n2;
  }
  return -1;
}

// "12 4 * 489 -" -> (12 * 4) - 489 = -441
int operar(char* expresion) {

  TPila pila;
  crear_pila(pila);

  int n = 0;
  for (int i=0; expresion[i]; i++) {
    char c = expresion[i];
    if (es_digito(c)) {
      n *= 10;
      n += convertir_caracter_a_digito(c);
    }
    else if (c == ' ') {
      push(pila, n);
      n = 0;
    }
    else if (es_operador(c)) {
      int n2 = pop(pila);
      int n1 = pop(pila);
      n = operar(n1, c, n2);
    }
  }
  return n;
}


int main() {

  char expresion[1000];
  cout << "Ingrese la expresion postfija: ";
  cin.getline(expresion, 1000, '\n');

  int resultado = operar(expresion);
  cout << "Resultado: " << resultado << endl;

  return 0;
}
