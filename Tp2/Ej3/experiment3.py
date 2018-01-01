import random

for c in range(2, 103):
	for i in range(0,100):
	#for i in range(0, 1):
		#c = random.randint(2, 5) #cantidad de clientes
		#c = range(2, 10)
		#f = random.randint(2, c) #cantidad de fabricas
		f = c
		#r = random.randint(c+f, (((f+c)*(f+c-1))/2+ (c+f))/2) #cantidad de aristas ((f+c)*(f+c-1))/2
		r = c+f

		print '{0:d} {1:d} {2:d}'.format( f, c, r)
		aristas = []
		unidosafabrica = []
		for i in range(0, f):
			unidosafabrica.append(i)

		for i in range(0, f):
			x = i
			y = random.randint(0,f+c-1)

			while(x == y or y > f and not((x in unidosafabrica) or (y in unidosafabrica)) or ((x,y) in aristas or (y,x) in aristas or (x-1,y) in aristas)):
				y = random.randint(0,f+c-1)

			if ( not(x in unidosafabrica)):
				unidosafabrica.append(x)
			if ( not(y in unidosafabrica)):
				unidosafabrica.append(y)		
			aristas.append((x,y))
			print '{0:d} {1:d} {2:d}'.format(x,y, random.randint(1,9))

		for i in range(0, c):
			x = f+i
			y = random.randint(0,f+c-1)

			while(x == y or y > f and not((x in unidosafabrica) or (y in unidosafabrica)) or ((x,y) in aristas or (y,x) in aristas) or (x-1,y) in aristas):
				y = random.randint(0,f+c-1)


			if ( not(x in unidosafabrica)):
				unidosafabrica.append(x)
			if ( not(y in unidosafabrica)):
				unidosafabrica.append(y)		
			aristas.append((x,y))
			print '{0:d} {1:d} {2:d}'.format(x,y, random.randint(1,9))


		for i in range(0, r-c-f):
			x = random.randint(0,f+c-1)
			y = random.randint(0,f+c-1)
				
			while(x == y or y > f and not((x in unidosafabrica) or (y in unidosafabrica)) or ((x,y) in aristas or (y,x) in aristas)):
				x = random.randint(0,f+c-1)
				y = random.randint(0,f+c-1)

			if ( not(x in unidosafabrica)):
				unidosafabrica.append(x)
			if ( not(y in unidosafabrica)):
				unidosafabrica.append(y)		
			aristas.append((x,y))
			print '{0:d} {1:d} {2:d}'.format(x,y, random.randint(1,9))
print '{0:d}'.format(0)
