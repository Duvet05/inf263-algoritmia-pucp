#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

struct Recurso {
  int costo;
  int recursos_implementados[3];
  int cantidad_recursos;
  int nivel_de_seguridad;
};

void leerArchivo(Recurso *&recursos, int &cantidad_recursos) {
  ifstream archivo("p2.txt");
  if (!archivo.is_open()) {
    cerr << "Error al abrir el archivo." << endl;
    return;
  }

  archivo >> cantidad_recursos;
  recursos = new Recurso[cantidad_recursos];
  for (int i = 0; i < cantidad_recursos; ++i) {
    archivo >> recursos[i].costo;
    archivo >> recursos[i].cantidad_recursos;
    for (int j = 0; j < recursos[i].cantidad_recursos; ++j) {
      archivo >> recursos[i].recursos_implementados[j];
    }
    archivo >> recursos[i].nivel_de_seguridad;
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

bool verificarRecursosImplementados(int *cromosoma, Recurso *recursos, int tamano_cromosoma, int recurso) {
  // Verificar que todos los recursos esten cubiertos
  for (int j=0; j<tamano_cromosoma; j++) {
    if (cromosoma[j]) {
      Recurso r = recursos[j];
      for (int k=0; k<r.cantidad_recursos; ++k) {
        int r_implementado = r.recursos_implementados[k];
        for (int m=0; m<tamano_cromosoma; ++m) {
          if (cromosoma[m] != 1 && m == r_implementado - 1) {
            return false;
          }
        }
      }
    }
  }
  return true;
}

int main() {

  Recurso *recursos = nullptr;
  int cantidad_recursos = 0;
  int presupuesto = 0;

  cout << "Ingrese el presupuesto disponible: ";
  cin >> presupuesto;

  leerArchivo(recursos, cantidad_recursos);

  int tamano_cromosoma = cantidad_recursos;
  int *cromosoma = new int[tamano_cromosoma];
  int combinaciones = pow(2, tamano_cromosoma);
  int mejor_combinacion = 0;
  int prespuesto_minimo = 0.8 * presupuesto;

  for (int i=0; i<combinaciones; ++i) {

    cargarCromosoma(cromosoma, tamano_cromosoma, i);

    int costo_total = 0;
    for (int j=0; j<tamano_cromosoma; ++j) {
      if (cromosoma[j] == 1) {
        costo_total += recursos[j].costo;
      }
    }
    if (costo_total <= presupuesto && costo_total >= prespuesto_minimo) {

      if (verificarRecursosImplementados(cromosoma, recursos, tamano_cromosoma, cantidad_recursos)) {
        
        // imprimer cromosoma valido
        cout << "Combinacion valida: " << i << " con costo total: " << costo_total << endl;
        for (int j=0; j<tamano_cromosoma; ++j) {
          if (cromosoma[j] == 1) {
            cout << "Recurso " << j+1 << " con costo: " << recursos[j].costo << endl;
          }
        }
        cout << endl;

      }

    }



  }






  return 0;
}