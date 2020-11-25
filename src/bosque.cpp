/** ===========================================================================
 * En este codigo de encuentran implementoados 
 * los metodos de la clase Bosque
 *
 * @autors - Johan Carrillo Toro
 *         - Lina Maria Montoya
 *         - Valentina Bedoya
 *         - Daniel Estrada
 *         
 *///===========================================================================


#include "bosque.h"

//------------------------------------------------------------------------------
Bosque::Bosque(int L_, double p_){  
	/**
	 * Constructor de la clase
	 *
	 * @param L_ Dimensiones del bosque (matriz cuadrada)
	 * @param p_ Probabilidad de propagacion del fuego.
	 */

	cambiar_tamanio(L_); ///<inicializacion de L
	cambiar_probabilidad(p_); ///< inicializacion de p
	
	inicializar_bosque(); ///< inicialiacion del sistema 
						  ///< con los parametros establecidos
}


Bosque::~Bosque(){
	/**
	 * Destructor de la clase
	 */
	
	cout << "\nEliminando el bosque" << endl;
}
//------------------------------------------------------------------------------
//
//----------------------Metodos para simulacion---------------------------------


void Bosque::inicializar_bosque(){
	/**
	 * Inicializa el bosque, crea una matriz de arboles en estado SANO excepto
	 * el del centro que inicia en estado QUEMANDOSE y se configurar las 
	 * condiciones iniciales del sistema. 
	 */

	int k=0; ///< ID
	
	//se redimensiona el vector con dimension LxL
	elementos.resize(L, vector<Arbol>(L));

	for (int i = 0; i < L; i++){
		for (int j = 0; j < L; j++){

			///se asigna la posicion a cada arbol del sistema
			elementos[i][j].pos_x = i;
			elementos[i][j].pos_y = j;

			///si es el arbol del centro inicial quemandose
			if (i ==  int(L/2) && j ==  int(L/2)) 
				elementos[i][j].estado = QUEMANDOSE;
			
			else
				elementos[i][j].estado = SANO;

			elementos[i][j].id = k; ///se asigna el ID
			k++;

			///se asignan los vecinos correspondientes
			calcular_primeros_vecinos(i, j); 
		}
	}

	//----------- inicializacion de contadores de arboles ---------------------
	num_activos = 1;  ///< al principio solo se esta quemando un arbol
	num_quemados = 0;  ///< no hay ningun arbol quemado
	num_vivos = L*L - 1;  ///< todos estan vivos menos el del medio

}



void Bosque::calcular_primeros_vecinos(int i, int j){
	/**
	 * Asignador de vecinos, segun la posicion en el arreglo se asignan como 
	 * vecinos los apuntadores de los elementos contiguos (primeros vecinos). 
	 *
	 * @param i fila
	 * @param j columna
	 */

	Arbol *vecino_l, *vecino_r, *vecino_t, *vecino_b;

	//========== elementos de las esquinas ==========
	if (i == 0 and j == 0){
		vecino_l = NULL;
		vecino_r = &elementos[i][j+1];
		vecino_t = NULL;
		vecino_b = &elementos[i+1][j];
	}

	else if( i == L-1 and j == L-1 ){
		vecino_l = &elementos[i][j-1];
		vecino_r = NULL;
		vecino_t = &elementos[i-1][j];
		vecino_b = NULL;
	}

	else if( i == 0 and j == L-1 ){
		vecino_l = &elementos[i][j-1];
		vecino_r = NULL;
		vecino_t = NULL;
		vecino_b = &elementos[i+1][j];
	}

	else if( i == L-1 and j == 0 ){
		vecino_l = NULL;
		vecino_r = &elementos[i][j+1];
		vecino_t = &elementos[i-1][j];
		vecino_b = NULL;
	}

	//============= primera fila ====================
	else if( i == 0 ){
		vecino_l = &elementos[i][j-1];
		vecino_r = &elementos[i][j+1];
		vecino_t = NULL;
		vecino_b = &elementos[i+1][j];
	}

	//============= ultima fila =====================
	else if( i == L-1 ){
		vecino_l = &elementos[i][j-1];
		vecino_r = &elementos[i][j+1];
		vecino_t = &elementos[i-1][j];
		vecino_b = NULL;
	}

	//=========== primera columna ===================
	else if( j == 0 ){
		vecino_l = NULL;
		vecino_r = &elementos[i][j+1];
		vecino_t = &elementos[i-1][j];
		vecino_b = &elementos[i+1][j];
	}

	//=========== ultima columna ====================
	else if( j == L-1 ){
		vecino_l = &elementos[i][j-1];
		vecino_r = NULL;
		vecino_t = &elementos[i-1][j];
		vecino_b = &elementos[i+1][j];
	}

	//== ======== demas elementos ===================
	else{
		vecino_l = &elementos[i][j-1];
		vecino_r = &elementos[i][j+1];
		vecino_t = &elementos[i-1][j];
		vecino_b = &elementos[i+1][j];	
	}

	/// asignacion de vecinos
	elementos[i][j].vecinos.push_back(vecino_l);
	elementos[i][j].vecinos.push_back(vecino_t);
	elementos[i][j].vecinos.push_back(vecino_r);
	elementos[i][j].vecinos.push_back(vecino_b);
	
}


