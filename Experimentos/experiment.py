import random

#random.seed(50)
encuestas = random.randint(1, 30) #encuestas
for agente in range(1,24): #agentes
	for muestras in range(0,100): #muestras
		encuestas = random.randint(1, 31) #encuestas
		print '{0:d} {1:d}'.format(agente,encuestas) #agentes y #encuestas
		for unaencuesta in range(0,encuestas):
			print '{0:d} {1:s}{2:d}'.format(random.randint(1, agente), random.choice(' -'), random.randint(1, agente))
print '{0:d} {1:d}'.format(0,0)