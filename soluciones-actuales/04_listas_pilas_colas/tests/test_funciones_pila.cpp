#include <cassert>
#include <sstream>
#include "../biblioteca/pilas/FuncionesPila.h"

int main() {
    pilas::Pila pila;
    pilas::Elemento dato = -1;

    // Pila vacia: nada que consultar ni desapilar.
    assert(pilas::esPilaVacia(pila) && pilas::altura(pila) == 0);
    assert(pilas::cima(pila) == nullptr);
    assert(!pilas::desapilar(pila, dato) && dato == -1);
    assert(pilas::desapilarNodo(pila) == nullptr);
    pilas::apilarNodo(pila, nullptr);
    assert(pilas::esPilaVacia(pila));

    // LIFO: el ultimo en entrar es el primero en salir.
    for (int i = 1; i <= 5; i++) pilas::apilar(pila, i);
    assert(pilas::altura(pila) == 5 && *pilas::cima(pila) == 5);
    std::ostringstream salida;
    pilas::imprimir(pila, salida);
    assert(salida.str() == " 1 2 3 4 5"); // De la base a la cima.
    assert(pilas::desapilar(pila, dato) && dato == 5);
    assert(*pilas::cima(pila) == 4 && pilas::altura(pila) == 4);

    // Mover nodos conserva la memoria: el mismo nodo cambia de pila.
    pilas::Pila otra;
    pilas::Nodo *nodo = pilas::desapilarNodo(pila);
    assert(nodo != nullptr && nodo->dato == 4 && nodo->sig == nullptr);
    pilas::apilarNodo(otra, nodo);
    assert(otra.lista.inicio == nodo && *pilas::cima(otra) == 4);
    assert(pilas::altura(pila) == 3 && *pilas::cima(pila) == 3);

    // Muchas operaciones seguidas mantienen el orden.
    for (int i = 0; i < 5000; i++) pilas::apilar(otra, i);
    for (int i = 4999; i >= 0; i--) assert(pilas::desapilar(otra, dato) && dato == i);
    assert(pilas::altura(otra) == 1 && *pilas::cima(otra) == 4);

    pilas::destruir(pila);
    pilas::destruir(otra);
    pilas::destruir(otra); // Destruir una pila vacia es valido.
    assert(pilas::esPilaVacia(pila) && pilas::esPilaVacia(otra));
    assert(pila.lista.fin == nullptr && otra.lista.fin == nullptr);
    return 0;
}
