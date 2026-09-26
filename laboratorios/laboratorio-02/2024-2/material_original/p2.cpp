#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

const int MAX_LINE = 100;
const int MAX_REGISTROS = 100;
const float VELOCIDAD_PROMEDIO = 45;

struct Registro {
    char id[100];
    char complejidad;
    int hayDisponibilidad;
    float distancia;
    int esHoraPunta;

    int tiempoEspera = 0;
};

struct NodoRegistro {
  Registro reg;
  NodoRegistro* sig = nullptr;
};

struct Lista {
  NodoRegistro* ini = nullptr;
  NodoRegistro* fin = nullptr;
  int n = 0;
};

void insertar(Lista& lista, NodoRegistro* nodo) {

  if (lista.n == 0) {
    lista.ini = nodo;
  }
  else {
    lista.fin->sig = nodo;
  }
  lista.fin = nodo;
  (lista.n)++;
}

NodoRegistro* remover(Lista& lista) {

  if (lista.n == 0)
    return nullptr;

  NodoRegistro* nodo = lista.ini;

  lista.ini = lista.ini->sig;
  (lista.n)--;

  if (lista.n == 0)
    lista.fin = nullptr;

  nodo->sig = nullptr;
  return nodo;
}

void imprime(Lista& lista) {
  for (NodoRegistro* r = lista.ini; r; r = r->sig) {
    cout << "ID: " << r->reg.id
              << ", Tiempo de espera: " << r->reg.tiempoEspera << std::endl;
  }
  cout << endl;
}

void calcularTiempoEspera(Registro& reg) {

  if (reg.complejidad == 'b')
    reg.tiempoEspera += 10;

  if (reg.complejidad == 'm')
    reg.tiempoEspera += 20;

  if (reg.complejidad == 'a')
    reg.tiempoEspera += 30;  

  if (reg.hayDisponibilidad == 0)
    reg.tiempoEspera += 5;
  
  reg.tiempoEspera += (reg.distancia / VELOCIDAD_PROMEDIO) * 60;

  if (reg.esHoraPunta == 1)
    reg.tiempoEspera += 10;
}

void cargarDatosLista(const char* nombreArchivo, Lista& lista) {
  ifstream archivo(nombreArchivo);
  if (!archivo.is_open()) {
    std::cerr << "Error al abrir el archivo: " << nombreArchivo << std::endl;
    return;
  }

  char linea[MAX_LINE];
  Registro registro;

  // P001,m,1,12.5,0

  while (true) {

    char cadena[100];

    archivo.getline(cadena, 100, ',');

    strcpy(registro.id, cadena);

    if (archivo.eof()) break;

    archivo >> registro.complejidad;
    archivo.get();

    archivo >> registro.hayDisponibilidad;
    archivo.get();

    archivo >> registro.distancia;
    archivo.get();

    archivo >> registro.esHoraPunta;
    archivo.get();

    NodoRegistro* nodo = new NodoRegistro;
    nodo->reg = registro;
    calcularTiempoEspera(nodo->reg);
    insertar(lista, nodo);

  }
  archivo.close();
}

void ordenarLista(Lista& lista) {

  Lista arregloListas[10];

  // Pimera pasada
  while (lista.n > 0) {
    NodoRegistro* nodo = remover(lista);
    insertar(arregloListas[nodo->reg.tiempoEspera % 10], nodo);
  }

  for (int i=0; i<10; i++) {
    while (arregloListas[i].n > 0) {
      NodoRegistro* nodo = remover(arregloListas[i]);
      insertar(lista, nodo);
    }
  }

  // Segunda pasada
  while (lista.n > 0) {
    NodoRegistro* nodo = remover(lista);
    insertar(arregloListas[nodo->reg.tiempoEspera / 10], nodo);
  }

  for (int i=0; i<10; i++) {
    while (arregloListas[i].n > 0) {
      NodoRegistro* nodo = remover(arregloListas[i]);
      insertar(lista, nodo);
    }
  }
}



int main() {

  char* nombreArchivo = "datos.csv";
  Lista lista;
  
  cargarDatosLista(nombreArchivo, lista);
  imprime(lista);
  
  ordenarLista(lista);
  imprime(lista);

  return 0;
}
