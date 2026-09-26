#include <iostream>
#include <fstream>

using namespace std;

struct Guerrero {
    int poder;
    int cantidadTipos;
    int tiposPermitidos[3];
};

struct Arma {
    char id;
    int poder;
    int tipo;
    int cantidadPrerrequisitos;
    char prerrequisitos[3];
};

/*
 * Lee el mismo formato de datos1.txt del laboratorio. Comprueba los limites
 * antes de llenar los arreglos: hasta 3 guerreros, 12 armas y 3 prerrequisitos.
 * Las cantidades, poderes, tipos y dependencias se reciben desde el archivo.
 */
bool leerDatos(istream &entrada, int &cantidadGuerreros, Guerrero guerreros[],
               int &cantidadArmas, Arma armas[]) {
    if (!(entrada >> cantidadGuerreros) ||
        cantidadGuerreros < 1 || cantidadGuerreros > 3) {
        return false;
    }

    for (int i = 0; i < cantidadGuerreros; i++) {
        Guerrero &guerrero = guerreros[i];
        if (!(entrada >> guerrero.poder >> guerrero.cantidadTipos) ||
            guerrero.poder < 0 ||
            guerrero.cantidadTipos < 1 || guerrero.cantidadTipos > 3) {
            return false;
        }
        for (int j = 0; j < guerrero.cantidadTipos; j++) {
            if (!(entrada >> guerrero.tiposPermitidos[j]) ||
                guerrero.tiposPermitidos[j] < 1 ||
                guerrero.tiposPermitidos[j] > 3) {
                return false;
            }
        }
    }

    if (!(entrada >> cantidadArmas) || cantidadArmas < 0 || cantidadArmas > 12) {
        return false;
    }

    for (int i = 0; i < cantidadArmas; i++) {
        Arma &arma = armas[i];
        if (!(entrada >> arma.id >> arma.poder >> arma.tipo
                      >> arma.cantidadPrerrequisitos) ||
            arma.poder < 0 || arma.tipo < 1 || arma.tipo > 3 ||
            arma.cantidadPrerrequisitos < 0 || arma.cantidadPrerrequisitos > 3) {
            return false;
        }
        for (int j = 0; j < i; j++) {
            if (armas[j].id == arma.id) {
                return false;
            }
        }
        for (int j = 0; j < arma.cantidadPrerrequisitos; j++) {
            if (!(entrada >> arma.prerrequisitos[j])) {
                return false;
            }
        }
    }
    return true;
}

/* Busca por su letra el arma que se necesita como prerrequisito. */
int buscarIndiceArma(const Arma armas[], int cantidadArmas, char id) {
    for (int i = 0; i < cantidadArmas; i++) {
        if (armas[i].id == id) {
            return i;
        }
    }
    return -1;
}

/*
 * Convierte un numero a base G+1, siendo G la cantidad de guerreros.
 * Cada posicion del cromosoma representa un arma:
 *   0 = no usarla; 1..G = colocarla en la mochila de ese guerrero.
 * Con los 3 guerreros del ejemplo, se utiliza base 4.
 */
void cargarCromosoma(int numero, int base, int cantidadArmas, int cromosoma[]) {
    for (int i = 0; i < cantidadArmas; i++) {
        cromosoma[i] = numero % base;
        numero /= base;
    }
}

/*
 * Valida una asignacion completa. El cromosoma impide reutilizar un arma.
 * Verifica tipos permitidos, prerrequisitos en la MISMA mochila y que cada
 * guerrero reciba un poder estrictamente mayor al suyo.
 */
