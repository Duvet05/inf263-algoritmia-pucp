#ifndef LISTAS_FUNCIONES_LISTA_H
#define LISTAS_FUNCIONES_LISTA_H

#include <iostream>
#include "Estructuras.h"

namespace listas {

// Usar solo en una lista nueva o ya destruida. Para vaciar, usar destruir.
void inicializar(Lista &lista);
bool esListaVacia(const Lista &lista);
int longitud(const Lista &lista);

// Estas funciones reservan un nodo nuevo.
void insertarInicio(Lista &lista, const Elemento &dato);
void insertarFinal(Lista &lista, const Elemento &dato);
// Posiciones desde 0. Para insertar, tambien se admite lista.longitud.
bool insertarEnPosicion(Lista &lista, int posicion, const Elemento &dato);

// Consultas: nullptr si no se encuentra el dato o la posicion no existe.
const Nodo *buscar(const Lista &lista, const Elemento &dato);
const Nodo *obtenerEnPosicion(const Lista &lista, int posicion);

// Extraer desconecta el nodo, SIN borrarlo; nullptr si no existe.
// Quien lo recibe debe reinsertarlo o liberarlo con delete.
Nodo *extraerInicio(Lista &lista);
Nodo *extraerEnPosicion(Lista &lista, int posicion);

// Reutilizan un nodo extraido, sin new. nullptr no hace nada.
// Precondicion: el nodo esta aislado y no pertenece a ninguna lista.
void insertarNodoInicio(Lista &lista, Nodo *nodo);
void insertarNodoFinal(Lista &lista, Nodo *nodo);

// Eliminar desconecta y hace delete. Retorna false si no hay nada que borrar.
bool eliminarInicio(Lista &lista);
bool eliminarFinal(Lista &lista);
bool eliminarEnPosicion(Lista &lista, int posicion);
bool eliminarDato(Lista &lista, const Elemento &dato); // Primera coincidencia.

// Transfiere todos los nodos al final de destino y deja origen vacia.
// Concatenar una lista consigo misma no hace nada.
void concatenar(Lista &destino, Lista &origen);
void invertir(Lista &lista);
void imprimir(const Lista &lista, std::ostream &salida = std::cout);
void destruir(Lista &lista);

} // namespace listas

#endif
