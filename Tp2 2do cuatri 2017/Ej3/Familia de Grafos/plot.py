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

bipartitos = bloques(datos("bipartitoout"),1)
noconexo = bloques(datos("noconexoout"),1)
conexo = bloques(datos("conexoout"),1)
completo = bloques(datos("completoout"),1)


plt.semilogy()
plt.plot(nada+bipartitos, label="Bipartitos")
plt.plot(nada+noconexo, label="No Conexos")
plt.plot(nada+conexo, label="Conexos")
plt.plot(nada+completo, label="Completos")


plt.legend(bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0.)
#plt.legend( ('Relaciones'), loc = 'upper left')
plt.grid(True)
plt.grid(color = '0.5', linestyle = '--', linewidth = 1)
plt.axis('tight')
#plt.axis([0, 20, 0, 0.00002])
plt.xlabel(r"Aumento de variables", fontsize = 15, color = 'black')
plt.ylabel(r"Tiempo en Segundos", fontsize = 15, color = 'black')
plt.title(' Familias de Grafos',fontsize = 17, color = 'black', verticalalignment = 'baseline', horizontalalignment = 'center')
plt.show()