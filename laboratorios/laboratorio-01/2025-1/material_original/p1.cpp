#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

void leerArchivo(int *&discos, int &cantidad_discos, int *&tablas, int &cantidad_tablas) {
  ifstream archivo("p1.txt");
  if (!archivo.is_open()) {
    cerr << "Error al abrir el archivo." << endl;
    return;
  }

  archivo >> cantidad_tablas;
  tablas = new int[cantidad_tablas];
  for (int i = 0; i < cantidad_tablas; ++i) {
    archivo >> tablas[i];
  }

  archivo >> cantidad_discos;
  discos = new int[cantidad_discos];
  for (int i = 0; i < cantidad_discos; ++i) {
    archivo >> discos[i];
  }

  archivo.close();
}

void cargarCromosoma(int *cromosoma, int tamano, int valor) {
  for (int i = 0; i < tamano; ++i) {
    cromosoma[i] = 0;
  }
  for (int i = 0; valor > 0; ++i) {
    if (valor % 2 == 1) {
      cromosoma[i] = 1;
    }
    valor /= 2;
  }
}
// 5 -> 101
// 5 % 2 = 1 -> cromosoma[0] = 1
// 5 / 2 = 2
// 2 % 2 = 0 -> cromosoma[1] = 0
// 2 / 2 = 1
// 1 % 2 = 1 -> cromosoma[2] = 1
// 1 / 2 = 0

int main() {

  int *discos = nullptr;
  int cantidad_discos = 0;
  int *tablas = nullptr;
  int cantidad_tablas = 0;

  leerArchivo(discos, cantidad_discos, tablas, cantidad_tablas);

  for (int i = 0; i < cantidad_discos; ++i) {
    cout << "Disco " << i << ": " << discos[i] << endl;
  }
  for (int i = 0; i < cantidad_tablas; ++i) {
    cout << "Tabla " << i << ": " << tablas[i] << endl;
  }

  int tamano_cromosoma = cantidad_discos * cantidad_tablas;
  int *cromosoma = new int[tamano_cromosoma];
  int combinaciones = pow(2, tamano_cromosoma);
  int velocidad_restante_discos[cantidad_discos]; 
  for (int i = 0; i < cantidad_discos; ++i) {
    velocidad_restante_discos[i] = discos[i];
  }
  int mayor_min = 0;
  int mejor_combinacion = 0;

  for (int i = 0; i < combinaciones; ++i) {

    cargarCromosoma(cromosoma, tamano_cromosoma, i);


    // 1. Verificar que la velocidad restante de los discos no sea negativa
    bool valido = true;
    for (int j = 0; j < tamano_cromosoma; ++j) {
      if (cromosoma[j] == 1) {
        int disco_index = j / cantidad_tablas;
        int tabla_index = j % cantidad_tablas;
        if (velocidad_restante_discos[disco_index] >= tablas[tabla_index]) {
          velocidad_restante_discos[disco_index] -= tablas[tabla_index];
        } else {
          valido = false;
          break;
        }
      }
    }

    // 2. Verificar que todas las tablas esten asignadas
    for (int j = 0; j < cantidad_tablas; ++j) {
      int cantidad_asignaciones = 0;
      for (int k = 0; k < cantidad_discos; ++k) {
        if (cromosoma[k * cantidad_tablas + j] == 1) {
          cantidad_asignaciones++;
        }
      }
      if (cantidad_asignaciones != 1) {
        valido = false;
        break;
      }
    }

    // Verificar si es la mejor combinacion
    if (valido) {
      int minimo_local = INT_MAX;
      for (int k = 0; k < cantidad_discos; ++k) {
        if (velocidad_restante_discos[k] < minimo_local) {
          minimo_local = velocidad_restante_discos[k];
        }
      }
      if (mayor_min < minimo_local) {
        mayor_min = minimo_local;
        mejor_combinacion = i;
      }
    }

    for (int k = 0; k < cantidad_discos; ++k) {
      velocidad_restante_discos[k] = discos[k];
    }
  }

  // Imprimir mejor combinacion
  cargarCromosoma(cromosoma, tamano_cromosoma, mejor_combinacion);
  cout << "Mayor valor minimo: " << mayor_min << endl;
  for (int i=0; i<cantidad_discos; ++i) {
    cout << "Disco " << i+1 << ": ";
    for (int j=0; j<cantidad_tablas; ++j) {
      if (cromosoma[i*cantidad_tablas + j] == 1) {
        cout << "Tabla " << j+1 << " ";
      }
    }
    cout << endl;
  }

  delete[] discos;
  delete[] tablas;
  delete[] cromosoma;

  return 0;
}
