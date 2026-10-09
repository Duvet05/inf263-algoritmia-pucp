#include <iostream>
#include <fstream>
#include "FuncionesAuxiliares.h"
using namespace std;

int main() {

    int jardin1[4][4] = {
        {1, 1, 1, 0},
        {1, 1, 1, 0},
        {1, 0, 1, 1},
        {1, 1, 0, 0}
    };

    int jardin2[4][5] = {
        {1, 1, 1, 0, 0},
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {1, 1, 0, 0, 0}
    };

    /*
    cout << "MÁXIMO ÁREA DEL JARDÍN 4x4:" << endl;
    cout << "La solución será: " << maxRectanguloJardin1(jardin1, 4, 4) << endl;
    cout << "Ya que el rectángulo máximo esta dado por " << maxRectanguloJardin1(jardin1, 4, 4) << " sectores." << endl;
    */

    cout << "MÁXIMO ÁREA DEL JARDÍN 4x5:" << endl;
    cout << "La solución será: " << maxRectanguloJardin2(jardin2, 4, 5) << endl;
    cout << "Ya que el rectángulo máximo esta dado por " << maxRectanguloJardin2(jardin2, 4, 5) << " sectores." << endl;


    return 0;

}