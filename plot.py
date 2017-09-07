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

salidaRandom = bloques(datos("1salidaRandom"),100)
salidaPositiva = bloques(datos("1salidaPositiva"),100)
salidaNegativa = bloques(datos("1salidaNegativa"),100)
#print salidaRandom
#plt.legend(["Caso Random"])


salidaPositivaPodas = bloques(datos("1salidaPositiva"),100)
salidaPositivaSinpodas = bloques(datos("salidapositivassinpodas"),100)

#salidaNegativasPodas = bloques(datos("1salidaNegativa"),100)
#salidaNegativasSinpodas = bloques(datos("salidanegativassinpodas"),100)

#salidaRandomPodas = bloques(datos("1salidaRandom"),100)
#salidaRandomSinpodas = bloques(datos("salidarandomsinpodas"),100)

#print salidaPositivaPodas
#print salidaPositivaSinpodas
plt.semilogy()
plt.plot(nada+salidaPositivaPodas)
plt.plot(nada+salidaPositivaSinpodas)
#plt.plot(nada+salidaNegativa)
plt.legend( ('Sin podas', 'Con podas'), loc = 'upper left')
#plt.legend(["Caso Random"])
plt.grid(True)
plt.grid(color = '0.5', linestyle = '--', linewidth = 1)
plt.axis('tight')
plt.axis([0, 20, 0, 5])
plt.xlabel(r"Cantidad de Agentes", fontsize = 24, color = 'black')
plt.ylabel(r"Tiempo en Segundos", fontsize = 24, color = 'black')
plt.title('Positivas vs podas',fontsize = 28, color = 'black', verticalalignment = 'baseline', horizontalalignment = 'center')
plt.show()