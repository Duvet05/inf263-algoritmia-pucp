
#ifndef COLAS_H
#define COLAS_H

typedef int TInfoC;

typedef struct NodoCola
{
    TInfoC elem;
    struct NodoCola* sig;
} TNodoCola;
typedef TNodoCola* TCola;

/*prototipos para trabajar la cola*/
void crear_cola(TCola &ptrCola);
int cola_vacia(TCola ptrCola);
void encolar(TCola &ptrCola, TInfoC valor);
TInfoC desencolar(TCola &ptrCola);
void imprime_cola(TCola ptrcola);

#endif /* COLAS_H */
