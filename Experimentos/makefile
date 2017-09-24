make: 
	g++ -g -std=c++11 -o backtracking Backtracking.cpp
	g++ -g -std=c++11 -o backtrackingPodas BacktrackingPodas.cpp
	
clean:
	rm backtrackingPodas
	rm backtracking

sinpodas:
	./backtracking < Muestras/Random > Salidas/SalidaRandom
	./backtracking < Muestras/Positivas > Salidas/SalidaPositiva
	./backtracking < Muestras/Negativas > Salidas/SalidaNegativa

podas:
	./backtrackingPodas < Muestras/Random > Salidas/SalidaPodasRandom
	./backtrackingPodas < Muestras/Positivas > Salidas/SalidaPodasPositiva
	./backtrackingPodas < Muestras/Negativas > Salidas/SalidaPodasNegativa

Variacion:
	./backtracking < Muestras/Variaciones > Salidas/Variaciones
	