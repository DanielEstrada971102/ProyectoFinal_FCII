
# L y p se pasan como argumentos en la ejecucion
# gnuplot -e "folder=value; L=value ; p=value" graficar_bosque.gp

set palette maxcolors 3
set palette model RGB defined ( \
  0 "black", \
  1 "green", \
  2 "red")

set size square
set autoscale
show autoscale
set pointsize 2

FILES = system("ls -1 data/".folder."/files/*.dat")
nfiles = words(FILES)

set terminal png size 1024,768

do for [i=0:nfiles-1]{
	imageName = sprintf("data/%s/images/step_%.1d.png",folder, i) 
	set output imageName

	titulo = sprintf("t = %.1d L = %.1d p = %.2f", i, L, p)  
	set title titulo
	file = sprintf("data/%s/files/step_%.1d.dat", folder, i)

   	plot file using 2:3:4 notitle with points ls 3 palette	
}


