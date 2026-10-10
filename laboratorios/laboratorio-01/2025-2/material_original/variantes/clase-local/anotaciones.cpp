
1. el robot tiene que moverse
2. la condicion inicial debe usar recursion, porque tiene que evaluar donde va a empezar
3. se que voy a pasar las coordenadas y debo guardar el numero de soluciones posibles, de la misma manera me piden imprimir la solucion!
4. la condicion para moverme ya la condicion, pueden haber rocas pero no complican
5. lo complicado es la galerias que se apilan, esta apilacion debe ser considerada por mi recursion

---
x=0
y=0
total_de_soluciones=0

//como este borrador que he hecho permite que como minimo llege de la izq (0,m-1) a la derecha (n-1,y) 
// como se que mi solucion es valida?
// 0 = no llego todavia a su final valido
// 1 = llego a su final
// 2 = tiene error, no considerar este camino
int perforarGalerias(matriz,n,m,x,y,numero_solicion,total_de_soluciones,estoy_buscando_inicio){
    matriz,

    if (buscarInicio) {

        if (fila < 0) {
                return false;
        }

                    // Una roca o galeria previa ocupa este punto de partida.
        if (mina[fila][0] != 0) {
                return perforarGalerias(mina, n, m, fila - 1, 0,
                                        numeroGaleria, totalGalerias, true);
            }


        // Se intenta construir una galeria desde la celda libre actual.
        if (perforarGalerias(mina, n, m, fila, 0,
                             numeroGaleria, totalGalerias, false)) {
            return true;
            }

        // Si no llega al lado derecho, se prueba la siguiente fila superior.
            return perforarGalerias(mina, n, m, fila - 1, 0,
                                numeroGaleria, totalGalerias, true);
    }


    //si me salgo, vuelvo atras, se me encuentro con piedra, vuelvo atras
    if (fila < 0 || fila >= n || columna < 0 || columna >= m ||mina[fila][columna] != 0) {
        return false;
    }

    //ya llegue a la derecha! ya funciona tu solucion
    if (columna == m - 1) {
        totalGalerias = numero_solicion;

        // Se buscan mas galerias sin borrar la que acaba de completarse.
        perforarGalerias(mina, n, m, n - 1, 0,
                         numeroGaleria + 1, totalGalerias, true);
        return true;
    }

    //soy optimista y digo sin sabe: este camino es valido, la recursion me dira lo contrario
    mina[fila][columna] = 1;

    if(perforarGalerias(matriz,n,m,x+1,y,total_de_soluciones)) por aca puede ser
    if(perforarGalerias(matriz,n,m,x,y+1,total_de_soluciones)) por aca puede ser
    if(perforarGalerias(matriz,n,m,x,y-1,total_de_soluciones)) por aca puede ser

     // El camino no llego al lado derecho; se deshace para probar otro. 
    mina[fila][columna] = 0;
    return false;

}



---
1 -> 2,3,4
