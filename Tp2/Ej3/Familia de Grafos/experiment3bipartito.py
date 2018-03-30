import random
from math import ceil

for	c in range(6, 107):
	for i in range(0, 1):
		f = 5
		r = c # conexo o no depende de f, pero no puede ser mayor
		#r = c # no conexo, con f > 2
		#r = c+f # conexo
		#r = ((c+f)*(c+f-1))/2 #completo
		print '{0:d} {1:d} {2:d}'.format( f, c, r) 
		aristas = []
		unidosafabrica = []
		fabricasConectadas = []
		aristasRestantes = r
		for i in range(0, f):
			unidosafabrica.append(i)

		for i in range(0, c):
			x = f+i
			y = random.randint(0,f-1)

			while(x == y or (x,y) in aristas or (y,x) in aristas or (y in fabricasConectadas and len(fabricasConectadas) < f) or (f - len(fabricasConectadas) == aristasRestantes)):
				y = random.randint(0,f-1)

			if (y < f):
				fabricasConectadas.append(y)
			aristas.append((x,y))
			aristasRestantes-=1
			print '{0:d} {1:d} {2:d}'.format(x,y, random.randint(1,9))
print '{0:d}'.format(0)