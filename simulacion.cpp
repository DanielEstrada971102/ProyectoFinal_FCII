/** ===========================================================================
 * Este codigo simula la propagacion de un incendio forestal 
 * en una red cuadrada de lado L con probabilidad de propagacion
 * p, los archivos generados se guardan en la ruta por defecto
 * 
 * @autors - Johan Carrillo Toro
 *         - Lina Maria Montoya
 *         - Valentina Bedoya
 *         - Daniel Estrada
 *         
 *///===========================================================================

#include "bosque.h"

int main(int argc, char const *argv[]){

	srand(time(NULL)); ///< importante iniciar la semilla
	int L = stoi(argv[1]);
	double p = stof(argv[2]);
	Bosque miniBosque( L, p);  ///< inicializa la red de arboles

	if (argv[3]!=NULL){ // se pasa la ruta de salida para los datos
		string out_path = argv[3];
		out_path = "data/" + out_path;
		
		/// se crean las carpetas para guardar los archivos
		string command = "mkdir " + out_path;
		system(command.c_str());
		command = "mkdir " + out_path + "/files "+ out_path + "/images";
		system(command.c_str());
		
		miniBosque.propagar(true, out_path + "/files/", out_path + "/images/");		
	}
	else{
		miniBosque.propagar(true); ///< se guardan en el path por defecto
	}

	return 0;
}
