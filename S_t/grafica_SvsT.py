# Este codigo genera las graficas de numero de arboles quemados en funcion
# del paso de la simulacion (t) para cada p disponible en la carpeta files
# 
# @autor -Daniel Estrada
# ------------------------------------------------------------------------------

from numpy import loadtxt
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

def main():
	
	L = 100
	p =50 #se genera la grafica para algun p de los archivos disponinbles

	fig, ax = plt.subplots()

	t,_,_, s = loadtxt("files/S_1000_%d.txt"%p, unpack=True)
	
	popt, pcov = curve_fit(f, t, s)

	ax.plot(t, s, ".k")
	ax.plot(t, f(t, *popt), '--r', label=r"$ p= %.2f ,%.2f t^{%.2f}$"%(p,popt[0], popt[1]))

	plt.title("Num Arboles quemados L = %d"%L)
	plt.xlabel("t")
	plt.ylabel("S")
	plt.legend(loc='best')
	plt.grid(True)
	plt.savefig("S_t%d.png"%p)


def f(t, A, nu):
	return A * t ** nu


if __name__ == '__main__':
	main()