#include "Pilas.h"
#include <iostream>
using namespace std;

/* al inicio la pila se inicializa con nulo, lo que indica que estaÂ¡ vacia*/
void crear_pila(TPila &ptrPila)
{
    ptrPila = nullptr;
}

/*Se implementaraÂ¡ usando una lista simplemente enlazada. push insertaraÂ¡ siempre
 un nodo al inicio.*/
void push(TPila &ptrPila, TInfoP valor)
{
    TNodoPila *ptrNuevo;
    
    ptrNuevo = new TNodoPila;
    ptrNuevo->valor = valor;
    ptrNuevo->ptrSig = ptrPila;
    ptrPila = ptrNuevo;
}

int pila_vacia(TPila ptrPila)
{
    return ptrPila == nullptr;
}

/*Dado que se ha realizado una insercion al inicio, para que la estructura se
 comporte como pila, se debe sacar los dados a partir del inicio de la lista.*/

TInfoP pop(TPila &ptrPila)
{    
    TNodoPila *ptrEliminar;
    TInfoP valor;
    
    if (!pila_vacia(ptrPila)) { 
        ptrEliminar = ptrPila;
        valor = ptrEliminar->valor; 
        ptrPila = ptrEliminar->ptrSig; 
        delete ptrEliminar;
    }
    return valor;
}

TInfoP top(TPila Pila)
{
    return Pila->valor;
}


/*Libera toda la memoria reservada para la lista utilizada en la pila.*/
void finalizar(TPila ptrPila)
{
    TNodoPila *ptrEliminar = ptrPila;
    
    while (ptrEliminar != nullptr)
    {    
        ptrPila = ptrEliminar->ptrSig;
        delete ptrEliminar;
        ptrEliminar = ptrPila;
    }
}

/*Solo para ver resultados*/
void imprime_pila(TPila ptrpila)
{
    for (; ptrpila != nullptr; ptrpila = ptrpila->ptrSig)
        cout << ptrpila->valor << " ";
    cout << endl;
}


