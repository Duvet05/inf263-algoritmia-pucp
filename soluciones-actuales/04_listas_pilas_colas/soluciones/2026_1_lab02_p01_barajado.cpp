#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
//el dato que quieres guardar (en este caso es una tupla)
struct Carta {
    int numero;
    char palo;
};
//estructura estandar para casos de lista simplemente enlazada
//siempre va a ver un nodo! simplemente enlazada
struct NodoBaraja {
    Carta carta;
    NodoBaraja *sig;
};
//estrutura alternativa para casos de lista doblemente enlazada
/*struct NodoBaraja {
    Carta carta;
    NodoBaraja *sig;
    NodoBaraja *ant;
}; */

//estructura lista! puede guardar "metadata",
//lo que puedes guardar dependende de las condiciones propuestas en el ejercicio
struct Baraja {
    NodoBaraja *inicio;
    NodoBaraja *fin;
    int longitud;
};


// ------------------------------------------------------
// Inicializa la baraja vacía
// ------------------------------------------------------
void inicializar(Baraja &baraja) {
    baraja.inicio = nullptr;
    baraja.fin = nullptr;
    baraja.longitud = 0;
}

// ------------------------------------------------------
// Verificacion de la baraja vacía
// ------------------------------------------------------
bool baraja_vacia(Baraja &baraja) {
    if(baraja.inicio == nullptr){
        return true;
    }
    return false;
}


// ------------------------------------------------------
// Crea un nodo nuevo y lo inserta al final.
// Esta función se usa para CREAR la baraja.
// ------------------------------------------------------
void insertar_final(Baraja &baraja, int numero, char palo) {

    NodoBaraja *nuevo = new NodoBaraja;
    //cargas data e inicializas nodo
    nuevo->carta.numero = numero;
    nuevo->carta.palo = palo;
    nuevo->sig = nullptr;

    if (baraja.inicio == nullptr) {
        baraja.inicio = nuevo;
        baraja.fin = nuevo;
    }
    else {
        baraja.fin->sig = nuevo;
        baraja.fin = nuevo;
    }

    baraja.longitud++;
}


// ------------------------------------------------------
// Inserta al final UN NODO QUE YA EXISTE.
//
// IMPORTANTE:
// Aquí NO hacemos new.
// Esta función sirve para mover nodos durante el barajado.
// ------------------------------------------------------
void insertar_nodo_final(Baraja &baraja, NodoBaraja *nodo) {

    nodo->sig = nullptr;

    if (baraja.inicio == nullptr) {
        baraja.inicio = nodo;
        baraja.fin = nodo;
    }
    else {
        baraja.fin->sig = nodo;
        baraja.fin = nodo;
    }

    baraja.longitud++;
}


// ------------------------------------------------------
// Crea las 52 cartas:
// 13 corazones
// 13 diamantes
// 13 tréboles
// 13 espadas
// ------------------------------------------------------
void crear_baraja(Baraja &baraja) {

    inicializar(baraja);

    char palos[4] = {'C', 'D', 'T', 'E'};

    for (int p = 0; p < 4; p++) {

        for (int numero = 1; numero <= 13; numero++) {

            insertar_final(baraja, numero, palos[p]);
        }
    }
}


// ------------------------------------------------------
// Extrae el nodo que se encuentra en una posición.
//
// Ejemplo:
//
// 0    1    2    3
// A -> B -> C -> D
//
// extraer posición 2:
//
// A -> B -> D
//
// C -> nullptr
// ------------------------------------------------------
NodoBaraja *extraer_en_posicion(Baraja &baraja, int posicion) {
    //que no este vacia
    if (baraja.inicio == nullptr)
        return nullptr;
    //q la posicion exista
    if (posicion < 0 || posicion >= baraja.longitud)
        return nullptr;


    // CASO 1:
    // Queremos extraer el primer nodo.
    if (posicion == 0) {

        NodoBaraja *extraido = baraja.inicio;
        //no perder referencia!
        baraja.inicio = baraja.inicio->sig;

        extraido->sig = nullptr;

        baraja.longitud--;


        // Si la lista quedó vacía,
        // también debemos actualizar fin.
        if (baraja.inicio == nullptr)
            baraja.fin = nullptr;

        return extraido;
    }


    // CASO 2:
    // Buscamos el nodo ANTERIOR al que queremos sacar.
    NodoBaraja *anterior = baraja.inicio;

    for (int i = 0; i < posicion - 1; i++) {
        anterior = anterior->sig;
    }

    NodoBaraja *extraido = anterior->sig;


    // Saltamos el nodo extraído.
    anterior->sig = extraido->sig;


    // Si sacamos el último nodo,
    // el nodo anterior pasa a ser el nuevo final.
    if (extraido == baraja.fin) {
        baraja.fin = anterior;
    }


    // Desconectamos totalmente el nodo.
    extraido->sig = nullptr;

    baraja.longitud--;

    return extraido;
}
// 13D 1T 2T 3T  5T 6T 7T 8T 9T 10T 11T 12T 13T 1E 2E 3E 4E 5E 6E 7E 8E 9E 10E 1C 2C 3C 5C 6C 7C 8C 9C 11C 12C 13C 1D
// 2D 3D 4D 5D 6D 7D 8D  10D 12D
//11E 12E 13E -> 9D

// ------------------------------------------------------
// ESTRATEGIA DE BARAJADO:
//
// La lista tiene dos zonas:
//
// [ zona pendiente | zona ya barajada ]
//
// Elegimos aleatoriamente un nodo de la zona pendiente,
// lo extraemos y lo mandamos al final.
//
// Cada vez la zona pendiente disminuye.
// ------------------------------------------------------
void barajar(Baraja &baraja) {

    int pendientes = baraja.longitud;
    while (pendientes > 0) {

        // Posición solamente dentro de la zona pendiente.
        int posicion = rand() % pendientes; // aleatoriedad se ve reduciendo


        // Sacamos físicamente el nodo.
        NodoBaraja *extraido =
                extraer_en_posicion(baraja, posicion);


        // Lo colocamos al final SIN CREAR NODO NUEVO.
        insertar_nodo_final(baraja, extraido);


        // Una carta más ya quedó barajada.
        pendientes--;
    }
}


// ------------------------------------------------------
void imprimir(const Baraja &baraja) {

    NodoBaraja *actual = baraja.inicio;

    while (actual != nullptr) {

        cout << actual->carta.numero
             << actual->carta.palo
             << " ";

        actual = actual->sig;
    }

    cout << endl;
}


// ------------------------------------------------------
// Elimina todos los nodos.
// ------------------------------------------------------
void destruir(Baraja &baraja) {

    while (baraja.inicio != nullptr) {

        NodoBaraja *eliminar = baraja.inicio;

        baraja.inicio = baraja.inicio->sig;

        delete eliminar;
    }

    baraja.fin = nullptr;
    baraja.longitud = 0;
}


// ------------------------------------------------------
int main() {
    //semilla = time
    srand(time(nullptr));

    Baraja baraja;

    crear_baraja(baraja);

    cout << "BARAJA ORIGINAL" << endl;
    imprimir(baraja);

    cout << endl;

    barajar(baraja);

    cout << "BARAJA BARAJADA" << endl;
    imprimir(baraja);

    destruir(baraja);

    cout << endl;
    cout << "Longitud final: "
         << baraja.longitud
         << endl;

    return 0;
}
