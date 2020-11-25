CC := g++
INC_DIR := include
SRC_DIR := src

OBJ := $(SRC_DIR)/bosque.cpp simulacion.cpp
CFLAGS := -Iinclude -Wall 
EXEC := simulacion_indencio.out

$(EXEC) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)

run: $(EXEC)
	./$(EXEC) $(L) $(P) $(OutFolder) #ejecuta el programa que simula el incendio
	gnuplot -e "folder='$(OutFolder)'; L=$(L) ; p=$(P)" graficar_bosque.gp # crea las graficas 
	convert -delay 10 @lista_imagenes.txt -loop 0 l$(L)_p$(P).gif # genera el gif
	rm lista_imagenes.txt #borra el archivo que genero el gif

clean:
	rm *.out *.txt