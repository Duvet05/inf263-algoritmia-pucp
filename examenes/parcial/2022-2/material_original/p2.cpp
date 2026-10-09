#include <iostream>
#include <fstream>
using namespace std;

typedef int ElementoPila;

typedef struct nodoP
{
    ElementoPila elemento;
    struct nodoP *sig;
} NodoP;

typedef struct pila
{
    NodoP *cima;
    int longitud;
} Pila;

void construirPila( Pila *pP )
{
    pP->cima = NULL;
    pP->longitud = 0;
}

int esPilaVacia( Pila P )
{
    return P.cima == NULL;
    // return C.longitud == 0;
}

NodoP* crearNuevoNodo( ElementoPila elemento, NodoP *sig )
{
    NodoP *pNuevoNodo;
    pNuevoNodo = new NodoP;
    pNuevoNodo->elemento = elemento;
    pNuevoNodo->sig = sig;
    return pNuevoNodo;
}

void apilar( Pila *pP, ElementoPila elemento)
{
    NodoP *pNuevoNodo;
    pNuevoNodo = crearNuevoNodo( elemento, pP->cima );
    pP->cima = pNuevoNodo;
    pP->longitud++;
}
//agregamos los parametros que la pila actual posee y los imprimos:
void mostrarP( Pila P )
{
    NodoP *pNodo;
    if ( esPilaVacia(P) )
        printf("La pila esta vacia\n");
    else
    {
        pNodo = P.cima;
        while ( pNodo != NULL )
        {
            printf("%d \n", pNodo->elemento);
            pNodo = pNodo->sig;
        }
        printf("\n\n");
    }
}

int obtenerLongitudP( Pila P )
{
    return P.longitud;    
}

ElementoPila desapilar( Pila *pP )
{
    NodoP *pNodo;
    ElementoPila elemento;
    pNodo = pP->cima;
    elemento = pNodo->elemento;
    pP->cima = pNodo->sig;
    pP->longitud--;
    delete pNodo;
    return elemento;
}
//destruir Pila, similar a destruir lista.
void destruir_Pila(Pila *pP){    
    NodoP* recorrido = pP->cima;
    while(recorrido != NULL){
        NodoP *nodo_a_eliminar=recorrido;        
        recorrido = recorrido->sig;
        delete nodo_a_eliminar;
    }
    pP->cima=NULL;
    pP->longitud=0;
}
ElementoPila cima(Pila p){
    if(esPilaVacia(p)) exit(2);
    return (ElementoPila)(p.cima->elemento); 
}


//Para el desarrollo de esta pregunta haremos uso del codigo del profe Hilmar Hinojosa.
int hallar_frecuencia_max(int frecuencia[],int cant_datos,int *frecMax,int *durMax){
    //creamos y construimos la pila:
    Pila pila_frecuencia;
    construirPila(&pila_frecuencia);
    
    int frecuen_actual,duracion_actual;
    int area_max=0,i=0;
    int tp,area_tope;

    while(i<cant_datos){
        if(esPilaVacia(pila_frecuencia) || frecuencia[cima(pila_frecuencia)] <= frecuencia[i]){
            apilar(&pila_frecuencia,i);
            i++;
        }else{
            tp = desapilar(&pila_frecuencia);
            if(esPilaVacia(pila_frecuencia)){
                area_tope = frecuencia[tp]*i;
                frecuen_actual = frecuencia[tp];
                duracion_actual = i;
            }else{
                area_tope = frecuencia[tp]*(i-cima(pila_frecuencia)-1);
                frecuen_actual = frecuencia[tp];
                duracion_actual = i-cima(pila_frecuencia)-1;
            }            
            if(area_max < area_tope){
                area_max = area_tope;
                (*frecMax) = frecuen_actual; // FRECUENCIA MÁXIMA
                (*durMax) = duracion_actual;   // DURACION MÁXIMA
            }
        }
    }   
    while(!esPilaVacia(pila_frecuencia)){
        tp = desapilar(&pila_frecuencia);
        if(esPilaVacia(pila_frecuencia)){
            frecuen_actual = frecuencia[tp];
            area_max = frecuencia[tp]*i;
            duracion_actual = i;
        }else{
            area_tope = frecuencia[tp]*(i-cima(pila_frecuencia)-1);
            frecuen_actual = frecuencia[tp];
            duracion_actual = i-cima(pila_frecuencia)-1;
        }
        if(area_max < area_tope){
            area_max = area_tope;
            (*frecMax) = frecuen_actual;
            (*durMax)= duracion_actual;
        }
    }
    destruir_Pila(&pila_frecuencia);
    
    return area_max;
}

int main(int argc, char** argv) {   
    int cant_datos,i;
    cout << "Ingrese la cantidad de datos: ";
    cin >> cant_datos;
    cout << "Ingrese los datos de frecuencia:" << endl;
    int frecuencia[cant_datos];
    for(i=0;i<cant_datos;i++){
        cin >> frecuencia[i];
    }
    /*Datos utilizados:  
     * 11
     * 1 2 1 4 5 6 4 5 2 2 1
    */
    int frecuencia_max = 0;
    int duracion_max = 0;
    hallar_frecuencia_max(frecuencia,cant_datos,&frecuencia_max,&duracion_max);
    
    cout << "La maxima �rea es: " << frecuencia_max * duracion_max << endl;
    cout << "Frecuencia: " << frecuencia_max << endl;
    cout << "Duracion: " << duracion_max << endl;
    return 0;
}



