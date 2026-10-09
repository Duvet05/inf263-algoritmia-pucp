
#ifndef ARBOL_H
#define ARBOL_H
/*informacion que se almacenara en el nodo*/
typedef int TInfo;

/*se define el  tipo de dato TNodo que representa a una estructura autoreferenciada*/
typedef struct NodoArbol
{
    TInfo valor;
    struct NodoArbol* izq;
    struct NodoArbol* der;
} TNodoArbol;

/*se define el tipo de dato para gestionar la lista enlazada*/
typedef TNodoArbol* TArbol;

TNodoArbol* crea_nodo(TInfo );
void inserta_nodo(TArbol *ptrArbol, TInfo elem);

void en_orden(TArbol ptrArbol);
void pre_orden(TArbol ptrArbol);
void pos_orden(TArbol ptrArbol);

TNodoArbol* menor(TNodoArbol* nodo);
TNodoArbol* mayor(TNodoArbol* nodo);

TNodoArbol* remover(TNodoArbol* nodo, TInfo info);

int arbol_vacio(TArbol);
TNodoArbol* buscar(TArbol, TInfo);

int altura(TArbol);
int nodos(TArbol);

#endif /* ARBOL_H */
