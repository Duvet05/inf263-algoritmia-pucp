// Referencia de estudio: operaciones comunes con una lista simplemente enlazada.
// Guarda enteros; para otro tipo, adapta Elemento y las comparaciones/impresion.
#include <iostream>

using Elemento = int;

struct Nodo {
    Elemento dato;
    Nodo *sig;
};

// La lista es dueña de sus nodos. No copies una Lista por asignacion.
struct Lista {
    Nodo *inicio = nullptr;
    Nodo *fin = nullptr;
    int longitud = 0;
};

// Usar al crear una lista o despues de destruirla, no para vaciarla.
void inicializar(Lista &lista) {
    lista.inicio = nullptr;
    lista.fin = nullptr;
    lista.longitud = 0;
}

bool esListaVacia(const Lista &lista) {
    return lista.inicio == nullptr;
}

int longitud(const Lista &lista) {
    return lista.longitud;
}

// Inserta un nodo aislado que ya existe; no reserva memoria.
void insertarNodoInicio(Lista &lista, Nodo *nodo) {
    if (nodo == nullptr) return;
    nodo->sig = lista.inicio;
    lista.inicio = nodo;
    if (lista.fin == nullptr) lista.fin = nodo;
    lista.longitud++;
}

void insertarNodoFinal(Lista &lista, Nodo *nodo) {
    if (nodo == nullptr) return;
    nodo->sig = nullptr;
    if (esListaVacia(lista)) lista.inicio = nodo;
    else lista.fin->sig = nodo;
    lista.fin = nodo;
    lista.longitud++;
}

// Estas dos funciones crean nodos nuevos.
void insertarInicio(Lista &lista, const Elemento &dato) {
    insertarNodoInicio(lista, new Nodo{dato, nullptr});
}

void insertarFinal(Lista &lista, const Elemento &dato) {
    insertarNodoFinal(lista, new Nodo{dato, nullptr});
}

// Las posiciones empiezan en 0. Para insertar se admite posicion == longitud.
bool insertarEnPosicion(Lista &lista, int posicion, const Elemento &dato) {
    if (posicion < 0 || posicion > lista.longitud) return false;
    if (posicion == 0) insertarInicio(lista, dato);
    else if (posicion == lista.longitud) insertarFinal(lista, dato);
    else {
        Nodo *anterior = lista.inicio;
        for (int i = 0; i < posicion - 1; i++) anterior = anterior->sig;
        anterior->sig = new Nodo{dato, anterior->sig};
        lista.longitud++;
    }
    return true;
}

// Consultas: nullptr si el dato o la posicion no existen.
const Nodo *buscar(const Lista &lista, const Elemento &dato) {
    const Nodo *actual = lista.inicio;
    while (actual != nullptr && actual->dato != dato) actual = actual->sig;
    return actual;
}

const Nodo *obtenerEnPosicion(const Lista &lista, int posicion) {
    if (posicion < 0 || posicion >= lista.longitud) return nullptr;
    const Nodo *actual = lista.inicio;
    for (int i = 0; i < posicion; i++) actual = actual->sig;
    return actual;
}

// Extraer desconecta el nodo, pero no lo borra. El llamador debe reinsertarlo
// o liberarlo con delete. El nodo extraido queda con sig == nullptr.
Nodo *extraerInicio(Lista &lista) {
    if (esListaVacia(lista)) return nullptr;
    Nodo *extraido = lista.inicio;
    lista.inicio = extraido->sig;
    if (lista.inicio == nullptr) lista.fin = nullptr;
    extraido->sig = nullptr;
    lista.longitud--;
    return extraido;
}

Nodo *extraerEnPosicion(Lista &lista, int posicion) {
    if (posicion < 0 || posicion >= lista.longitud) return nullptr;
    if (posicion == 0) return extraerInicio(lista);

    Nodo *anterior = lista.inicio;
    for (int i = 0; i < posicion - 1; i++) anterior = anterior->sig;
    Nodo *extraido = anterior->sig;
    anterior->sig = extraido->sig;
    if (extraido == lista.fin) lista.fin = anterior;
    extraido->sig = nullptr;
    lista.longitud--;
    return extraido;
}

// Eliminar desconecta y libera el nodo.
bool eliminarEnPosicion(Lista &lista, int posicion) {
    Nodo *extraido = extraerEnPosicion(lista, posicion);
    if (extraido == nullptr) return false;
    delete extraido;
    return true;
}

bool eliminarInicio(Lista &lista) {
    return eliminarEnPosicion(lista, 0);
}

bool eliminarFinal(Lista &lista) {
    return eliminarEnPosicion(lista, lista.longitud - 1);
}

bool eliminarDato(Lista &lista, const Elemento &dato) {
    Nodo *anterior = nullptr;
    Nodo *actual = lista.inicio;
    while (actual != nullptr && actual->dato != dato) {
        anterior = actual;
        actual = actual->sig;
    }
    if (actual == nullptr) return false;
    if (anterior == nullptr) lista.inicio = actual->sig;
    else anterior->sig = actual->sig;
    if (actual == lista.fin) lista.fin = anterior;
    delete actual;
    lista.longitud--;
    return true;
}

// Transfiere los nodos de origen al final de destino y vacia origen.
void concatenar(Lista &destino, Lista &origen) {
    if (&destino == &origen || esListaVacia(origen)) return;
    if (esListaVacia(destino)) destino.inicio = origen.inicio;
    else destino.fin->sig = origen.inicio;
    destino.fin = origen.fin;
    destino.longitud += origen.longitud;
    inicializar(origen);
}

void invertir(Lista &lista) {
    Nodo *anterior = nullptr;
    Nodo *actual = lista.inicio;
    lista.fin = lista.inicio;
    while (actual != nullptr) {
        Nodo *siguiente = actual->sig;
        actual->sig = anterior;
        anterior = actual;
        actual = siguiente;
    }
    lista.inicio = anterior;
}

void imprimir(const Lista &lista, std::ostream &salida = std::cout) {
    const Nodo *actual = lista.inicio;
    while (actual != nullptr) {
        salida << actual->dato << " -> ";
        actual = actual->sig;
    }
    salida << "nullptr\n";
}

void destruir(Lista &lista) {
    while (!esListaVacia(lista)) delete extraerInicio(lista);
}

int main() {
    Lista numeros;
    insertarFinal(numeros, 10);
    insertarFinal(numeros, 20);
    insertarEnPosicion(numeros, 1, 15);
    imprimir(numeros); // 10 -> 15 -> 20 -> nullptr

    // Para reordenar sin reservar otro nodo, se extrae y se reinserta.
    Nodo *primero = extraerInicio(numeros);
    insertarNodoFinal(numeros, primero);
    imprimir(numeros); // 15 -> 20 -> 10 -> nullptr

    eliminarDato(numeros, 20);
    invertir(numeros);
    imprimir(numeros); // 10 -> 15 -> nullptr

    destruir(numeros);
    return 0;
}
