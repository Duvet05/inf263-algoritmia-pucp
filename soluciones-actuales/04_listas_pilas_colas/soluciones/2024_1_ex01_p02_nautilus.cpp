// Nautilus | Examen 1 de 2024-1, pregunta 2.
// Una pila enlazada propia, como en bad_sunny_pila_simple.cpp.
// Compilar desde 04_listas_pilas_colas:
// clang++ -std=c++17 -Wall -Wextra -Wpedantic soluciones/2024_1_ex01_p02_nautilus.cpp -o /tmp/nautilus
// /tmp/nautilus

#include <iostream>

using namespace std;

// ======================= Biblioteca de pila =======================

struct Nodo
{
    int nivel;
    Nodo *abajo;
};

struct Pila
{
    Nodo *cima;
};

void construirPila(Pila &pila)
{
    pila.cima = nullptr;
}

bool esPilaVacia(const Pila &pila)
{
    return pila.cima == nullptr;
}

void apilar(Pila &pila, int nivel)
{
    Nodo *nuevo = new Nodo;
    nuevo->nivel = nivel;
    nuevo->abajo = pila.cima; // El nuevo nodo apunta a la cima anterior.
    pila.cima = nuevo;        // Ahora el nuevo nodo es la cima.
}

// Precondicion: la pila no esta vacia.
int desapilar(Pila &pila)
{
    Nodo *sale = pila.cima;
    int nivel = sale->nivel;
    pila.cima = sale->abajo; // La cima baja al siguiente nodo.
    delete sale;
    return nivel;
}

// ========================== Nautilus ==========================

// Precondiciones: n >= 0 y las n ordenes son 'S' o 'B'.
// Estrategia: apilar los niveles 1, 2, ..., n + 1.
// Una B deja los niveles pendientes para imprimirlos en orden inverso.
// Una S (o el final) vacia la pila y completa ese bloque descendente.
// Solo se usa la pila y el arreglo de entrada, que no se modifica.
// Cada nivel se apila y desapila una vez: tiempo O(n), espacio O(n).
void generarMovimientos(const char ordenes[], int n)
{
    Pila pila;
    construirPila(pila);
    bool primero = true;

    // Hay un nivel mas que ordenes: n ordenes unen n + 1 niveles.
    for (int i = 0; i <= n; i++)
    {
        apilar(pila, i + 1);

        // Se comprueba el final primero para no leer ordenes[n].
        if (i == n || ordenes[i] == 'S')
        {
            while (!esPilaVacia(pila))
            {
                if (!primero)
                    cout << ' ';
                cout << desapilar(pila);
                primero = false;
            }
        }
    }

    // El ultimo bloque ya vacio la pila y libero todos sus nodos.
    cout << '\n';
}

int main()
{
    // Cada cadena es el arreglo de entrada de un caso del enunciado.
    generarMovimientos("SSSBS", 5);   // 1 2 3 5 4 6
    generarMovimientos("BBS", 3);     // 3 2 1 4
    generarMovimientos("SBSBBSS", 7); // 1 3 2 6 5 4 7 8
    return 0;
}
