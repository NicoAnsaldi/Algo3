make: 
	g++ -g -std=c++11 -o backtracking Backtracking.cpp
	g++ -g -std=c++11 -o backtrackingPodas BacktrackingPodas.cpp
	
clean:
	rm backtrackingPodas
	rm backtracking

test:
	./backtracking < input > Test/BacktrackingTest
	./backtracking < test1.in 
	./backtrackingPodas < input > Test/BacktrackingPodasTest
	./backtrackingPodas < test1.in