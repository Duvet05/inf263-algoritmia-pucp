#include "./Cola/BibliotecaCola/Cola.h"
#include "./Cola/BibliotecaCola/funcionesCola.h"
#include <iostream>
#include <fstream>
using namespace std;

struct ColaPrioridad {
  Cola vip;
  Cola regular;
};


void atenderCliente(ColaPrioridad &colaPrioridad, int tiempoRestante, ElementoCola &clienteAtendido) {

  if (tiempoRestante < 0) {
    int codigoVip = colaPrioridad.vip.inicio->elemento.codigo;
    int codigoRegular = colaPrioridad.regular.inicio->elemento.codigo;

    if (codigoVip < codigoRegular) {
      clienteAtendido = desencolar(colaPrioridad.vip);
    } else {
      clienteAtendido = desencolar(colaPrioridad.regular);
    }

    return;
  }

  if (!esColaVacia(colaPrioridad.vip)) {
    clienteAtendido = desencolar(colaPrioridad.vip);

  } else if (!esColaVacia(colaPrioridad.regular)) {
    clienteAtendido = desencolar(colaPrioridad.regular);

  } 

}

void insertarCliente(ColaPrioridad &colaPrioridad, int codigo, int tiempoLlegada, bool esVip, int &t, ElementoCola &clienteAtendido, int& cantidadVipNoAtendidos) {


  cout << "Insertando cliente codigo: " << codigo << ", tiempoLlegada: " << tiempoLlegada << ", esVip: " << esVip << endl;

  // Crear el cliente
  ElementoCola cliente;
  cliente.codigo = codigo;
  cliente.tiempoLlegada = tiempoLlegada;
  cliente.tiempoRestante = 20; // Supongamos que cada cliente tarda 20 segundos en ser atendido

  if (esVip) {
    encolar(colaPrioridad.vip, cliente);
  } else {
    encolar(colaPrioridad.regular, cliente);
  }
  
  cout << "--------------------------------------------------" << endl;
  imprimir(colaPrioridad.vip);
  imprimir(colaPrioridad.regular);


  // Atender cliente
  if (clienteAtendido.tiempoRestante == -1) {
    atenderCliente(colaPrioridad, 0, clienteAtendido);
  }
  else {
    int tiempoPaso = (tiempoLlegada - t);

    clienteAtendido.tiempoRestante -= tiempoPaso;

    if (clienteAtendido.tiempoRestante <= 0) {
      int tiempoExtra = -clienteAtendido.tiempoRestante;
      atenderCliente(colaPrioridad, clienteAtendido.tiempoRestante, clienteAtendido);
      clienteAtendido.tiempoRestante -= tiempoExtra;
    }
    // calcular cuanto tiempo tiene que esperar el cliente vip
    if (esVip) {
      if (clienteAtendido.tiempoRestante > 30) {
        
        cantidadVipNoAtendidos++;

      }
    }

  }
  
  
  
  
  t = tiempoLlegada;


  cout << "--------------------------------------------------" << endl;
  imprimir(colaPrioridad.vip);
  imprimir(colaPrioridad.regular);


}

int main() {

  ColaPrioridad colaPrioridad;
  construir(colaPrioridad.vip);
  construir(colaPrioridad.regular);

  int t = 0;
  ElementoCola clienteAtendido;
  clienteAtendido.tiempoRestante = -1; // Indica que no hay cliente siendo atendido

  int cantidadVipNoAtendidos = 0;

  insertarCliente(colaPrioridad, 1, 15, false, t, clienteAtendido, cantidadVipNoAtendidos);


  insertarCliente(colaPrioridad, 2, 30, true, t, clienteAtendido, cantidadVipNoAtendidos);


  insertarCliente(colaPrioridad, 3, 45, false, t, clienteAtendido, cantidadVipNoAtendidos);


  insertarCliente(colaPrioridad, 4, 60, true, t, clienteAtendido, cantidadVipNoAtendidos);


  insertarCliente(colaPrioridad, 5, 75, false, t, clienteAtendido, cantidadVipNoAtendidos);


  insertarCliente(colaPrioridad, 6, 90, true, t, clienteAtendido, cantidadVipNoAtendidos);


  cout << "Cantidad de clientes VIP atendidos: " << 3 - cantidadVipNoAtendidos << endl;
  cout << "Cantidad de clientes VIP que no fueron atendidos en menos de 30 segundos: " << cantidadVipNoAtendidos << endl;

  return 0;
}



