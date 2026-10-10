// TortuNinjas | Examen 1 de 2023-2, pregunta 1.
// Listas simplemente enlazadas propias; todos los datos se ingresan por teclado.
// Reparto mediante busqueda iterativa con retroceso: no se usa recursion.
// Compilar desde 04_listas_pilas_colas:
// clang++ -std=c++17 -Wall -Wextra -Wpedantic soluciones/2023_2_ex01_p01_tortuninjas.cpp -o /tmp/tortuninjas
// /tmp/tortuninjas < tests/datos/tortuninjas-ejemplo.txt

#include <iostream>

using namespace std;

// ====================== Estructuras ======================

struct Nodo
{
    int peso;
    Nodo *siguiente;
};

struct Lista
{
    Nodo *inicio = nullptr;
    Nodo *fin = nullptr;
};

struct Camion
{
    Lista artefactos;
};

struct TortuNinja
{
    const char *nombre;
    long long capacidad = 0;
    long long carga = 0;
    int primerCamion = -1;
    int segundoCamion = -1;
};

// ====================== Lista simple ======================

// Agrega un artefacto nuevo al final. Solo se usa al ingresar los datos.
void insertarFinal(Lista &lista, int peso)
{
    Nodo *nuevo = new Nodo{peso, nullptr};
    if (lista.inicio == nullptr)
        lista.inicio = nuevo;
    else
        lista.fin->siguiente = nuevo;
    lista.fin = nuevo;
}

// Recorre la lista para sumar los pesos sin modificarla.
long long sumarPesos(const Lista &lista)
{
    long long total = 0;
    for (const Nodo *actual = lista.inicio; actual != nullptr; actual = actual->siguiente)
        total += actual->peso;
    return total;
}

// Imprime los pesos de los artefactos; el 0 de fin de ingreso no es un nodo.
void imprimirLista(const Lista &lista)
{
    for (const Nodo *actual = lista.inicio; actual != nullptr; actual = actual->siguiente)
    {
        cout << actual->peso;
        if (actual->siguiente != nullptr)
            cout << ' ';
    }
    cout << '\n';
}

// Libera los nodos al terminar el programa.
void destruirLista(Lista &lista)
{
    while (lista.inicio != nullptr)
    {
        Nodo *sale = lista.inicio;
        lista.inicio = sale->siguiente;
        delete sale;
    }
    lista.fin = nullptr;
}

// ====================== a) Ingreso variable ======================

// Cada camion recibe tantos artefactos como se ingresen antes de un 0.
bool leerCamiones(Camion camiones[], int cantidad)
{
    for (int i = 0; i < cantidad; i++)
    {
        cout << "Pesos del camion " << i + 1 << " (0 para terminar): ";
        int peso;
        while (true)
        {
            if (!(cin >> peso) || peso < 0)
                return false;
            if (peso == 0)
                break;
            insertarFinal(camiones[i].artefactos, peso);
        }
    }
    return true;
}

// ====================== b) Reparto iterativo con retroceso ======================

// Prueba un ninja para cada camion mediante un while, sin recursion.
// actual indica el camion por repartir y candidato el siguiente ninja a probar.
// Si un camino falla, deshace la ultima asignacion y prueba el siguiente ninja.
// Precondiciones: 5 <= cantidad <= 8 y los ninjas no tienen asignaciones.
// No modifica las listas ni necesita arreglos o pilas auxiliares.
bool buscarAsignacion(const Camion camiones[], int cantidad, TortuNinja tortugas[])
{
    int actual = 0;
    int candidato = 0;

    while (actual >= 0)
    {
        if (actual == cantidad)
        {
            // Todos los camiones se asignaron; los cuatro ninjas deben participar.
            bool todosParticipan = true;
            for (int i = 0; i < 4; i++)
                if (tortugas[i].primerCamion == -1)
                    todosParticipan = false;
            if (todosParticipan)
                return true;
        }
        else
        {
            long long peso = sumarPesos(camiones[actual].artefactos);

            // Saltar a los ninjas que ya tienen dos camiones o no tienen capacidad.
            while (candidato < 4 &&
                   (tortugas[candidato].segundoCamion != -1 ||
                    tortugas[candidato].carga + peso > tortugas[candidato].capacidad))
                candidato++;

            if (candidato < 4)
            {
                TortuNinja &ninja = tortugas[candidato];
                if (ninja.primerCamion == -1)
                    ninja.primerCamion = actual;
                else
                    ninja.segundoCamion = actual;
                ninja.carga += peso;

                // Avanzar: el siguiente camion empieza probando con Leonardo.
                actual++;
                candidato = 0;
                continue;
            }
        }

        // No se pudo seguir, o falta que participe algun ninja: retroceder.
        actual--;
        if (actual < 0)
            break; // Se agotaron todas las alternativas.

        long long peso = sumarPesos(camiones[actual].artefactos);
        for (int i = 0; i < 4; i++)
        {
            TortuNinja &ninja = tortugas[i];
            if (ninja.segundoCamion == actual)
                ninja.segundoCamion = -1;
            else if (ninja.primerCamion == actual)
                ninja.primerCamion = -1;
            else
                continue;

            // Deshacer ese reparto y recordar por que ninja seguir.
            ninja.carga -= peso;
            candidato = i + 1;
            break;
        }
    }
    return false;
}

