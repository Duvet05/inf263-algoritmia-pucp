#include ".\ArbolBinario\BibliotecaArbolBinario\funcionesArbolBinario.h"
#include ".\ArbolBinario\BibliotecaArbolBinario\ArbolBinario.h"
#include <cstring>
#include <iostream>
using namespace std;

bool encontrarSubcadena(const char* cadena, const char* subcadena, int &i) {
  int lenCadena = strlen(cadena);
  int lenSubcadena = strlen(subcadena);

  int iPrev = i;

  for (int j=0; subcadena[j + i] != 0; j++) {

    if (cadena[j + i] != subcadena[j]) {
      i = iPrev; // Restaurar el valor original de i si no coincide
      return false;
    }

  }

  return true; // Subcadena no encontrada
}


void sacaPalabras(const char* instruccionSQL, char **cadenas, int &numCadenas) {

  char delimitador = ' ';

  for (int i = 0; instruccionSQL[i] != '\0'; ) {

    char palabra[100];
    int k = 0;

      // Extraer una palabra hasta el delimitador o el final de la cadena
      while (instruccionSQL[i] != delimitador && instruccionSQL[i] != '\0') {
        palabra[k++] = instruccionSQL[i++];
      }
      palabra[k] = '\0'; // Terminar la cadena de la palabra


    // Almacenar la palabra en el arreglo de cadenas
    cadenas[numCadenas] = new char[k + 1];
    strcpy(cadenas[numCadenas], palabra);
    numCadenas++;

    // Saltar el delimitador
    if (instruccionSQL[i] == delimitador) {
      i++;
    }

  }
  cadenas[numCadenas] = nullptr; // Marcar el final del arreglo de cadenas

}

void reordenarArregloCadenas(char **cadenas, int &numCadenas) {
    /*
    antes:
    [
      "SELECT"  
      "nombre" 
      "FROM" 
      "usuarios"  
      "WHERE" 
      "activo"
      "="
      "1"
      "GROUP BY"
      "edad"
    ]

    despues:
    [
      "SELECT"  
      "nombre" 
      "FROM" 
      "usuarios"  
      "WHERE" 
      "activo = 1"
      "GROUP BY"
      "edad"
    ]

  */


  char cadenasAux[100][100];
  int numCadenasAux = 0;
  bool flag = false;

  for (int i = 0; i < numCadenas; i++) {

    strcpy(cadenasAux[numCadenasAux], cadenas[i]);
    numCadenasAux++;

    if (flag) {
      while (cadenas[i+1] != nullptr && strcmp(cadenas[i+1], "GROUP_BY") != 0 && strcmp(cadenas[i+1], "ORDER_BY") != 0) {
        // Concatenar la siguiente cadena a la actual
        strcat(cadenasAux[numCadenasAux - 1], " ");
        strcat(cadenasAux[numCadenasAux - 1], cadenas[i+1]);
        i++;
      }
      flag = false;
    }

    if (strcmp(cadenas[i], "WHERE") == 0) {
      flag = true;
    }
  }

  // copiar del aux al original
  for (int i = 0; i < numCadenasAux; i++) {
    cadenas[i] = cadenasAux[i];
  }
  numCadenas = numCadenasAux;
}


void crearArbolSQL(ArbolBinario& arbol, const char* instruccionSQL) {


  char *cadenas[100];
  int numCadenas = 0;

  const char* clausulas[] = {"SELECT", "FROM", "WHERE", "GROUP_BY", "ORDER_BY"};
  int numClausulas = 5;

  sacaPalabras(instruccionSQL, (char**)cadenas, numCadenas);
  reordenarArregloCadenas((char**)cadenas, numCadenas);

  // imprimir arreglo cadenas
  for (int i = 0; i < numCadenas; i++) {
    cout << "Cadena " << i << ": " << cadenas[i] << endl;
  }

  NodoArbolBinario* nodoActual = arbol.raiz;

  for (int i = 0; i < numCadenas; i++) {
    cout << "Palabra " << i << ": " << cadenas[i] << endl;

    if (i%2 == 0 && i > 0) {
      nodoActual = nodoActual->derecha;
    }

    ElementoArbolBinario elemento;
    strcpy(elemento.expresion, cadenas[i]);

    if (i%2 == 0) {
      if (strcmp(cadenas[i], clausulas[i/2]) != 0) {
        cout << "Error: La instruccion SQL debe tener la clausula " << clausulas[i/2] << endl;
        return;
      }
      plantarNodoArbolBinario(nodoActual, nullptr, elemento, nullptr);
    }
    else {
      if (strcmp(cadenas[i], clausulas[(i+1)/2]) == 0) {
        cout << "Error: La instruccion SQL debe tener un valor antes de la clausula " << clausulas[(i+1)/2] << endl;
        return;
      }
      plantarNodoArbolBinario(nodoActual->izquierda, nullptr, elemento, nullptr);
    }
  }

  if (numCadenas % 2 != 0) {
    cout << "Error: Instruccion SQL incompleta." << endl;
    return;
  }

  cout << "Consulta valida." << endl;
}

int main() {

  ArbolBinario arbol;
  construir(arbol);

  crearArbolSQL(arbol, "SELECT * FROM usuarios WHERE");

  recorrerEnOrden(arbol);


  return 0;
}