void Bosque::actualizar_estados(){
	/**
	 * Evoluciona un paso de la simulacion, se recorre la matriz y se 
	 * ejecuta el algoritmo de propagacion del modelo cuando se encuentre un
	 * arbol en estado QUEMANDOSE.
	 */

	double dado=0; 
	int estado_actual[L][L];  ///< copia auxiliar del estado actual del sistema

	/// se crea una copia del estado actual del sistema
	for (int i = 0; i < L; i++){
		for (int j = 0; j < L; j++)
			estado_actual[i][j] = elementos[i][j].estado;
	}


	for(int i=0; i<L; i++){
		for(int j=0; j<L; j++){

			/// si se esta quemando puede propagar el fuego a los vecinos
			if( estado_actual[i][j] == QUEMANDOSE ){

				for(int k=0; k<4; k++) ///< ciclo sobre los vecinos
				{
					/// si el vecino existe y es suceptible a quemarse
					if( elementos[i][j].vecinos[k] != NULL and 
						elementos[i][j].vecinos[k]->estado == SANO)
					{

						dado = (double) rand() / (RAND_MAX);

						if(  dado <= p )///< Cambio de estado segun la probabilidad
						{
							elementos[i][j].vecinos[k]->estado = QUEMANDOSE;
							
							/// actualiza los contadores por el cambio
							num_activos++;
							num_vivos--; 
						}
					}

				} 

				/// actualiza los contadores por el paso de la simulacion, el 
				/// que se estaba quemando pasa a ser quemado
				elementos[i][j].estado = QUEMADO;
				num_activos--;
				num_quemados++;
			}
		}
	}

}


void Bosque::propagar(bool save, string pathName, string ImagesPathName){
	/**
	 * Simulacion, evoliciona el sistema hasta que se extiga el fuego. permite 
	 * guardar la informacion de cada paso de tiempo para visualizar la evolucion
	 *
	 * @param save booleano que indica si se desean guardar los datos
	 * @param pathName ruta para almacenar los archivos de datos generados,
	 *        valor por defecto -> "./data/prueba/files/"
	 * @param ImagesPathName ruta para guardar un archivo que contiene los nombres
	 *        de las imagenes que se generan para cada paso de la simulacion, 
	 *        esto se usa para la generación de un gif del sistema,
	 *        valor por defecto -> "./data/prueba/images/"
	 */


	t_fuego = 0; ///< inicio de la simulacion -> paso = 0
	inicializar_bosque(); ///< reinicio a la configuracion inicial del sistema


	if(save) ///< si se desea guardar los datos
	{
		/// archivo de estado inicial
		escribir_archivo(pathName + "step_" + to_string(t_fuego) + ".dat", 
						ImagesPathName + "step_" + to_string(t_fuego) + ".png");

		/// La simulacion corre mientras existan arboles en estado QUEMANDOSE
		while( num_activos != 0 ){ 
			actualizar_estados();  
			t_fuego++;
			/// archivo de estado en cada paso de la simualcion
			escribir_archivo(pathName + "step_" + to_string(t_fuego) + ".dat",
							ImagesPathName + "step_" + to_string(t_fuego) + ".png");
		}	
	}

	else /// si solo se desea correr la simualcion si generar los archivos
	{
		while( num_activos != 0 ){
			actualizar_estados();
			t_fuego++;
		}	
	}

}
//------------------------------------------------------------------------------
//
//-------------------- Metodos "setter" y "getter" -----------------------------


