/** ===========================================================================
 * Este codigo corre kmax simulaciones de una red de tamaño LxL para cada 
 * valor de p entre 0 y 1 cada 0.01, con eso se hace un promedio del numero
 * de arboles quemados en funcion de p
 * 
 * @autors - Daniel Estrada
 *         
 *///===========================================================================

#include "../bosque.h"

double prom(int*, int);

int main(int argc, char const *argv[])
{
	srand(time(NULL));

	int L = 1000;
	double p;
	int k, kmax=50;
	int S_array[kmax];
		
	ofstream OutFile("Sp_" + to_string(L) + ".txt");
	
	if (OutFile.fail()){
		cout << "Error: Archivo" << endl;
		exit(0);
	}

	OutFile << right << "#p" << setw(15) <<  "s" << endl;

	for (p = 0; p <= 1.0 ; p = p + 0.01){
		cout << "calculando para p = " << p << endl;
		Bosque sistema(L,p);

		for (k = 0; k < kmax; k++){
				
			sistema.propagar();
			S_array[k] =  sistema.obtener_num_arboles(QUEMADO);
			sistema.inicializar_bosque();
		}

		OutFile << right << p << setw(15) <<  prom(S_array, kmax) <<endl;
	}

	OutFile.close();

	return 0;
}

double prom(int *array, int n){
	double S=0;

	for (int i = 0; i < n; i++){
		S += array[i];
	}

	return S / n;
}