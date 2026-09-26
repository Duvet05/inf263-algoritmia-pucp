

#include "arbol.h"
#include <iostream>
using namespace std;

/////////////////////////////////////////////////////////////////////

TNodoArbol* crea_nodo(TInfo info)
{
    TNodoArbol *nuevo = new TNodoArbol;
    nuevo->valor = info;
    nuevo->izq = nuevo->der = nullptr;
    return nuevo;
}
/*Si el valor se encuentra, no lo inserta*/
void inserta_nodo(TArbol *arbol, TInfo info)
{
    if (*arbol == nullptr)
        *arbol = crea_nodo(info);
    else
    {
       TNodoArbol* ptrPadre = nullptr;
       TNodoArbol* ptrRecorrido = *arbol;

       while (ptrRecorrido != nullptr)
       {
           ptrPadre = ptrRecorrido;
           if (ptrRecorrido->valor > info)
               ptrRecorrido = ptrRecorrido->izq;
           else if (ptrRecorrido->valor < info)
               ptrRecorrido = ptrRecorrido->der;
           else
               ptrRecorrido = ptrRecorrido->der;
       }

       if (ptrPadre->valor > info)
           ptrPadre->izq = crea_nodo(info);
       else
           ptrPadre->der = crea_nodo(info);
   }
}

void en_orden(TArbol ptrArbol)
{
    if (ptrArbol)
    {
        en_orden(ptrArbol->izq);
        cout << ptrArbol->valor << " ";
        en_orden(ptrArbol->der);
    }
}

void pre_orden(TArbol ptrArbol)
{
    if (ptrArbol)
    {
        cout << ptrArbol->valor << " ";
        pre_orden(ptrArbol->izq);
        pre_orden(ptrArbol->der);
    }
}

void pos_orden(TArbol ptrArbol)
{
    if (ptrArbol)
    {
        pos_orden(ptrArbol->izq);
        pos_orden(ptrArbol->der);
        cout << ptrArbol->valor << " ";
    }
}


TNodoArbol* menor(TNodoArbol* nodo)
{
    if (nodo == nullptr || nodo->izq == nullptr)
        return nodo;
    return menor(nodo->izq);
}
TNodoArbol* mayor(TNodoArbol* nodo)
{
    if (nodo == nullptr || nodo->der == nullptr)
        return nodo;
    return mayor(nodo->der);
}

TNodoArbol* remover(TNodoArbol* nodo, TInfo info)
{
    if (nodo == nullptr)
        return nullptr;
    
    if (info < nodo->valor)
        nodo->izq = remover(nodo->izq, info);
    else if (info > nodo->valor)
        nodo->der = remover(nodo->der, info);
    else
    {
        if (nodo->izq == nullptr)
        {
            TNodoArbol *aux = nodo->der;
            delete nodo;
            return aux;
        }
        if (nodo->der == nullptr)
        {
            TNodoArbol *aux = nodo->izq;
            delete nodo;
            return aux;
        }

        TNodoArbol* m = menor(nodo->der);
        nodo->valor = m->valor;
        nodo->der = remover(nodo->der, m->valor);
    }
   
    return nodo;
}

int arbol_vacio(TArbol arbol)
{
    return arbol == nullptr;
}

TNodoArbol* buscar(TArbol arbol, TInfo info)
{
    if (arbol_vacio(arbol))
        return nullptr;
    
    if (arbol->valor == info)
        return arbol;
    
    if (arbol->valor < info)
        return buscar(arbol->der, info);
    return buscar(arbol->izq, info);
}

int altura(TArbol arbol)
{
    if (arbol_vacio(arbol))
        return 0;
    
    int izq = altura(arbol->izq);
    int der = altura(arbol->der);
    
    return 1 + ((izq > der) ? izq : der);
}

int nodos(TArbol arbol)
{
    if (arbol_vacio(arbol))
        return 0;
    return 1 + nodos(arbol->izq) + nodos(arbol->der);
}