// ====================== c) Burbuja y union sin nodos nuevos ======================

// Burbuja: compara vecinos e intercambia sus pesos hasta que no haya cambios.
// No reserva nodos, no usa otra lista y no usa arreglos auxiliares.
void ordenarBurbuja(Lista &lista, bool ascendente)
{
    if (lista.inicio == nullptr)
        return;

    bool huboCambio;
    do
    {
        huboCambio = false;
        for (Nodo *actual = lista.inicio; actual->siguiente != nullptr;
             actual = actual->siguiente)
        {
            Nodo *siguiente = actual->siguiente;
            bool fueraDeOrden = ascendente ? actual->peso > siguiente->peso
                                           : actual->peso < siguiente->peso;
            if (fueraDeOrden)
            {
                int temporal = actual->peso;
                actual->peso = siguiente->peso;
                siguiente->peso = temporal;
                huboCambio = true;
            }
        }
    } while (huboCambio);
}

// Inserta un nodo de origen despues de cada nodo original de destino.
// Los nodos sobrantes se enlazan al final. Origen queda vacia.
// Precondicion: destino y origen son listas diferentes.
void intercalarListas(Lista &destino, Lista &origen)
{
    if (destino.inicio == nullptr)
    {
        destino.inicio = origen.inicio;
        destino.fin = origen.fin;
        origen.inicio = nullptr;
        origen.fin = nullptr;
        return;
    }

    Nodo *actual = destino.inicio;
    while (actual != nullptr && origen.inicio != nullptr)
    {
        Nodo *siguienteDestino = actual->siguiente;
        Nodo *intercalado = origen.inicio;
        origen.inicio = intercalado->siguiente;
        if (origen.inicio == nullptr)
            origen.fin = nullptr;

        actual->siguiente = intercalado;
        intercalado->siguiente = siguienteDestino;
        if (siguienteDestino == nullptr)
            destino.fin = intercalado;
        actual = siguienteDestino;
    }

    if (origen.inicio != nullptr)
    {
        destino.fin->siguiente = origen.inicio;
        destino.fin = origen.fin;
        origen.inicio = nullptr;
        origen.fin = nullptr;
    }
}

// Prepara el camion final de cada ninja que recibio dos camiones.
// Solo modifica las listas originales, con punteros y variables simples.
void prepararRescate(Camion camiones[], const TortuNinja tortugas[])
{
    for (int i = 0; i < 4; i++)
    {
        int primero = tortugas[i].primerCamion;
        int segundo = tortugas[i].segundoCamion;
        if (segundo != -1)
        {
            ordenarBurbuja(camiones[primero].artefactos, true);
            ordenarBurbuja(camiones[segundo].artefactos, false);
            intercalarListas(camiones[primero].artefactos, camiones[segundo].artefactos);
        }
    }
}

// Muestra un unico camion final por ninja. Requiere un reparto valido.
void mostrarRescate(const Camion camiones[], const TortuNinja tortugas[])
{
    for (int i = 0; i < 4; i++)
    {
        cout << tortugas[i].nombre << ": ";
        imprimirLista(camiones[tortugas[i].primerCamion].artefactos);
    }
}

// Limpia la memoria del ingreso; las listas absorbidas ya estan vacias.
void liberarCamiones(Camion camiones[], int cantidad)
{
    for (int i = 0; i < cantidad; i++)
        destruirLista(camiones[i].artefactos);
    delete[] camiones;
}

int main()
{
    int cantidad;
    cout << "Cantidad de camiones (5 a 8): ";
    if (!(cin >> cantidad) || cantidad < 5 || cantidad > 8)
    {
        cerr << "La cantidad debe estar entre 5 y 8.\n";
        return 1;
    }

    TortuNinja tortugas[4] = {
        {"Leonardo"}, {"Rafael"}, {"Donatello"}, {"Miguel Angel"}};
    for (int i = 0; i < 4; i++)
    {
        cout << "Capacidad maxima de " << tortugas[i].nombre << ": ";
        if (!(cin >> tortugas[i].capacidad) || tortugas[i].capacidad < 0)
        {
            cerr << "La capacidad debe ser un entero no negativo.\n";
            return 1;
        }
    }

    // El arreglo de camiones pertenece al ingreso. Su cantidad no es fija.
    Camion *camiones = new Camion[cantidad];
    if (!leerCamiones(camiones, cantidad))
    {
        cerr << "Ingrese pesos positivos y un 0 al terminar cada camion.\n";
        liberarCamiones(camiones, cantidad);
        return 1;
    }

    cout << '\n';
    if (buscarAsignacion(camiones, cantidad, tortugas))
    {
        cout << "Las TortuNinjas completaron su mision.\n";
        prepararRescate(camiones, tortugas);
        mostrarRescate(camiones, tortugas);
    }
    else
        cout << "Las TortuNinjas no pueden completar la mision.\n";

    liberarCamiones(camiones, cantidad);
    return 0;
}
