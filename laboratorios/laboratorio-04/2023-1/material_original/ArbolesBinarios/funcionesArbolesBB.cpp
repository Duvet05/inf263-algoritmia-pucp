/* 
 * File:   funcionesArbolesBB.cpp
 * Author: ANA RONCAL
 * Created on 24 de septiembre de 2023, 10:36 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "NodoArbol.h"
#include "ArbolBinario.h"
#include "funcionesArbolesBB.h"
#include "ArbolBinarioBusqueda.h"
using namespace std;
#include "funcionesArbolesBinarios.h"


void construir(struct ArbolBinarioBusqueda & arbol){
    construir(arbol.arbolBinario);
}

bool esArbolVacio(const struct ArbolBinarioBusqueda & arbol){
    return esArbolVacio(arbol.arbolBinario);
}

void plantarArbolBB(struct NodoArbol *& arbol, 
                    struct NodoArbol * arbolIzquierdo, int elemento, 
                    struct NodoArbol * arbolDerecho){
    
    struct NodoArbol * nuevoNodo = new struct NodoArbol;
    nuevoNodo->elemento = elemento;
    nuevoNodo->izquierda = arbolIzquierdo;
    nuevoNodo->derecha = arbolDerecho;
    arbol = nuevoNodo;
}

void insertarRecursivo(struct NodoArbol *& raiz, int elemento){
    if(esNodoVacio(raiz))
        plantarArbolBB(raiz, nullptr, elemento, nullptr);
    else
        if (raiz->elemento > elemento)
            insertarRecursivo(raiz->izquierda, elemento);
        else
            // if(raiz->elemento < elemento)
                insertarRecursivo(raiz->derecha, elemento);
            //else
                //cout<<endl<<"El elemento "<< elemento <<" ya se encuentra en el árbol"<< endl;
}

void insertar(struct ArbolBinarioBusqueda & arbol, int elemento){
    insertarRecursivo(arbol.arbolBinario.raiz, elemento);
}

void enOrden(const struct ArbolBinarioBusqueda & arbol){
    recorrerEnOrden(arbol.arbolBinario);
}

void preOrden(const struct ArbolBinarioBusqueda & arbol){
    recorrerPreOrden(arbol.arbolBinario);
}

void postOrden(const struct ArbolBinarioBusqueda & arbol){
    recorrerPostOrden(arbol.arbolBinario);
}

void destruirArbolBB(struct ArbolBinarioBusqueda & arbol){
    destruirArbolBinario(arbol.arbolBinario);
}

int minimoNodoABB(const struct ArbolBinarioBusqueda & arbolBB){
    return minimoNodo(arbolBB.arbolBinario.raiz);
}
int maximoNodoABB(const struct ArbolBinarioBusqueda & arbolBB){
    return maximoNodo(arbolBB.arbolBinario.raiz);
}

int minimoNodo(struct NodoArbol * nodo){
    /*como el algoritmo busca el menor, se mueve a la izquierda*/
    if(esNodoVacio(nodo))
        return -1;
    if(esNodoVacio(nodo->izquierda))
        return nodo->elemento;
    /*busca en la izquierda*/
    return minimoNodo(nodo->izquierda);        
}

int maximoNodo(struct NodoArbol * nodo){
    if(esNodoVacio(nodo)){
        return -1;
    }
    if(esNodoVacio(nodo->derecha))
        return nodo->elemento;
    return maximoNodo(nodo->derecha);
}


struct NodoArbol *  minimoArbol(struct NodoArbol * nodo){
    if(esNodoVacio(nodo))
        return nodo;
    if(esNodoVacio(nodo->izquierda))
        return nodo;
    return minimoArbol(nodo->izquierda);
}

struct NodoArbol * eliminarNodoRecursivo(struct NodoArbol * nodo, int elemento){
    
    if(esNodoVacio(nodo))
        return nodo;
    //Buscamos el nodo a eliminar
    /*caso que el elemento a eliminar se encuentre a la izquierda*/
    if(nodo->elemento > elemento)
        nodo->izquierda = eliminarNodoRecursivo(nodo->izquierda, elemento);
    else
        /*caso que el elemento a eliminar se encuentre a la derecha*/
        if(nodo->elemento < elemento)
            nodo->derecha = eliminarNodoRecursivo(nodo->derecha, elemento);
        else
            /*encontró el elemento*/
            /*caso de una sola hoja derecha*/
            if(esNodoVacio(nodo->izquierda)){
                struct NodoArbol * hijo = nodo->derecha;
                delete nodo;
                return hijo;
            }
            else
                /*caso de una sola hoja izquierda*/
                if(esNodoVacio(nodo->derecha)){
                    struct NodoArbol * hijo = nodo->izquierda;
                    delete nodo;
                    return hijo;
                }
                else{
                    /*el elemento a eliminar tiene dos descendientes*/
                    struct NodoArbol * minNodo = minimoArbol(nodo->derecha);
                    /*se sustituye el elemento por el mínimo encontrado*/
                    nodo->elemento = minNodo->elemento;
                    /*se elimina el nodo que se reemplazo*/
                    nodo->derecha = eliminarNodoRecursivo(nodo->derecha, minNodo->elemento);
                }   
    return nodo;
}

void  eliminarNodo(struct ArbolBinarioBusqueda & arbol, int dato){
    arbol.arbolBinario.raiz = eliminarNodoRecursivo(arbol.arbolBinario.raiz, dato);
}

int comparaABB(int elementoA, int elementoB ){
    if(elementoA == elementoB) return 0;
    else if(elementoA < elementoB) return -1;
    else if (elementoA > elementoB) return 1;
    return 1;
}

bool buscaArbolRecursivo(struct NodoArbol * nodo, int dato){
    if(esNodoVacio(nodo)){
        return false;
    } 
    if(comparaABB(nodo->elemento, dato) == 0)
        return true;
    if(comparaABB(nodo->elemento, dato) == 1)
        return buscaArbolRecursivo(nodo->izquierda, dato);
    else
        if(comparaABB(nodo->elemento, dato) == -1) 
            return buscaArbolRecursivo(nodo->derecha, dato);
    return false;
}

bool buscaArbol(const struct ArbolBinarioBusqueda & arbol ,int dato){
    return buscaArbolRecursivo(arbol.arbolBinario.raiz, dato);
}



