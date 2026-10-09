#include "Listas.h"

int main() {

  TLista lista;
  crear_lista(lista);

  insertar_inicio(lista, 3);
  insertar_inicio(lista, 4);
  insertar_inicio(lista, 2);
  insertar_inicio(lista, 1);

  imprimir(lista);

  ordenar(lista);

  imprimir(lista);

  finalizar_lista(lista);

  return 0;
}