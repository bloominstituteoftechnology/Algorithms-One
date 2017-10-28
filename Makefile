ttsp:	heapsAlg.o loadCities.o travellingSalesman.o TTSP.o
	clang -o ttsp heapsAlg.c loadCities.c travellingSalesman.c TTSP.c

heapsAlg.o loadCities.o travellingSalesman.o TTSP.o:	ttsp.h
