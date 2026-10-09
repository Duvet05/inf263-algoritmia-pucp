// Incidentes de seguridad | Examen 1 de 2023-2, pregunta 2.
// Pilas y cola enlazadas propias: los algoritmos trasladan los mismos nodos.
// Se siguen los nombres de la salida de consola de la pagina 5 del PDF.
// Ver enunciados/incidentes.md para las etiquetas contradictorias del dibujo.
// Compilar desde 04_listas_pilas_colas:
// clang++ -std=c++17 -Wall -Wextra -Wpedantic soluciones/2023_2_ex01_p02_incidentes.cpp -o /tmp/incidentes
// /tmp/incidentes

#include <iostream>

using namespace std;

struct Nodo
{
    int codigo;
    Nodo *siguiente;
};

struct Pila
{
    Nodo *cima = nullptr;
    int longitud = 0;
};

struct Cola
{
    Nodo *inicio = nullptr;
    Nodo *fin = nullptr;
    int longitud = 0;
};

// ====================== Operaciones con nodos existentes ======================

bool esPilaVacia(const Pila &pila)
{
    return pila.cima == nullptr;
}

bool esColaVacia(const Cola &cola)
{
    return cola.inicio == nullptr;
}

// Recibe un nodo aislado y lo coloca en la cima, sin reservar memoria.
void apilarNodo(Pila &pila, Nodo *nodo)
{
    nodo->siguiente = pila.cima;
    pila.cima = nodo;
    pila.longitud++;
}

// Precondicion: la pila tiene al menos un nodo. Lo extrae sin destruirlo.
Nodo *desapilarNodo(Pila &pila)
{
    Nodo *sale = pila.cima;
    pila.cima = sale->siguiente;
    sale->siguiente = nullptr;
    pila.longitud--;
    return sale;
}

// Recibe un nodo aislado y lo coloca al final de la cola.
void encolarNodo(Cola &cola, Nodo *nodo)
{
    nodo->siguiente = nullptr;
    if (esColaVacia(cola))
        cola.inicio = nodo;
    else
        cola.fin->siguiente = nodo;
    cola.fin = nodo;
    cola.longitud++;
}

// Precondicion: la cola tiene al menos un nodo. Lo extrae sin destruirlo.
Nodo *desencolarNodo(Cola &cola)
{
    Nodo *sale = cola.inicio;
    cola.inicio = sale->siguiente;
    if (cola.inicio == nullptr)
        cola.fin = nullptr;
    sale->siguiente = nullptr;
    cola.longitud--;
    return sale;
}

// Estas dos funciones reservan nodos SOLO durante la carga inicial.
void apilarInicial(Pila &pila, int codigo)
{
    apilarNodo(pila, new Nodo{codigo, nullptr});
}

void encolarInicial(Cola &cola, int codigo)
{
    encolarNodo(cola, new Nodo{codigo, nullptr});
}

// ====================== a) Reiniciar la cola ======================

// Ordena por el numero de incidente, codigo % 100, no por el impacto.
// Usa como apoyo la otra pila permitida, que debe estar vacia al comenzar.
// Ascendente significa que el incidente mas antiguo queda en la cima.
// No usa recursion, arreglos ni nodos nuevos. Su tiempo es O(k^2).
void ordenarPorLlegada(Pila &origen, Pila &auxiliar, bool ascendente)
{
    while (!esPilaVacia(origen))
    {
        Nodo *actual = desapilarNodo(origen);
        int llegada = actual->codigo % 100;
        while (!esPilaVacia(auxiliar) &&
               (ascendente ? auxiliar.cima->codigo % 100 > llegada
                           : auxiliar.cima->codigo % 100 < llegada))
            apilarNodo(origen, desapilarNodo(auxiliar));
        apilarNodo(auxiliar, actual);
    }
    while (!esPilaVacia(auxiliar))
        apilarNodo(origen, desapilarNodo(auxiliar));
}

// Rota nodos del inicio al final sin cambiar su identidad.
// Precondicion: cantidad >= 0; si cantidad > 0, la cola no esta vacia.
void rotarCola(Cola &cola, int cantidad)
{
    for (int i = 0; i < cantidad; i++)
        encolarNodo(cola, desencolarNodo(cola));
}

