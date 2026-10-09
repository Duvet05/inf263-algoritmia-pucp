#include "Colas.h"

int main() {

  TCola cola;
  crear_cola(cola);

  encolar(cola, 1);
  encolar(cola, 2);
  encolar(cola, 3);
  encolar(cola, 4);

  imprime_cola(cola);

  desencolar(cola);

  imprime_cola(cola);

  return 0;
}