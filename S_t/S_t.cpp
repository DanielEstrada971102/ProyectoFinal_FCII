/** ===========================================================================
 * Este codigo genera los datos para la grafica del parametro de orden 
 * t contra el la probabilidad de propagacion, por cada p se hacen k_max 
 * corridas de una red de tamaño LxL
 * 
 * @autors - Johan Carrillo Toro
 *         
 *///===========================================================================
#include "./bosque.h"

double S_prom(vector < int >, int);  // funcion que calcula el promedio

int main(){

	int L = 501;
	double p;
	int k, k_max =25;
	vector < int > S_array(k_max, 0);  // guarda el # total de quemados
	ofstream OutFile("S_tiempo" + to_string(L) + ".txt");
	
	// se comprueba la correcta apertura del archivo
	if (OutFile.fail()){
		cout << "Error: Archivo" << endl;
		exit(0);
	}

	for (p = 0.0; p <= 1.0 ; p = p + 0.02){

		cout << "calculando para p = " << p << endl;
		k=0;

		Bosque sistema(L, p);  // creacion del bosque

		while(k < k_max){
			sistema.propagar();  // se evoluciona el sistema
			S_array[k] =  sistema.obtener_tiempo();  // se obtiene el tiempo de actividad
			sistema.inicializar_bosque();  // se reinicia el sistema
			k++;
		}

		OutFile << S_prom(S_array, k_max) << endl;  // se guarda el promedio de tiempo
	}

	OutFile.close();

	return 0;
}

double S_prom(vector < int > array, int n){
	// esta funcion calcula el promedio usando las componentes de un arreglo

	double S=0;

	for (int i = 0; i < n; i++){
		S += array[i];
	}

	return S / double(n);
}