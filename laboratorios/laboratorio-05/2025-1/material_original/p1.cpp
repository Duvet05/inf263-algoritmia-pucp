#include "./ArbolBinario/ArbolBinario/BibliotecaArbolBinario/funcionesArbolBinario.h"
#include "./ArbolBinario/ArbolBinario/BibliotecaArbolBinario/ArbolBinario.h"
#include <iostream>
#include <cstring>
using namespace std;

const char* determinarCategoria(const char* palabra, const char** articulos, const char** sustantivos, const char** verbos) {
    
    for (int i = 0; articulos[i] != nullptr; ++i) {
        if (strcmp(palabra, articulos[i]) == 0) {
            return "articulo";
        }
    }
    for (int i = 0; sustantivos[i] != nullptr; ++i) {
        if (strcmp(palabra, sustantivos[i]) == 0) {
            return "sustantivo";
        }
    }
    for (int i = 0; verbos[i] != nullptr; ++i) {
        if (strcmp(palabra, verbos[i]) == 0) {
            return "verbo";
        }
    }
    return "desconocida";
}

void separarCadenaEnPalabras(const char* cadena, char palabras[][50], int& cantidadPalabras) {
  
  cantidadPalabras = 0;

  for (int i=0; cadena[i] != '\0'; ) {
    while (cadena[i] == ' ') {
      ++i;
    }
    if (cadena[i] == '\0') {
      break;
    }
    int j = 0;
    while (cadena[i] != ' ' && cadena[i] != '\0') {
      palabras[cantidadPalabras][j++] = cadena[i++];
    }
    palabras[cantidadPalabras][j] = '\0';
    ++cantidadPalabras;
  }


}

void crearArbolGramatical( ArbolBinario& arbol, const char** articulos, const char** sustantivos, const char** verbos, int* ordenes)  {

  char cadena[100];
  cout << "Ingrese la oración a validar: ";
  cin.getline(cadena, 100);


  // separar la cadena en palabras
  char palabras[20][50];
  int cantidadPalabras = 0;
  separarCadenaEnPalabras(cadena, palabras, cantidadPalabras);

  NodoArbolBinario* articuloNodo = nullptr;
  NodoArbolBinario* sustantivoNodo = nullptr;
  NodoArbolBinario* verboNodo = nullptr;

  for (int i = 0; i < cantidadPalabras; ++i) {

    char categoria[20];
    strcpy(categoria, determinarCategoria(palabras[i], articulos, sustantivos, verbos));

    ElementoArbolBinario elemento;
    strcpy(elemento.categoria, categoria);
    strcpy(elemento.palabra, palabras[i]);

    if (strcmp(categoria, "desconocida") == 0) {
      cout << "La palabra '" << palabras[i] << "' no pertenece a ninguna categoría conocida." << endl;
    }
    if (strcmp(categoria, "articulo") == 0) {
      ordenes[0] = i;
      plantarNodoArbolBinario(articuloNodo, nullptr, elemento, nullptr);
    } else if (strcmp(categoria, "sustantivo") == 0) {
      ordenes[1] = i;
      plantarNodoArbolBinario(sustantivoNodo, nullptr, elemento, nullptr);
    } else if (strcmp(categoria, "verbo") == 0) {
      ordenes[2] = i;
      plantarNodoArbolBinario(verboNodo, nullptr, elemento, nullptr);
    }
  }

  NodoArbolBinario* sujetoNodo = nullptr;
  if (articuloNodo != nullptr && sustantivoNodo != nullptr) {
    ElementoArbolBinario sujetoElemento;
    strcpy(sujetoElemento.categoria, "sujeto");
    strcpy(sujetoElemento.palabra, "");

    if (ordenes[0] > ordenes[1]) {
      plantarNodoArbolBinario(sujetoNodo, sustantivoNodo, sujetoElemento, articuloNodo);
    }
    else {
      plantarNodoArbolBinario(sujetoNodo, articuloNodo, sujetoElemento, sustantivoNodo);
    }
    
  }

  NodoArbolBinario* predicadoNodo = nullptr;
  if (verboNodo != nullptr) {
    ElementoArbolBinario predicadoElemento;
    strcpy(predicadoElemento.categoria, "predicado");
    strcpy(predicadoElemento.palabra, "");

    plantarNodoArbolBinario(predicadoNodo, verboNodo, predicadoElemento, nullptr);
  }

  plantarNodoArbolBinario(arbol.raiz, sujetoNodo, ElementoArbolBinario{"oracion", ""}, predicadoNodo);
}

bool validarArbolGramatical(ArbolBinario& arbol, int* ordenes) {

  if (ordenes[0] < ordenes[1] && ordenes[1] < ordenes[2]) {
    cout << "Arbol valido" << endl;
    return true;
  } else {
    cout << "Arbol invalido" << endl;

    if (!(ordenes[0] < ordenes[1])) {
      cout << "Error: El artículo debe preceder al sustantivo." << endl;
    }
    if (!(ordenes[1] < ordenes[2])) {
      cout << "Error: El sustantivo debe preceder al verbo." << endl;
    }

  }
  return false;
}

int main() {

  const char* articulos[] = {"el", "la", "los", "las", "un", nullptr}; 
  const char* sustantivos[] = {"gato", "perro", "casa", "mesa", "silla", nullptr}; 
  const char* verbos[] = {"come", "salta", "duerme", nullptr}; 

  ArbolBinario arbol;
  construir(arbol);

  int ordenes[3] = {0, 0, 0};

  crearArbolGramatical(arbol, articulos, sustantivos, verbos, ordenes);

  if (validarArbolGramatical(arbol, ordenes)) {
    cout << "\nRecorrido en orden del árbol gramatical:\n";
    recorrerEnOrden(arbol);
    cout << endl;
  }

  return 0;
}
