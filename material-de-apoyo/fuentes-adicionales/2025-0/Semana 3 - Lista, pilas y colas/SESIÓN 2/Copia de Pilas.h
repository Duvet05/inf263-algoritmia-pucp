
#ifndef PILAS_H
#define PILAS_H

typedef int TInfoP;

typedef struct NodoPila
{
    TInfoP valor;
    struct NodoPila *ptrSig; /*estructura auto-referenciada*/
}TNodoPila;
typedef TNodoPila* TPila;


void crear_pila(TPila &ptrPila);
void push(TPila &ptrPila, TInfoP);
int pila_vacia(TPila ptrPila);
TInfoP pop(TPila& ptrPila);
TInfoP top(TPila ptrPila);
void finalizar(TPila ptrPila);
void imprime_pila(TPila ptrPila);

#endif /* PILAS_H */
