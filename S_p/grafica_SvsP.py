# Este codigo genera las graficas de numero de arboles quemados en funcion
# de la probabilidad de propagacion (p) 
# 
# @autor -Daniel Estrada
# ------------------------------------------------------------------------------

from numpy import arange, loadtxt, fabs
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

def main():
	#p = arange(0, 1, 0.02)
	#s = loadtxt("Sp_51_1.txt")
	#grafica_Sp(p, s, "Sp_51_1.png", L=51)
	L = 1000
	p, s = loadtxt("Sp_&d.txt"%L, unpack=True)
	grafica_Sp(p, s, "Sp_%d.png", L=L)

	

def grafica_Sp(p, s, imageName, L):
	popt, pcov = curve_fit(f, p[:45], s[:45], [.3, -2.38]) # solo se usan los valores menores a p_c para ela juste

	fig, ax = plt.subplots()

	ax.loglog(p, s, 'or', label='datos')
	ax.loglog(p, f(p, *popt), '--b', label=r"$%.2f|p - 0.5|^{%.2f}$"%(popt[0], popt[1]))
	plt.title("Num Arbosles quedamos L = %d"%L)
	plt.xlabel("p")
	plt.ylabel("S")
	plt.legend(loc='best')
	plt.grid(True)
	plt.savefig(imageName)


def f(p, A, gamma):
	return A * fabs(p - 0.5) ** gamma


if __name__ == '__main__':
	main()