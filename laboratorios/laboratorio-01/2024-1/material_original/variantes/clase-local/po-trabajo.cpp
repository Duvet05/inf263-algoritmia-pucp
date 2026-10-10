#include <iostream>
#include <fstream>

using namespace std;

struct Guerrero {
    int poder = 0;
    int tipos_de_armas[4] = {0};
};

struct Arma {
    char id = '\0';
    int poder = 0;
    int tipo = 0;
    char armas_prerequisitos[4] = {0};
};

int leerDatos(int &cantidad_guerreros, Guerrero* &guerreros,
              int &cantidad_armas, Arma* &armas, const char* nombre_archivo);
int contarAsignaciones(int cantidad_guerreros, int cantidad_armas);
void cargarCromosoma(int* cromosoma, int cantidad_armas, int numero, int base);
bool esAsignacionValida(const int* cromosoma, int cantidad_guerreros,
                       const Guerrero* guerreros, int cantidad_armas,
                       const Arma* armas);
bool encontrarSolucionFuerzaBruta(int cantidad_guerreros, const Guerrero* guerreros,
                                 int cantidad_armas, const Arma* armas,
                                 int* armas_utilizadas, int &asignaciones_probadas);
void imprimirSolucion(int cantidad_guerreros, const Guerrero* guerreros,
                      int cantidad_armas, const Arma* armas,
                      const int* armas_utilizadas);

// Carga los datos, enumera asignaciones completas e imprime la primera valida.
int main(int argc, char* argv[]) {
    if (argc > 2) {
        cout << "Uso: " << argv[0] << " [archivo_de_datos]\n";
        return 1;
    }

    int cantidad_guerreros = 0, cantidad_armas = 0;
    Guerrero* guerreros = nullptr;
    Arma* armas = nullptr;
    const char* nombre_archivo = argc == 2 ? argv[1] : nullptr;
    if (leerDatos(cantidad_guerreros, guerreros, cantidad_armas,
                  armas, nombre_archivo) != 0) {
        delete[] guerreros;
        delete[] armas;
        return 1;
    }

    int armas_utilizadas[12] = {0};
    int asignaciones_probadas = 0;
    bool encontrada = encontrarSolucionFuerzaBruta(
        cantidad_guerreros, guerreros, cantidad_armas, armas,
        armas_utilizadas, asignaciones_probadas);

    if (encontrada) {
        imprimirSolucion(cantidad_guerreros, guerreros,
                         cantidad_armas, armas, armas_utilizadas);
    } else {
        cout << "No existe una solucion para este caso.\n";
    }
    cout << "Asignaciones probadas: " << asignaciones_probadas << '\n';
    cout << "Asignaciones posibles: "
         << contarAsignaciones(cantidad_guerreros, cantidad_armas) << '\n';

    delete[] guerreros;
    delete[] armas;
    return 0;
}

// Lee el formato del laboratorio y comprueba sus cantidades maximas antes
// de escribir en los arreglos. Conserva un cero final en tipos y requisitos.
int leerDatos(int &cantidad_guerreros, Guerrero* &guerreros,
              int &cantidad_armas, Arma* &armas, const char* nombre_archivo) {
    ifstream archivo(nombre_archivo ? nombre_archivo : "datos1.txt");
    if (!archivo && !nombre_archivo) {
        archivo.clear();
        archivo.open("Copia de datos1.txt");
    }
    if (!archivo) {
        cout << "No se puede abrir el archivo de datos.\n";
        return 1;
    }
    if (!(archivo >> cantidad_guerreros) ||
        cantidad_guerreros < 1 || cantidad_guerreros > 3) {
        cout << "La cantidad de guerreros debe estar entre 1 y 3.\n";
        return 1;
    }
    guerreros = new Guerrero[cantidad_guerreros];
    for (int i = 0; i < cantidad_guerreros; i++) {
        int cantidad_tipos = 0;
        if (!(archivo >> guerreros[i].poder >> cantidad_tipos) ||
            guerreros[i].poder < 0 || cantidad_tipos < 1 || cantidad_tipos > 3) {
            cout << "Datos de guerrero invalidos.\n";
            return 1;
        }
        for (int j = 0; j < cantidad_tipos; j++) {
            if (!(archivo >> guerreros[i].tipos_de_armas[j]) ||
                guerreros[i].tipos_de_armas[j] < 1 ||
                guerreros[i].tipos_de_armas[j] > 3) {
                cout << "Los tipos de armas deben estar entre 1 y 3.\n";
                return 1;
            }
        }
    }

    if (!(archivo >> cantidad_armas) || cantidad_armas < 0 || cantidad_armas > 12) {
        cout << "La cantidad de armas debe estar entre 0 y 12.\n";
        return 1;
    }
    armas = new Arma[cantidad_armas];
    for (int i = 0; i < cantidad_armas; i++) {
        int cantidad_requisitos = 0;
        if (!(archivo >> armas[i].id >> armas[i].poder >> armas[i].tipo
                      >> cantidad_requisitos) || armas[i].poder < 0 ||
            armas[i].tipo < 1 || armas[i].tipo > 3 ||
            cantidad_requisitos < 0 || cantidad_requisitos > 3) {
            cout << "Datos de arma invalidos.\n";
            return 1;
        }
        for (int j = 0; j < i; j++) {
            if (armas[i].id == armas[j].id) {
                cout << "Los identificadores de las armas deben ser distintos.\n";
                return 1;
            }
        }
        for (int j = 0; j < cantidad_requisitos; j++) {
            if (!(archivo >> armas[i].armas_prerequisitos[j])) {
                cout << "Faltan los prerrequisitos de un arma.\n";
                return 1;
            }
        }
    }
    for (int i = 0; i < cantidad_armas; i++) {
        for (int j = 0; j < 3 && armas[i].armas_prerequisitos[j]; j++) {
            int k = 0;
            while (k < cantidad_armas &&
                   armas[k].id != armas[i].armas_prerequisitos[j]) k++;
            if (k == cantidad_armas) {
                cout << "Un prerrequisito menciona un arma que no existe.\n";
                return 1;
            }
        }
    }
    return 0;
}

