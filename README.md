# ProyectoFinal_FCII

En este proyecto se presenta un modelo muy simple que ejemplifica el fenómeno de la percolación.

Se presenta un modelo de propagación de un incendio en un bosque de geometría cuadrada, de tamaño de lado L. La clase denominada Bosque es una matriz cuyos elementos son del tipo de estructura definida como Arbol. Cada elemento Arbol tiene 3 estados posibles: SANO, QUEMADO y QUEMANDOSE, además de que está identificado con un id y su posición en la matriz Bosque. A cada Arbol se le permite conocer el estado de sus cuatro vecinos más cercanos: arriba, abajo, izquierda y derecha, esto debido a que un Arbol vecino que esté en estado QUEMANDOSE tiene probabilidad P de propagar el fuego a sus vecinos en estado SANO.
El sistema comienza siempre con un incendio propagándose desde el centro del Bosque y evoluciona en el tiempo hasta que no haya ningún elemento Arbol en estado QUEMANDOSE. Como parámetros de la simulación se tiene el tamaño del lado L del Bosque y la probabilidad P de contagiar el estado QUEMANDOSE a los vecinos. En todo momento el sistema podrá devolver la cantidad de elementos Arbol en cualquiera de los 3 estados y el número de pasos de tiempo que han transcurrido. Como resultado de la simulación se provee un conjunto de archivos con el estado de cada Arbol del sistema en cada instante de tiempo (un archivo por paso de tiempo), se entrega también un conjunto de imágenes que representan el sistema en cada tiempo, se usan diferentes colores para representar el estado de cada árbol: verde para el estado SANO, rojo para el estado QUEMANDOSE y negro para el estado QUEMADO, finalmente con esta imagénes se genera un archivo .gif que muestra cómo el sistema evoluciona en el tiempo.

## Instalación

Para correr la simulacion usando el Makefile se puede ejecutar el siguiente comando:

```bash
make run L P NOMBRE_CARPETA_ARCHIVOS_SALIDA
```

donde:

L --> parametro para la dimensión del bosque

P --> parametro para probabilidad de propagación
NOMBRE_CARPETA_ARCHIVOS_OUT --> nombre para una carpeta que contenga los archivos de salida de la simulacion

ejecutando este comando se crea una carpeta en ./data con el nombre que indicado. Además se genera un gif nombrado
con los parametros L y P que se pusieron.

## Cómo usar

En la carpeta src se encuentra el archivo bosque.cpp la definición de las funciones de la clase Bosque.
En la carpeta include se encuentra el archivo bosque.h que contiene la declaración de la clase.
En la carpeta data quedan por defecto todas las imágenes y archivos que genera el programa.
En la carpeta S_p hay un programa que realiza la simulación un número de veces kmax. Esto se repite para cada valor de p entre 0 y 1 en intervalos de 0.01, con eso se hace un promedio del número de arboles quemados en funcion de p y se puede graficar con el archivo grafica_SvsP.py dentro de esta misma carpeta.
En la carpeta S_t hay dos archivos para compilar. S_vs_t.cpp que sirve para correr la simulacion para diferentes valores de p y guardar un archivo con el número de árboles en cada estado, en cada paso de tiempo. El archivo S_t se usa para simular el sistema un número k_max de veces para valores de p entre 0 y 1 con paso 0.02. Se promedia el número total de árboles quemado para todas las k_max simulaciones hechas con el mismo p y se guardan en un archivo. Se puede graficar  con el archivo grafica_SvsT.py

Para poder compilar los archivos en S_p y S_t hay que poner en la misma carpeta el archivo que se quiere junto con bosque.cpp y bosque.h que están en las carpetas ya indicadas. Los parámetros se pueden cambiar dentro del archivo, además se puede cambiar el tamaño de paso de incremento de p y el número de veces kmax que se corre cada simulación de cada p.

## Autores
Valentina Bedoya
Johan Carrillo
Daniel Estrada
Lina Montoya



