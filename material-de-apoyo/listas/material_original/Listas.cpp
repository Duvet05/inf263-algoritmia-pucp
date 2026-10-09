
#include <iostream>
using namespace std;
#include "listas.h"


int tamano(TLista ptrLista)
{   TLista ptrrec;
    int cont=0;
    
    ptrrec=ptrLista;
    while(ptrrec)
    {
        ptrrec=ptrrec->sig;
        cont++;
    }
    
    return cont;
}

void crear_lista(TLista &ptrLista){
    ptrLista = nullptr;
}

int esta_vacia(TLista ptrLista){
    return ptrLista==nullptr;
}

void insertar_inicio(TLista &ptrLista, TInfo elem){
    // Primer paso: Crear un nodo con el elemento
    TNodo *ptrNuevo;
    ptrNuevo = new Nodo;
    ptrNuevo->elem = elem;
    // Segundo paso: Insertar el nodo creado al inicio de la lista
    ptrNuevo->sig = ptrLista;
    ptrLista = ptrNuevo;
}

void insertar_final(TLista &ptrLista, TInfo elem){
    // Primer paso: Crear un nodo con el elemento
    TNodo *ptrNuevo;
    ptrNuevo = new Nodo;
    ptrNuevo->elem = elem;
    // Segundo paso: Insertar el nodo creado al final de la lista
    TNodo *ptrRec, *ptrUltimo;
    ptrNuevo->sig = nullptr;
    ptrRec = ptrLista;    
    ptrUltimo = nullptr;
    while (ptrRec){
        ptrUltimo = ptrRec;
        ptrRec = ptrRec->sig;
    }
    if (ptrUltimo)
        ptrUltimo->sig=ptrNuevo;
    else
        ptrLista = ptrNuevo;
      
}

void imprimir(TLista ptrLista){
    TNodo *ptrRec;
    ptrRec = ptrLista;
    
    while (ptrRec){
        cout << ptrRec->elem << " ";
        ptrRec = ptrRec->sig;
    }
    cout << endl;
}

void finalizar_lista(TLista ptrLista){
    TNodo *ptrRec, *ptrLiberar;
    ptrRec = ptrLista;
    
    while (ptrRec){
        ptrLiberar = ptrRec;
        ptrRec = ptrRec->sig;
        delete ptrLiberar;
    }
}

TInfo remover_final(TLista& lista) {
    // Caso particular: La lista esta vacia
    if (esta_vacia(lista))
        return 0;

    TNodo *ptrRec, *ptrUltimo;
    ptrRec = lista;    
    ptrUltimo = nullptr;
    while (ptrRec->sig != nullptr){
        ptrUltimo = ptrRec;
        ptrRec = ptrRec->sig;
    }
    // verificar si la lista solo tiene un nodo
    if (ptrUltimo == nullptr) {
        lista = nullptr;
    }
    else 
        ptrUltimo->sig = nullptr;
    // Elimina el nodo y devuelve su valor
    TInfo elem = ptrRec->elem;
    delete ptrRec;
    return elem;
}

void invertir(TLista& lista) {
    // Caso base
    if (esta_vacia(lista))
        return;

    // Primer paso: Remover el ultimo valor de la lista
    TInfo ultimoValor = remover_final(lista);
    // Segundo paso: Llamada recursiva
    invertir(lista);
    // Tercer paso: Insertar el ultimo valor al inicio de la lista
    insertar_inicio(lista, ultimoValor);
}

void intercambiar(TLista& lista, TNodo* nodo1, TNodo* nodo2) {
    TInfo elem = nodo1->elem;
    nodo1->elem = nodo2->elem;
    nodo2->elem = elem;
}

void ordenar(TLista& lista) {

    /*
    for (int i=0; i<n-1; i++) {
        for (int j=0; j<n-1-i; j++) {
        if (a[j+1] < a[j]) {
            intercambiar(a, j, j+1);
        }
        }
    } 
    */

    int n = tamano(lista);
    TNodo* nodo_i = lista;
    for (int i=0; i<n-1; i++) {
        TNodo* nodo_j = lista;
        for (int j=0; j<n-1-i; j++) {
            if (nodo_j->sig->elem < nodo_j->elem) {
                intercambiar(lista, nodo_j, nodo_j->sig);
            }
            nodo_j = nodo_j->sig;
        }
        nodo_i = nodo_i->sig;
    }


}

