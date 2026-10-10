#include <iostream>
using namespace std;

const int MAX_ARTICULOS = 20;

// Fuerza bruta: contar las 2^n selecciones con multiplicacion entera.
int contarSelecciones(int n) {
    int total = 1;
    for (int i = 0; i < n; i++) total *= 2;
    return total;
}

// El articulo 0 corresponde al digito de la izquierda (mas significativo).
// Ejemplo: numero 11, n=4 -> [1,0,1,1]. El ultimo articulo cambia primero.
void cargarCromosoma(int numero, int n, int seleccion[]) {
    for (int i = n - 1; i >= 0; i--) {
        seleccion[i] = numero % 2;
        numero /= 2;
    }
}

// Revisa todas las selecciones y conserva la de mayor peso que no excede C.
// No hay valores monetarios: en este ejercicio se maximiza el peso utilizado.
long long resolverMochila(const int pesos[], int n, long long capacidad,
                         int mejor[]) {
    long long mejorPeso = 0;
    int seleccion[MAX_ARTICULOS] = {};
    for (int i = 0; i < n; i++) mejor[i] = 0;
    const int total = contarSelecciones(n);
    for (int codigo = 0; codigo < total; codigo++) {
        cargarCromosoma(codigo, n, seleccion);
        long long peso = 0;
        for (int i = 0; i < n; i++) {
            if (seleccion[i] == 1) peso += pesos[i];
        }
        if (peso <= capacidad && peso > mejorPeso) {
            mejorPeso = peso;
            for (int i = 0; i < n; i++) mejor[i] = seleccion[i];
        }
    }
    return mejorPeso;
}

// Entrada por teclado o redireccion: n, capacidad y los n pesos positivos.
// Ejemplo: 4 15 1 2 10 4. La solucion vacia es valida si no entra ningun peso.
int main() {
    int n = 0;
    long long capacidad = 0;
    int pesos[MAX_ARTICULOS] = {}, mejor[MAX_ARTICULOS] = {};
    if (!(cin >> n >> capacidad) || n < 0 || n > MAX_ARTICULOS || capacidad < 0) {
        cerr << "Entrada invalida: 0 <= n <= 20 y capacidad >= 0.\n";
        return 1;
    }
    for (int i = 0; i < n; i++) {
        if (!(cin >> pesos[i]) || pesos[i] <= 0) {
            cerr << "Cada peso debe ser un entero positivo.\n";
            return 1;
        }
    }
    const long long mejorPeso = resolverMochila(pesos, n, capacidad, mejor);
    cout << "Seleccion (orden de entrada): ";
    for (int i = 0; i < n; i++) cout << mejor[i] << ' ';
    cout << "\nPesos elegidos: ";
    for (int i = 0; i < n; i++) if (mejor[i]) cout << pesos[i] << ' ';
    cout << "\nPeso total: " << mejorPeso;
    cout << "\nEspacio libre: " << capacidad - mejorPeso;
    cout << "\nSelecciones revisadas: " << contarSelecciones(n) << '\n';
    return 0;
}
