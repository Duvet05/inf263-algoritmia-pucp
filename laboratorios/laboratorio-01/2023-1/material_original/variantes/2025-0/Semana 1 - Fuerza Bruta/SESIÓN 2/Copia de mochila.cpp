#include <iostream>
#include <cmath>
using namespace std;
#define MAX 4

void cargabin(int num, int* cromo) {
	
	for(int j=0; j<MAX; j++)
		cromo[j] = 0;
	
	for (int i=0; num>0; i++) {
		int res = num%2;
		num = num/2;
		cromo[i] = res;
	} 
}


int main() {
	
	int art[] = {1, 2, 10, 4};
	
	int peso = 15; // capacidad de la mochila
	
	// mpeso es el maximo peso que puedo colocar en la mochila sin sobrepasar la capacidad
	int mcomb=0, mpeso=0, flag=0;

	int cromo[MAX];
	int comb = pow(2, MAX);
	
	for(int i=0; i<comb; i++) {

		cargabin(i,cromo);
		int parcial=0; // es la suma de los articulos seleccionados
		
		for(int j=0; j<MAX; j++)
			if(cromo[j] == 1)
				parcial += art[j];
		
		if(parcial <= peso && mpeso <= parcial) {
			mpeso = parcial;
			mcomb = i;
			if(mpeso == peso)
				flag=1;
		}
		if(flag)
			break;
	}
	cout << "El maximo peso que puede cargar la mochila es: " << mpeso << endl;
	cout << "Los articulos son: ";
	cargabin(mcomb,cromo);
	for(int j=0; j<MAX; j++){
		if (cromo[j] == 1)
			cout << art[j] << " ";
	}
	
	return 0;
}