// Precondiciones del caso: la cola esta ordenada por llegada y sus incidentes
// son posteriores a los que esperan en las pilas. Los numeros de incidente
// son unicos. La capacidad no es negativa y la cola inicial no la supera.
// Al terminar: cola con los incidentes mas antiguos que caben, pila1 vacia
// y pila2 con los sobrantes, del mas reciente al mas antiguo desde la cima.
bool reinicia_cola(Cola &cola, int espaciosPermitidos, Pila &pila1, Pila &pila2)
{
    if (espaciosPermitidos < 0 || cola.longitud > espaciosPermitidos)
        return false;

    // Paso 1: reunir en pila1 los incidentes que estaban en ambas pilas.
    while (!esPilaVacia(pila2))
        apilarNodo(pila1, desapilarNodo(pila2));

    // Paso 2: el incidente mas antiguo debe ser el primero en salir.
    ordenarPorLlegada(pila1, pila2, true);

    int ingresar = pila1.longitud;
    if (ingresar > espaciosPermitidos)
        ingresar = espaciosPermitidos;
    int conservarCola = espaciosPermitidos - ingresar;
    if (conservarCola > cola.longitud)
        conservarCola = cola.longitud;
    int retirarCola = cola.longitud - conservarCola;

    // Paso 3, azul: dejar delante los sobrantes y llevarlos a pila2.
    rotarCola(cola, conservarCola);
    for (int i = 0; i < retirarCola; i++)
        apilarNodo(pila2, desencolarNodo(cola));

    // Verde: los incidentes antiguos de pila1 entran en los espacios libres.
    for (int i = 0; i < ingresar; i++)
        encolarNodo(cola, desapilarNodo(pila1));

    // Anaranjado: los incidentes conservados de la cola quedan al final.
    rotarCola(cola, conservarCola);

    // Si la capacidad no alcanza ni para los antiguos, tambien quedan fuera.
    // Reordenar esos sobrantes con las mismas dos pilas; pila1 queda vacia.
    bool quedanAntiguos = !esPilaVacia(pila1);
    while (!esPilaVacia(pila1))
        apilarNodo(pila2, desapilarNodo(pila1));
    if (quedanAntiguos)
        ordenarPorLlegada(pila2, pila1, false);

    return true;
}

// ====================== b) Reclasificar las pilas ======================

// Precondicion: se acaba de ejecutar reinicia_cola con exito.
// La unica estructura auxiliar es la cola temporal permitida.
// La doble transferencia invierte el orden para dejar lo mas antiguo arriba.
// Segun la consola del PDF: pila1 recibe 2xx y pila2 recibe 1xx.
void reclasifica_pilas(Pila &pila1, Pila &pila2)
{
    Cola temporal;
    while (!esPilaVacia(pila2))
        encolarNodo(temporal, desapilarNodo(pila2));

    while (!esColaVacia(temporal))
    {
        Nodo *actual = desencolarNodo(temporal);
        if (actual->codigo / 100 == 2)
            apilarNodo(pila1, actual);
        else
            apilarNodo(pila2, actual);
    }
}

// ====================== c) Mostrar y probar el caso del PDF ======================

// Muestra una pila desde su cima hasta su base.
void imprimirPila(const Pila &pila)
{
    if (esPilaVacia(pila))
        cout << "vacia";
    for (const Nodo *actual = pila.cima; actual != nullptr; actual = actual->siguiente)
    {
        cout << actual->codigo;
        if (actual->siguiente != nullptr) cout << ' ';
    }
    cout << '\n';
}

// Muestra una cola desde su inicio hasta su final.
void imprimirCola(const Cola &cola)
{
    if (esColaVacia(cola))
        cout << "vacia";
    for (const Nodo *actual = cola.inicio; actual != nullptr; actual = actual->siguiente)
    {
        cout << actual->codigo;
        if (actual->siguiente != nullptr) cout << ' ';
    }
    cout << '\n';
}

void mostrarEstado(const char *titulo, const Cola &cola, const Pila &pila1, const Pila &pila2)
{
    cout << titulo << "\nCola: ";
    imprimirCola(cola);
    cout << "Pila 1: ";
    imprimirPila(pila1);
    cout << "Pila 2: ";
    imprimirPila(pila2);
    cout << '\n';
}

// Libera los nodos solo al finalizar el programa.
void destruirPila(Pila &pila)
{
    while (!esPilaVacia(pila))
        delete desapilarNodo(pila);
}

void destruirCola(Cola &cola)
{
    while (!esColaVacia(cola))
        delete desencolarNodo(cola);
}

int main()
{
    Cola cola;
    Pila pila1;
    Pila pila2;
    const int espaciosPermitidos = 8;

    encolarInicial(cola, 206);
    encolarInicial(cola, 107);
    encolarInicial(cola, 208);
    encolarInicial(cola, 109);
    encolarInicial(cola, 210);
    encolarInicial(cola, 211);
    encolarInicial(cola, 112);
    encolarInicial(cola, 113);

    apilarInicial(pila1, 101);
    apilarInicial(pila1, 102);
    apilarInicial(pila1, 105);
    apilarInicial(pila2, 203);
    apilarInicial(pila2, 204);

    mostrarEstado("INICIAL:", cola, pila1, pila2);
    bool reiniciada = reinicia_cola(cola, espaciosPermitidos, pila1, pila2);
    if (reiniciada)
    {
        mostrarEstado("REINICIA COLA:", cola, pila1, pila2);
        reclasifica_pilas(pila1, pila2);
        mostrarEstado("RECLASIFICA PILAS:", cola, pila1, pila2);
    }
    else
        cerr << "La capacidad indicada no admite la cola inicial.\n";

    destruirCola(cola);
    destruirPila(pila1);
    destruirPila(pila2);
    return reiniciada ? 0 : 1;
}
