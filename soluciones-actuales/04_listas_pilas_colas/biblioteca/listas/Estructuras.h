#ifndef LISTAS_ESTRUCTURAS_H
#define LISTAS_ESTRUCTURAS_H

namespace listas {

// Para otro ejercicio, adapta Elemento al dato que guardara cada nodo.
using Elemento = int;

struct Nodo {
    Elemento dato;
    Nodo *sig;
};

// Una lista es duena de sus nodos. Pasarla por referencia, nunca copiarla.
struct Lista {
    Nodo *inicio = nullptr;
    Nodo *fin = nullptr;
    int longitud = 0;
};

} // namespace listas

#endif
