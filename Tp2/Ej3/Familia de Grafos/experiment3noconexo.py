import random
from math import ceil

for	c in range(6, 107):
	for i in range(0, 1):
		f = 5
		r = c # no conexo, con f > 2
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
			y = random.randint(0,f+c-1)

			while(x == y or (x,y) in aristas or (y,x) in aristas or (y < f and y in fabricasConectadas) or ( not( (x in unidosafabrica) or (y in unidosafabrica) ) ) or (f - len(fabricasConectadas) == aristasRestantes and y >= f) ):
				y = random.randint(0,f+c-1)

			if (y < f):
				fabricasConectadas.append(y)
			if ( not(x in unidosafabrica)):
				unidosafabrica.append(x)
			if ( not(y in unidosafabrica)):
				unidosafabrica.append(y)		
			aristas.append((x,y))
			aristasRestantes-=1
			print '{0:d} {1:d} {2:d}'.format(x,y, random.randint(1,9))

		for i in range(0, aristasRestantes):
			x = random.randint(0,f+c-1)
			y = random.randint(0,f+c-1)
		
			while(x == y or (x,y) in aristas or (y,x) in aristas or (y < f and y in fabricasConectadas) or ( not( (x in unidosafabrica) or (y in unidosafabrica) ) ) or (f - len(fabricasConectadas) == aristasRestantes and y >= f)):
				x = random.randint(0,f+c-1)
				y = random.randint(0,f+c-1)

			if ( not(x in unidosafabrica)):
				unidosafabrica.append(x)
			if ( not(y in unidosafabrica)):
				unidosafabrica.append(y)		
			aristas.append((x,y))
			aristasRestantes-=1
			print '{0:d} {1:d} {2:d}'.format(x,y, random.randint(1,9))
print '{0:d}'.format(0)

