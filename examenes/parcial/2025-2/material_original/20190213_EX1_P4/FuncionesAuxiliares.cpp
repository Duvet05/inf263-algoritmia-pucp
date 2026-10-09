//
// Created by HP SUPPORT on 18/10/2025.
//

#include "BibliotecaPila/ElementoPila.h"
#include "BibliotecaPila/Pila.h"
#include "BibliotecaPila/funcionesPila.h"
#include "FuncionesAuxiliares.h"

// Función principal: calcula el área máxima del jardín
int maxRectanguloJardin1(int matriz[][4], int n, int m) {

    int alturas[5] = {0}; // Memoria temporal (arreglo unidimensional)
    int maxArea = 0;

    for (int i = 0; i < n; i++) {
        // Actualizar alturas
        for (int j = 0; j < m; j++) {
            if (matriz[i][j] == 0)
                alturas[j] = 0;
            else
                alturas[j]++;
        }

        int areaFila = maxRectanguloHistograma(alturas, m);
        if (areaFila > maxArea)
            maxArea = areaFila;
    }

    return maxArea;

}

// Función principal: calcula el área máxima del jardín
int maxRectanguloJardin2(int matriz[][5], int n, int m) {

    int alturas[5] = {0}; // Memoria temporal (arreglo unidimensional)
    int maxArea = 0;

    for (int i = 0; i < n; i++) {
        // Actualizar alturas
        for (int j = 0; j < m; j++) {
            if (matriz[i][j] == 0)
                alturas[j] = 0;
            else
                alturas[j]++;
        }

        int areaFila = maxRectanguloHistograma(alturas, m);
        if (areaFila > maxArea)
            maxArea = areaFila;
    }

    return maxArea;

}

// Calcula el rectángulo máximo en un histograma usando solo una pila
int maxRectanguloHistograma(int alturas[], int m) {

    Pila pila;
    construir(pila);

    int maxArea = 0;
    int i = 0;

    while (i < m) {
        ElementoPila elem;
        elem.numero = alturas[i];

        // Si la pila está vacía o la altura actual es mayor que la cima, apilamos
        if (esPilaVacia(pila) || alturas[i] >= cima(pila).numero) {
            apilar(pila, elem);
            i++;
        } else {
            // Calculamos área con la barra en la cima
            ElementoPila top = desapilar(pila);
            int altura = top.numero;
            int ancho = esPilaVacia(pila) ? i : i - longitud(pila) - 1;
            int area = altura * ancho;
            if (area > maxArea) maxArea = area;
        }
    }

    // Desapilar el resto
    while (!esPilaVacia(pila)) {
        ElementoPila top = desapilar(pila);
        int altura = top.numero;
        int ancho = esPilaVacia(pila) ? i : i - longitud(pila) - 1;
        int area = altura * ancho;
        if (area > maxArea) maxArea = area;
    }

    destruir(pila);
    return maxArea;

}