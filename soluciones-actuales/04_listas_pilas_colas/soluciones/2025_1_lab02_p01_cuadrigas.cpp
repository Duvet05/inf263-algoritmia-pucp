#include <iostream>
#include <cstring>

using namespace std;


struct Cuadriga {
    int id;
    char nombre[50];
    char equipo[30];
};


struct Nodo {
    Cuadriga dato;
    Nodo *sig;
};


struct Lista {
    Nodo *inicio;
    Nodo *fin;
};


void inicializar(Lista &lista) {
    lista.inicio = nullptr;
    lista.fin = nullptr;
}

void insertarFinal(Lista &lista,
                   int id,
                   const char nombre[],
                   const char equipo[]) {

    Nodo *nuevo = new Nodo;

    nuevo->dato.id = id;
    //CADENA DE CARACTERES! ACORDESE DE INICIALIZAR
    strcpy(nuevo->dato.nombre, nombre);
    strcpy(nuevo->dato.equipo, equipo);

    nuevo->sig = nullptr;

    if (lista.inicio == nullptr) {
        lista.inicio = nuevo;
        lista.fin = nuevo;
    }

    else {
        lista.fin->sig = nuevo;
        lista.fin = nuevo;
    }
}


// 4,5,6,8,19,20,13
// lista par: 4 ; lista import: ; lista original: 5,6,8,19,20,13
// lista par: 4 ; lista import: 5; lista original: 6,8,19,20,13
// lista par: 4,6 ; lista import: 5; lista original: 8,19,20,13
// lista par: 4,6,8 ; lista import: 5; lista original: 19,20,13
// lista par: 4,6,8 ; lista import: 5,19; lista original: 20,13
// lista par: 4,6,8,20 ; lista import: 5,19; lista original: 13
// lista par: 4,6,8,20 ; lista import: 5,19,13; lista original:

// lista par: 4,6,8,20 ; lista import: 5,19,13; lista original: 4,6,8,20,5,19,13;



// ESTRATEGIA:
// Se recorre la lista una sola vez.
// Cada nodo se desconecta de su posición original
// y se enlaza al final del grupo de pares o impares.
// No se crean nodos nuevos durante el reordenamiento.
// Finalmente se conecta el último par con el primer impar.
// 13,4,5,6,8,19,20
void reordenar(Lista &lista) {

    Nodo *actual = lista.inicio;

    Nodo *inicioPar = nullptr;
    Nodo *finPar = nullptr;

    Nodo *inicioImpar = nullptr;
    Nodo *finImpar = nullptr;


    while (actual != nullptr) {
        //no perder referencia
        Nodo *siguiente = actual->sig;

        actual->sig = nullptr;


        if (actual->dato.id % 2 == 0) {

            if (inicioPar == nullptr) {

                inicioPar = actual;
                finPar = actual;
            }

            else {

                finPar->sig = actual;
                finPar = actual;
            }
        }

        else {

            if (inicioImpar == nullptr) {

                inicioImpar = actual;
                finImpar = actual;
            }

            else {

                finImpar->sig = actual;
                finImpar = actual;
            }
        }


        actual = siguiente;
    }


    if (inicioPar != nullptr) {

        lista.inicio = inicioPar;

        finPar->sig = inicioImpar;


        if (inicioImpar != nullptr)
            lista.fin = finImpar;

        else
            lista.fin = finPar;
    }

    else {

        lista.inicio = inicioImpar;
        lista.fin = finImpar;
    }
}


void imprimir(const Lista &lista) {

    const Nodo *actual = lista.inicio;

    while (actual != nullptr) {

        cout << "[ID: "
             << actual->dato.id
             << ", Nombre: "
             << actual->dato.nombre
             << ", Equipo: "
             << actual->dato.equipo
             << "]"
             << endl;

        actual = actual->sig;
    }
}

// Libera los nodos una sola vez y deja ambos extremos vacios.
void destruir(Lista &lista) {
    while (lista.inicio != nullptr) {
        Nodo *eliminar = lista.inicio;
        lista.inicio = eliminar->sig;
        delete eliminar;
    }
    lista.fin = nullptr;
}


int main() {

    Lista lista;

    inicializar(lista);


    insertarFinal(lista, 17, "Messala", "Rojo");
    insertarFinal(lista, 4, "Ben-Hur", "Azul");
    insertarFinal(lista, 12, "Artax", "Verde");
    insertarFinal(lista, 7, "Drusus", "Negro");


    cout << "LISTA INICIAL" << endl;

    imprimir(lista);


    reordenar(lista);


    cout << endl;
    cout << "LISTA FINAL" << endl;

    imprimir(lista);


    destruir(lista);

    return 0;
}
