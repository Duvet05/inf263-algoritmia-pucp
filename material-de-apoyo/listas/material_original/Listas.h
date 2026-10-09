

#ifndef LISTAS_H
#define LISTAS_H

/*informacion que se almacenara en el nodo*/
typedef int TInfo;

/*se define el  tipo de dato TNodo que representa a una estructura autoreferenciada*/
typedef struct Nodo{
    TInfo elem;
    struct Nodo* sig;
} TNodo;

/*se define el tipo de dato para gestionar la lista enlazada*/
typedef TNodo* TLista;

/*prototipos del TAD Lista*/
void crear_lista(TLista &ptrLista);
int esta_vacia(TLista ptrLista);
void insertar_inicio(TLista &ptrLista, TInfo elem);
void insertar_final(TLista &ptrLista, TInfo elem);
void imprimir(TLista ptrLista);
void finalizar_lista(TLista ptrLista);
int tamano(TLista ptrLista);
TInfo remover_final(TLista& lista);
void invertir(TLista& lista);
void intercambiar(TLista& lista, TNodo* nodo1, TNodo* nodo2);
void ordenar(TLista& lista);


#endif /* LISTAS_H */
