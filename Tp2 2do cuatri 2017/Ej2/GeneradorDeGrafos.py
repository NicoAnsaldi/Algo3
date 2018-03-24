import random

a = raw_input()
b = raw_input()

print '{0:d} {1:d}'.format(int(a), int(b))
aristas = []
for i in range(0, int(b)):
	x = random.randint(0,int(a)-1)
	y = random.randint(0,int(a)-1)
	while x == y:
		y = random.randint(0,int(a)-1)
	while ((x,y) in aristas) or ((y,x) in aristas):
		x = random.randint(0,int(a)-1)
		y = random.randint(0,int(a)-1)
		while x == y:
			y = random.randint(0,int(a)-1)
	aristas.append((x,y))
	print '{0:d} {1:d} {2:d}'.format(x,y, random.randint(1,30))

	