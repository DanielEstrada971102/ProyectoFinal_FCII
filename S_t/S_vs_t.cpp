/** ===========================================================================
 * Este codigo corre una simulacion para varios valores de p y guarda un 
 * archivo con las cuentas de los arboles en cada paso de las simulacioines
 *
 * Con el dato del numero de arboles quemados en funcion de tiempo
 * se quiere mostrar la ley de potencias que sigue esta variable
 * 
 * @autors - Daniel Estrada
 *         
 *///===========================================================================
#include "./bosque.h"


int main(int argc, char const *argv[])
{
	srand(time(NULL));

	int L = 1000;
	int k=0;

	Bosque sistema(L, 1);

	for (int p = 45; p <= 55; p = p + 1)
	{
		sistema.cambiar_probabilidad(p/100.0);
		sistema.inicializar_bosque();

		ofstream OutFile("files/S_" + to_string(L) + "_" + to_string(p)+ ".txt");
	
		if (OutFile.fail()){
			cout << "Error: Archivo" << endl;
			exit(0);
		}

		OutFile << right << "#t" << setw(15) << "SANO" ;
		OutFile << setw(15) << "QUEMANDOSE" ;
		OutFile << setw(15) << "QUEMADO" << endl;
		
		k = 0;
		while(sistema.obtener_num_arboles(QUEMANDOSE) != 0){

			OutFile << right << k;
			OutFile << setw(15) << sistema.obtener_num_arboles(SANO);
			OutFile << setw(15) << sistema.obtener_num_arboles(QUEMANDOSE);
			OutFile << setw(15) << sistema.obtener_num_arboles(QUEMADO) << endl;

			sistema.actualizar_estados();
			k++;
		}	

		OutFile << right << k;
		OutFile << setw(15) << sistema.obtener_num_arboles(SANO);
		OutFile << setw(15) << sistema.obtener_num_arboles(QUEMANDOSE);
		OutFile << setw(15) << sistema.obtener_num_arboles(QUEMADO) << endl;	

		OutFile.close();
	
	}
	
	return 0;
}
