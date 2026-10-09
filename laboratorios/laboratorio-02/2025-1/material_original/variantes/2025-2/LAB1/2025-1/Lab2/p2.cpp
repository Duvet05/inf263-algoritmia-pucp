#include <iostream>
#include <fstream>
using namespace std;


void leerArchivo(int **&matriz, int& N, int& M, int& C, int& x, int& y, char& direccion) {
  ifstream archivo("p2.txt");
  if (!archivo.is_open()) {
    cerr << "Error al abrir el archivo." << endl;
    return;
  }

  archivo >> N >> M;

  matriz = new int*[N];

  for (int i = 0; i < N; ++i) {
    matriz[i] = new int[M];

    for (int j = 0; j < M; ++j) {
      archivo >> matriz[i][j];
    }
  }

  archivo >> C;
  archivo >> x >> y;
  archivo >> direccion;

  archivo.close();
}

void imprimirMatriz(int **matriz, int N, int M) {
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      cout << matriz[i][j] << " ";
    }
    cout << endl;
  }
}

void hallarOro(int **matriz, int N, int M, int C, int c_restante, int x, int y, char direccion) {
  // c_restante: Cantidad de movimientos que me quedan

  // Caso base: si c_restante es 0, terminar la búsqueda
  if (c_restante == 0) {
    return;
  }

  // Procesamiento: Buscamos el oro desde la posición actual
  
  // Si estamos en la primera llamada recursiva
  if (C == c_restante) {
    // Buscamos en el eje de la direccion
    if (direccion == 'R' || direccion == 'L') {
      // Busqueda horizontal
      for (int j = y+1; j < M && matriz[x][j] != 2; ++j) {
        if (matriz[x][j] == 0) {
          cout << "Oro encontrado en: (" << x << ", " << j << ")" << endl;
          break;
        }
      }
      for (int j = y-1; j >= 0 && matriz[x][j] != 2; --j) {
        if (matriz[x][j] == 0) {
          cout << "Oro encontrado en: (" << x << ", " << j << ")" << endl;
          break;
        }
      }

    } else if (direccion == 'U' || direccion == 'D') {
      // Busqueda vertical
      for (int i = x+1; i < N && matriz[i][y] != 2; ++i) {
        if (matriz[i][y] == 0) {
          cout << "Oro encontrado en: (" << i << ", " << y << ")" << endl;
          break;
        }
      }
      for (int i = x-1; i >= 0 && matriz[i][y] != 2; --i) {
        if (matriz[i][y] == 0) {
          cout << "Oro encontrado en: (" << i << ", " << y << ")" << endl;
          break;
        }
      }
    }
  }
  
  // Busqueda normal
  if (direccion == 'R' || direccion == 'L') {
    // Busqueda vertical
    for (int i = x+1; i < N && matriz[i][y] != 2; ++i) {
      if (matriz[i][y] == 0) {
        cout << "Oro encontrado en: (" << i << ", " << y << ")" << endl;
        break;
      }
    }
    for (int i = x-1; i >= 0 && matriz[i][y] != 2; --i) {
      if (matriz[i][y] == 0) {
        cout << "Oro encontrado en: (" << i << ", " << y << ")" << endl;
        break;
      }
    }


  } else if (direccion == 'U' || direccion == 'D') {
    // Busqueda horizontal
    for (int j = y+1; j < M && matriz[x][j] != 2; ++j) {
      if (matriz[x][j] == 0) {
        cout << "Oro encontrado en: (" << x << ", " << j << ")" << endl;
        break;
      }
    }
    for (int j = y-1; j >= 0 && matriz[x][j] != 2; --j) {
      if (matriz[x][j] == 0) {
        cout << "Oro encontrado en: (" << x << ", " << j << ")" << endl;
        break;
      }
    }
  }

  cout << endl;

  // Calcular la siguiente posicion
  int x_sig, y_sig;
  if (direccion == 'R') {
    x_sig = x;
    y_sig = y + 1;
  } else if (direccion == 'L') {
    x_sig = x;
    y_sig = y - 1;
  } else if (direccion == 'U') {
    x_sig = x - 1;
    y_sig = y;
  } else if (direccion == 'D') {
    x_sig = x + 1;
    y_sig = y;
  }

  // Verificar si chocamos con una roca
  if (matriz[x_sig][y_sig] == 2) {
    // Cambiar direccion en 180 grados
    if (direccion == 'R') {
      direccion = 'L';
    } else if (direccion == 'D') {
      direccion = 'U';
    } else if (direccion == 'L') {
      direccion = 'R';
    } else if (direccion == 'U') {
      direccion = 'D';
    }
    x_sig = x;
    y_sig = y;
  }

  // llamada recursiva
  hallarOro(matriz, N, M, C, c_restante - 1, x_sig, y_sig, direccion);
}


int main() {

  int N, M;
  int **matriz;
  int C;
  int x, y;
  char direccion;

  leerArchivo(matriz, N, M, C, x, y, direccion);

  imprimirMatriz(matriz, N, M);
  cout << endl;

  hallarOro(matriz, N, M, C, C, x, y, direccion);


  return 0;
}