int Bosque::obtener_num_arboles(int state) const{
	/**
	 * Obtener el numero de arboles en ciero estado
	 *
	 * @param state tipo de contador que se quiere consultar
	 * @return cuentas de arboles en el estado solicitado
	 */

	if (state == SANO)
		return num_vivos;
	
	else if (state == QUEMANDOSE)
		return num_activos;

	else if (state == QUEMADO)
		return num_quemados;
	
	else
		return 0;

}

int Bosque::obtener_tiempo() const{
	/**
	 * Obtener el paso actual en el proceso de simulacion
	 *
	 * @return numero de paso actual en la simulacion
	 */

	return t_fuego;
}

void Bosque::cambiar_tamanio(int L_){
	/**
	 * Cambiar tamaño de la red de arboles
	 *
	 * @param L_ Dimensiones del bosque (matriz cuadrada)
	 */
	if (L_ <= 0){
		cout << "Debe ingresar un numero entre  mayor que cero";
		cout << "establecido a 10x10 por defecto" << endl;
		L = 10;
	}

	else
		L = L_;

}

void Bosque::cambiar_probabilidad(double p_){
	/**
	 * Cambiar la probabilidad de propagacion del fuego
	 *
	 * @param p_ Probabilidad de propagacion del fuego.
	 */
	
	if( p<=1 || p>=0 ) 
		p = p_;  ///< p es una probabilidad
	
	else{ 
		cout << "Debe ingresar un numero entre 0 y 1 ";
		cout << "establecido a 0.45 por defecto" << endl;
		p = 0.45;
	}
}

//------------------------------------------------------------------------------
//
//------------------------- Metodos auxiliares ---------------------------------


void Bosque::escribir_archivo(string fileName, string Imagen){
	/**
	 * Escribe un archivo con la informacion del sistema en el paso de simulacion
	 * actual, la informacion incluida es (#id, posx, posy, estado) para cada 
	 *
	 * @param fileName nombre del archivo a generar
	 * @param 
	 */

	ofstream Out_DataFile(fileName);
	ofstream Out_ImagesName;

	Out_ImagesName.open("lista_imagenes.txt", ios::app);

	/// se comprueba que los archivos abrieron bien
	if (Out_DataFile.fail()){
		cout << "Error: Archivo de datos" << endl;
		exit(0);
	}

	if (Out_ImagesName.fail()){
		cout << "Error: Archivo de imagenes" << endl;
		exit(0);
	}

	/// se añade nombre de la imagen que corresponde a este archivo de datos a una 
	/// lista de nombres que se usan para crear un gif al final de la simulacion
	Out_ImagesName << right << Imagen << endl; 

	/// encabezado del archivo de datos
	Out_DataFile << right << "#id"; 
	Out_DataFile << setw(10) << "posx";
	Out_DataFile << setw(10) << "posy";
	Out_DataFile << setw(10) << "estado" << endl; 
	
	for (int i = 0; i < L; i++){
		for (int j = 0; j < L; j++){
			/// informacion actual de cada arbol
			Out_DataFile << right << elementos[i][j].id << setw(10);
			Out_DataFile << elementos[i][j].pos_x << setw(10);
			Out_DataFile << elementos[i][j].pos_y << setw(10);
			Out_DataFile << elementos[i][j].estado << endl;
		}
		
	}

	/// se cierran los archivos
	Out_DataFile.close();
	Out_ImagesName.close();

}
