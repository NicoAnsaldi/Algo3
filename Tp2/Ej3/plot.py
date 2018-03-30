import matplotlib.pyplot as plt
import seaborn as sns
sns.set(style="darkgrid")

def datos(nombre_archivo):
    valores = open(nombre_archivo, "r") 
    valores = valores.read()
    valores = [float(x) for x in valores.split()]
    return valores

def bloques(valores,intervalo):
    res = []
    valor = 0
    for elem in range(0,len(valores)):
        if elem % intervalo == 0 and elem != 0:
            res.append(valor/intervalo)
            valor = 0
        valor += valores[elem]
    res.append(valor/intervalo)
    return res

nada = [None]

normal = bloques(datos("out2"),100)

#print normal
#plt.semilogy()
plt.plot(nada+normal)

plt.legend( ('Practica'), loc = 'upper left')
plt.grid(True)
plt.grid(color = '0.5', linestyle = '--', linewidth = 1)
#plt.axis('tight')
#plt.axis([1, 100, 0, 0.0001])
plt.xlabel(r"Cantidad de iteracion", fontsize = 24, color = 'black')
plt.ylabel(r"Tiempo en Segundos", fontsize = 24, color = 'black')
plt.title(' Practica vs Teorica',fontsize = 28, color = 'black', verticalalignment = 'baseline', horizontalalignment = 'center')
plt.show()