// Cada arma tiene G+1 destinos: no usarla (0) o uno de los G guerreros.
// Multiplicacion entera: como maximo 4^12 = 16 777 216 asignaciones.
int contarAsignaciones(int cantidad_guerreros, int cantidad_armas) {
    int total = 1;
    for (int i = 0; i < cantidad_armas; i++) total *= cantidad_guerreros + 1;
    return total;
}

// Convierte un numero a base G+1. Cada digito indica el destino de un arma,
// en el orden de lectura. Para tres guerreros: 0=libre, 1=G1, 2=G2, 3=G3.
void cargarCromosoma(int* cromosoma, int cantidad_armas, int numero, int base) {
    for (int j = cantidad_armas - 1; j >= 0; j--) {
        cromosoma[j] = numero % base;
        numero /= base;
    }
}

// Valida una asignacion COMPLETA. Un digito por arma impide reutilizarla.
// Comprueba requisitos en la misma mochila, tipos y poder estrictamente mayor.
bool esAsignacionValida(const int* cromosoma, int cantidad_guerreros,
                       const Guerrero* guerreros, int cantidad_armas = 12,
                       const Arma* armas) {
    long long suma_poder[3] = {0};
    for (int i = 0; i < cantidad_armas; i++) {
        int destino = cromosoma[i];
        //[0,P-1,0,0,0,0,0,0,0,0,0,0] <-- no he usado ninguna
 
        if (destino == 0) continue;
        if (destino < 1 || destino > cantidad_guerreros) return false;

        //por cantidad de prerequisitos, voy a ver si mi arreglo cromosoma,
        //tiene ese prerrequisito
        for (int j = 0; j < 3 && armas[i].armas_prerequisitos[j]; j++) {
            int k = 0;
            while (k < cantidad_armas &&
                   armas[k].id != armas[i].armas_prerequisitos[j]) k++;
            if (k == cantidad_armas || cromosoma[k] != destino) return false;
            //
        }

        const Guerrero &guerrero = guerreros[destino - 1];
        bool tipo_permitido = false;
        for (int j = 0; j < 3 && guerrero.tipos_de_armas[j]; j++) {
            if (armas[i].tipo == guerrero.tipos_de_armas[j]) {
                tipo_permitido = true;
                break;
            }
        }
        if (!tipo_permitido) return false;
        suma_poder[destino - 1] += armas[i].poder;
    }

    for (int g = 0; g < cantidad_guerreros; g++) {
        if (suma_poder[g] < guerreros[g].poder) return false;
    }
    return true;
}

// FUERZA BRUTA ITERATIVA: enumera TODAS las asignaciones completas en orden,
// desde 0 hasta (G+1)^A - 1, y se detiene en la primera que cumple las reglas.
// No utiliza llamadas recursivas ni reservas y liberaciones de mochilas.
bool encontrarSolucionFuerzaBruta(int cantidad_guerreros, const Guerrero* guerreros,
                                 int cantidad_armas, const Arma* armas,
                                 int* armas_utilizadas, int &asignaciones_probadas) {
    const int base = cantidad_guerreros + 1;
    const int combinaciones = contarAsignaciones(cantidad_guerreros, cantidad_armas);
    int cromosoma[12] = {0};
    asignaciones_probadas = 0;
    for (int j = 0; j < cantidad_armas; j++) armas_utilizadas[j] = 0;

    for (int i = 0; i < combinaciones; i++) {
        cargarCromosoma(cromosoma, cantidad_armas, i, base);
        //[0,0,0,0,0,0,0,0,0,0,0,0] <-- no he usado ninguna
        //[1,0,0,0,0,0,0,0,0,0,0,0] <-- he usado el arma Z
        
        asignaciones_probadas++;
        if (esAsignacionValida(cromosoma, cantidad_guerreros, guerreros,
                               cantidad_armas, armas)) {
            for (int j = 0; j < cantidad_armas; j++) {
                armas_utilizadas[j] = cromosoma[j];
            }
            return true;
        }
    }
    return false;
}

// Imprime la mochila de cada guerrero y el poder que supera su objetivo.
void imprimirSolucion(int cantidad_guerreros, const Guerrero* guerreros,
                      int cantidad_armas, const Arma* armas,
                      const int* armas_utilizadas) {
    for (int g = 0; g < cantidad_guerreros; g++) {
        long long poder_total = 0;
        cout << "Guerrero " << g + 1 << '\n';
        cout << "Poder: " << guerreros[g].poder << '\n';
        cout << "Armas en mochila para vencerlo: ";
        for (int j = 0; j < cantidad_armas; j++) {
            if (armas_utilizadas[j] == g + 1) {
                cout << armas[j].id << ' ';
                poder_total += armas[j].poder;
            }
        }
        cout << "\nPoder de la mochila: " << poder_total << "\n\n";
    }
}
