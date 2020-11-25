/** ===========================================================================
 * En este codigo de encuentra la definicion de la clase Bosque 
 *
 * @autors - Johan Carrillo Toro
 *         - Lina Maria Montoya
 *         - Valentina Bedoya
 *         - Daniel Estrada
 *         
 *///===========================================================================

#ifndef ARBOL_H
#define ARBOL_H

//========================= posibles estados ==================================

#define SANO 1
#define QUEMADO 0 
#define QUEMANDOSE 2

//==============================================================================
//----------------------------Librerias-----------------------------------------
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;
//------------------------------------------------------------------------------
//---------------------- Estructura de datos "Arbol" ---------------------------
typedef struct Arbol Arbol;

struct Arbol
{
	int id;  // identificador
	int estado;  // estado
	vector < Arbol* > vecinos;	// apuntadores a los vecinos
	int pos_x;  // posicion x del arbol en el bosque
	int pos_y;  // posicion y del arbol en el bosque
};

//------------------------------------------------------------------------------
//----------------------------- Clase Bosque -----------------------------------
class Bosque{
	/**
	 * Esta clase representa un arreglo de arboles para simular la propagacion
	 * de un incendio con un modelo de percolacion dinamico en una red cuadrada
	 * LxL con umbral de probabilidad p.
	 *
	 * @public
	 * |---> @method[void] Bosque(int, double) contructor de la clase
	 * |---> @method[void] ~Bosque() destructor de la clase
	 * |---> @method[int] obtener_num_arboles(int) retorna el numero de arboles 
	 * |			      en un estado especifico
	 * |---> @method[int] obtener_timepo() retorna el numero de pasos actual
	 * | 				  en la simulacion de la propagacion  
	 * |---> @method[void] cambiar_tamanio(int) cambia el atributo privado L
	 * |---> @method[void] cambiar_probabilidad(int) cambia el atributo privado 
	 * |---> @method[void] inicializar_bosque() establece los elemntos de la 
	 * |				   variable privada elementos y sus propiedade, tambien,
	 * |				   reinicia los contadores.
	 * |---> @method[void] actualizar_estados() evoluciona el sistema un paso 
	 * |				   segun el algoritmo del modelo de percolacion
	 * |---> @method[void] propagar(bool, string, string) evoluciona el sistema 
	 * |				   hasta que se extinga el fuego, permite guardar o no 
	 * |				   los datos de cada paso de tiempo.
	 * 
	 * @private
	 * |---> @attrubute[int] L la dimension de la red de arboles es LxL
	 * |---> @attrubute[double] p probabilidad de propagacion del fuego
	 * |---> @attrubute[int] t_fuego numero de pasos de simulacion 
	 * |---> @attrubute[int] num_activos numeros de arboles en estado QUEMANDOSE
	 * |---> @attrubute[int] num_quemados numeros de arboles en estado QUEMADO
	 * |---> @attrubute[int] num_vivos numeros de arboles en estado SANO
	 * |---> @attrubute[vector<vector<Arbol>] elementos red de arboles LxL
	 * |
	 * |---> @method[void] calcular_primeros_vecinos(int i, int j) asigna los 
	 * |    			   vecinos del elemento i,j del arreglo
	 * |---> @methos[void] escribir_archivo(string, string) genera un archivo con
	 * |				   la información de la red en el paso de tiempo actual
	 */
	public:
		Bosque(int, double);  
		~Bosque();

		int obtener_num_arboles(int) const;
		int obtener_tiempo() const;
		void cambiar_tamanio(int);
		void cambiar_probabilidad(double);

		void inicializar_bosque();
		void actualizar_estados();
		void propagar(bool save=false, string pathName="./data/prueba/files/", 
				      string ImagesPathName="./data/prueba/images/");	
	private:
		int L;
		double p;

		int t_fuego;

		int num_activos;
		int num_quemados;
		int num_vivos;
		
		vector < vector <Arbol>> elementos;

		void calcular_primeros_vecinos(int, int);
		void escribir_archivo(string, string);

};

#endif