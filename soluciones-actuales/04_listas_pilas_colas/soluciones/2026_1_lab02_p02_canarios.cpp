#include <iostream>

// Aporte[receptor][donante] indica cuanto material genetico recibio
// el primer canario del segundo.
//
// Estrategia: eliminar candidatos por parejas mediante recursion. Si el
// candidato actual aporto al nuevo canario, este nuevo canario no puede ser
// ancestral; si no aporto, el candidato actual queda descartado. Al final,
// se verifica recursivamente al unico candidato. Tiempo O(n), sin ciclos ni
// estructuras auxiliares.
int buscarCandidato(const int aporte[][10], int indice) {
    if (indice == 0) return 0;

    int candidato = buscarCandidato(aporte, indice - 1);
    if (aporte[indice][candidato] > 0) return candidato;
    return indice;
}

// Comprueba que el candidato aporto a todos y no recibio de ninguno,
// ignorando su aporte consigo mismo.
bool esAncestral(const int aporte[][10], int cantidad,
                 int candidato, int indice) {
    if (indice == cantidad) return true;
    if (indice == candidato)
        return esAncestral(aporte, cantidad, candidato, indice + 1);

    if (aporte[indice][candidato] == 0 || aporte[candidato][indice] != 0)
        return false;
    return esAncestral(aporte, cantidad, candidato, indice + 1);
}

int canarioAncestral(const int aporte[][10], int cantidad) {
    if (cantidad <= 0) return -1;

    int candidato = buscarCandidato(aporte, cantidad - 1);
    if (esAncestral(aporte, cantidad, candidato, 0)) return candidato;
    return -1;
}

int main() {
    const int cantidad = 10;
    const int aporte[10][10] = {
        {100, 0,   50, 40, 30, 20, 30, 0,  80, 0},
        {50,  100, 0,  40, 30, 20, 20, 0,  10, 25},
        {80,  30,  100,40, 30, 0,  30, 20, 10, 60},
        {50,  0,   0,  100,30, 0,  50, 30, 30, 90},
        {50,  10,  10, 10, 100,0,  10, 50, 10, 50},
        {20,  0,   0,  0,  0,  100,90, 20, 40, 20},
        {0,   0,   0,  0,  0,  0,  100,0,  0,  0},
        {0,   0,   0,  0,  0,  0,  50, 100,50, 20},
        {20,  0,   0,  40, 0,  0,  90, 0,  100,10},
        {0,   10,  0,  0,  0,  0,  10, 0,  60, 100}
    };

    std::cout << canarioAncestral(aporte, cantidad) << '\n';
    return 0;
}


// ubicar el canario que empieze con 0 recursivamente
// mi recursion siempre tien que terminar en 0, y la cantidad de 0's sumados sea cantidad - 1
// si no se enceuntra -1 si se enceuntra guardar el numero de canario
//