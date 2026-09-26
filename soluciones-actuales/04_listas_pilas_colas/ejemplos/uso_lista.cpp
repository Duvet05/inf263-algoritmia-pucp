#include <iostream>
#include "../biblioteca/listas/FuncionesLista.h"

int main() {
    listas::Lista lista;
    listas::inicializar(lista);

    listas::insertarFinal(lista, 20);
    listas::insertarInicio(lista, 10);
    listas::insertarEnPosicion(lista, 1, 15);
    std::cout << "Lista inicial: ";
    listas::imprimir(lista); // 10 -> 15 -> 20 -> nullptr

    const listas::Nodo *encontrado = listas::buscar(lista, 15);
    if (encontrado != nullptr) std::cout << "Encontrado: " << encontrado->dato << '\n';

    // Mover el primer nodo al final reutiliza la misma memoria.
    listas::Nodo *extraido = listas::extraerInicio(lista);
    listas::insertarNodoFinal(lista, extraido);
    std::cout << "Primero al final: ";
    listas::imprimir(lista); // 15 -> 20 -> 10 -> nullptr

    listas::eliminarDato(lista, 20);
    listas::invertir(lista);
    std::cout << "Tras eliminar 20 e invertir: ";
    listas::imprimir(lista); // 10 -> 15 -> nullptr

    listas::destruir(lista);
    std::cout << "Longitud final: " << listas::longitud(lista) << '\n';
    return 0;
}
