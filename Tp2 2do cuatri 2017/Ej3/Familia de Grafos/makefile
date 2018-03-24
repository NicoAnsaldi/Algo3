all:
	python experiment3conexo.py > exconexo
	python experiment3noconexo.py > exnoconexo
	python experiment3completo.py > excompleto
	python experiment3bipartito.py > exbipartito
	./ej3 < exbipartito > bipartitoout
	./ej3 < exconexo > conexoout
	./ej3 < exnoconexo > noconexoout
	./ej3 < excompleto > completoout
	python plot.py
rm:
