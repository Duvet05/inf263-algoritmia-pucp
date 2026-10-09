#include <iostream>
using namespace std;

// Función recursiva para resolver el problema de las Torres de Hanói
void hanoi(int n, char origen, char destino, char auxiliar) {
    // Caso base: Si solo hay un disco, moverlo directamente al destino
    if (n == 1) {
        cout << "Mover disco 1 desde " << origen << " hasta " << destino << endl;
        return;
    }
    
    // Paso 1: Mover n-1 discos desde el origen al auxiliar
    hanoi(n - 1, origen, auxiliar, destino);
    
    // Paso 2: Mover el disco restante al destino
    cout << "Mover disco " << n << " desde " << origen << " hasta " << destino << endl;
    
    // Paso 3: Mover los n-1 discos desde el auxiliar al destino
    hanoi(n - 1, auxiliar, destino, origen);
}

int main() {
    int discos;
    
    cout << "Introduce el número de discos: ";
    cin >> discos;
    
    cout << "Los pasos para resolver las Torres de Hanói con " << discos << " discos son:\n";
    hanoi(discos, 'A', 'C', 'B'); // A: origen, C: destino, B: auxiliar
    
    return 0;
}
