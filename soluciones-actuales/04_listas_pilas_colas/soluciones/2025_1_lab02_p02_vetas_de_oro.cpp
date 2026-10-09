#include <iostream>

using namespace std;

const int MAX = 20;

// Convención usada en la matriz:
// 0  -> espacio vacío
// 1  -> inicio de veta de oro
// -1 -> roca

// Direcciones posibles
const int ARRIBA = 0;
const int ABAJO = 1;
const int IZQUIERDA = 2;
const int DERECHA = 3;


// ---------------------------------------------------------
// Función recursiva única.
//
// modo = 0 -> mueve la sonda
// modo = 1 -> busca una veta en línea recta
//
// La misma función se usa para ambas tareas para cumplir
// con la restricción de "una sola función recursiva".
// ---------------------------------------------------------
void recorrer(
    int mina[][MAX],
    int n,
    int m,
    int fila,
    int columna,
    int df,
    int dc,
    int combustible,
    int modo,
    bool posicionInicial
) {

    // =====================================================
    // MODO 1: BÚSQUEDA DE ORO EN UNA DIRECCIÓN
    // =====================================================
    if (modo == 1) {

        // Caso base:
        // si salimos de la matriz, terminamos.
        if (fila < 0 || fila >= n ||
            columna < 0 || columna >= m) {
            return;
        }

        // Si encontramos una roca,
        // no podemos seguir buscando por esa línea.
        if (mina[fila][columna] == -1) {
            return;
        }

        // Si encontramos oro,
        // imprimimos el inicio de la veta.
        if (mina[fila][columna] == 1) {

            cout << "Oro: "
                 << fila << " "
                 << columna << endl;

            return;
        }

        // Si está vacío, seguimos buscando
        // en la misma dirección.
            (
            mina,
            n,
            m,
            fila + df,
            columna + dc,
            df,
            dc,
            combustible,
            1,
            false
        );

        return;
    }



    // =====================================================
    // MODO 0: MOVIMIENTO DE LA SONDA
    // =====================================================

    // -----------------------------------------------------
    // Mientras la sonda se desplaza horizontalmente,
    // busca oro verticalmente.
    // -----------------------------------------------------
    if (dc != 0) {

        // Buscar hacia arriba.
        recorrer(
            mina,
            n,
            m,
            fila - 1,
            columna,
            -1,
            0,
            combustible,
            1,
            false
        );

        // Buscar hacia abajo.
        recorrer(
            mina,
            n,
            m,
            fila + 1,
            columna,
            1,
            0,
            combustible,
            1,
            false
        );
    }

    // -----------------------------------------------------
    // Mientras la sonda se desplaza verticalmente,
    // busca oro horizontalmente.
    // -----------------------------------------------------
    else {

        // Buscar hacia la izquierda.
        recorrer(
            mina,
            n,
            m,
            fila,
            columna - 1,
            0,
            -1,
            combustible,
            1,
            false
        );

        // Buscar hacia la derecha.
        recorrer(
            mina,
            n,
            m,
            fila,
            columna + 1,
            0,
            1,
            combustible,
            1,
            false
        );
    }



    // -----------------------------------------------------
    // En la posición inicial también revisamos hacia atrás
    // respecto de la dirección inicial.
    //
    // Esto permite detectar, por ejemplo:
    //
    //     Oro: 3 0
    //
    // cuando la sonda comienza en (3,2)
    // moviéndose hacia la derecha.
    // -----------------------------------------------------
    if (posicionInicial) {

        recorrer(
            mina,
            n,
            m,
            fila - df,
            columna - dc,
            -df,
            -dc,
            combustible,
            1,
            false
        );
    }



    // -----------------------------------------------------
    // Sin combustible ya no puede desplazarse.
    // -----------------------------------------------------
    if (combustible == 0) {
        return;
    }



    // Calculamos la próxima posición.
    int siguienteFila = fila + df;
    int siguienteColumna = columna + dc;



    // -----------------------------------------------------
    // Si intenta salir de la matriz, termina.
    // -----------------------------------------------------
    if (siguienteFila < 0 || siguienteFila >= n ||
        siguienteColumna < 0 || siguienteColumna >= m) {
        return;
    }



    // =====================================================
    // CASO: ENCUENTRA UNA ROCA
    // =====================================================
    if (mina[siguienteFila][siguienteColumna] == -1) {

        // Llegar a la roca consume una unidad.
        //
        // Si solo quedaba una unidad,
        // llega a la roca pero ya no puede regresar.
        if (combustible == 1) {
            return;
        }

        // El enunciado indica que llegar y salir
        // de la roca consume combustible.
        //
        // Por eso restamos 2:
        //
        // 1 por llegar
        // 1 por salir
        //
        // Además invertimos la dirección.
        recorrer(
            mina,
            n,
            m,
            fila,
            columna,
            -df,
            -dc,
            combustible - 2,
            0,
            false
        );

        return;
    }



    // =====================================================
    // MOVIMIENTO NORMAL
    // =====================================================
    recorrer(
        mina,
        n,
        m,
        siguienteFila,
        siguienteColumna,
        df,
        dc,
        combustible - 1,
        0,
        false
    );
}


// ---------------------------------------------------------
// Convierte una dirección en desplazamiento de fila/columna.
// Esta función NO es recursiva.
// ---------------------------------------------------------
void obtenerDireccion(int direccion, int &df, int &dc) {

    if (direccion == ARRIBA) {
        df = -1;
        dc = 0;
    }
    else if (direccion == ABAJO) {
        df = 1;
        dc = 0;
    }
    else if (direccion == IZQUIERDA) {
        df = 0;
        dc = -1;
    }
    else { // DERECHA
        df = 0;
        dc = 1;
    }
}


int main() {

    int n = 6;
    int m = 7;

    // Matriz basada en el ejemplo del laboratorio.
    //
    // 0  = vacío
    // 1  = veta
    // -1 = roca
    int mina[MAX][MAX] = {

        {0, 1, 1, 1, 1, 1, 1},
        {0, 1, 1, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0},
        {1, 0, 0, 0,-1, 0, 0},
        {1, 1, 0, 0, 0, 0, 0},
        {1, 1, 0, 1, 1, 0, 0}
    };


    // Posición inicial indicada en el enunciado.
    int filaInicial = 3;
    int columnaInicial = 2;


    // En el ejemplo:
    // "Movimiento de la sonda: derecha"
    int direccion = DERECHA;


    // Combustible.
    int C = 4;


    int df, dc;

    obtenerDireccion(direccion, df, dc);


    cout << "Vetas encontradas:" << endl;


    recorrer(
        mina,
        n,
        m,
        filaInicial,
        columnaInicial,
        df,
        dc,
        C,
        0,      // modo movimiento
        true    // posición inicial
    );


    return 0;
}