bool esAsignacionValida(const int cromosoma[], int cantidadGuerreros,
                       const Guerrero guerreros[], int cantidadArmas,
                       const Arma armas[]) {
    long long poderes[3] = {};

    for (int i = 0; i < cantidadArmas; i++) {
        int mochila = cromosoma[i];
        if (mochila == 0) {
            continue;
        }

        int guerrero = mochila - 1;
        bool tipoPermitido = false;
        for (int j = 0; j < guerreros[guerrero].cantidadTipos; j++) {
            if (armas[i].tipo == guerreros[guerrero].tiposPermitidos[j]) {
                tipoPermitido = true;
                break;
            }
        }
        if (!tipoPermitido) {
            return false;
        }

        for (int j = 0; j < armas[i].cantidadPrerrequisitos; j++) {
            int requisito = buscarIndiceArma(armas, cantidadArmas,
                                            armas[i].prerrequisitos[j]);
            if (requisito == -1 || cromosoma[requisito] != mochila) {
                return false;
            }
        }

        poderes[guerrero] += armas[i].poder;
    }

    for (int i = 0; i < cantidadGuerreros; i++) {
        if (poderes[i] <= guerreros[i].poder) {
            return false;
        }
    }
    return true;
}

/*
 * Fuerza bruta iterativa: enumera los (G+1)^N cromosomas completos y prueba
 * cada uno. Se detiene al encontrar una solucion, como solicita el enunciado.
 * Con G=3 y N=12 hay 4^12 = 16 777 216 posibilidades.
 * No hay llamadas recursivas ni construccion de soluciones por backtracking.
 */
bool resolverFuerzaBruta(int cantidadGuerreros, const Guerrero guerreros[],
                        int cantidadArmas, const Arma armas[], int solucion[]) {
    int base = cantidadGuerreros + 1;
    int totalCombinaciones = 1;
    for (int i = 0; i < cantidadArmas; i++) {
        totalCombinaciones *= base;
    }

    for (int numero = 0; numero < totalCombinaciones; numero++) {
        cargarCromosoma(numero, base, cantidadArmas, solucion);
        if (esAsignacionValida(solucion, cantidadGuerreros, guerreros,
                              cantidadArmas, armas)) {
            return true;
        }
    }
    return false;
}

/* Muestra las armas de cada mochila y el poder reunido para vencer al enemigo. */
void imprimirSolucion(int cantidadGuerreros, const Guerrero guerreros[],
                      int cantidadArmas, const Arma armas[], const int solucion[]) {
    for (int i = 0; i < cantidadGuerreros; i++) {
        cout << "Guerrero " << i + 1 << '\n';
        cout << "Poder del guerrero: " << guerreros[i].poder << '\n';
        cout << "Armas en mochila para vencerlo:";
        long long poderReunido = 0;
        for (int j = 0; j < cantidadArmas; j++) {
            if (solucion[j] == i + 1) {
                cout << ' ' << armas[j].id;
                poderReunido += armas[j].poder;
            }
        }
        cout << "\nPoder reunido: " << poderReunido << "\n\n";
    }
}

/*
 * Carga los datos, ejecuta la busqueda y muestra una solucion si existe.
 * Uso: ./p1 [archivo_de_datos]. Si no se indica archivo, usa datos1.txt.
 */
int main(int argc, char *argv[]) {
    if (argc > 2) {
        cerr << "Uso: " << argv[0] << " [archivo_de_datos]\n";
        return 1;
    }
    const char *ruta = argc == 2 ? argv[1] : "datos1.txt";
    ifstream archivo(ruta);
    if (!archivo) {
        cerr << "No se pudo abrir el archivo: " << ruta << '\n';
        return 1;
    }

    int cantidadGuerreros = 0;
    int cantidadArmas = 0;
    Guerrero guerreros[3] = {};
    Arma armas[12] = {};
    int solucion[12] = {};

    if (!leerDatos(archivo, cantidadGuerreros, guerreros, cantidadArmas, armas)) {
        cerr << "Datos invalidos. Revise el formato y los limites del enunciado.\n";
        return 1;
    }

    if (resolverFuerzaBruta(cantidadGuerreros, guerreros,
                           cantidadArmas, armas, solucion)) {
        imprimirSolucion(cantidadGuerreros, guerreros,
                         cantidadArmas, armas, solucion);
    } else {
        cout << "No existe una solucion para este caso.\n";
    }
    return 0;
}
