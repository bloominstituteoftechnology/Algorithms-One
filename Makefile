ttsp:	heapsAlg.o loadCities.o travellingSalesman.o nearestNeighbor.o kNN.o sortByDistance.o TTSP.o
	clang -o ttsp heapsAlg.c loadCities.c travellingSalesman.c nearestNeighbor.c kNN.c sortByDistance.c TTSP.c

debug: 	heapsAlg.o loadCities.o travellingSalesman.o nearestNeighbor.o kNN.o sortByDistance.o TTSP.o
	clang -g -std=c11 -Wall -Werror -pedantic-errors -o ttsp heapsAlg.c loadCities.c travellingSalesman.c nearestNeighbor.c kNN.c sortByDistance.c TTSP.c

heapsAlg.o loadCities.o travellingSalesman.o nearestNeighbor.o kNN.o sortByDistance.o TTSP.o:	ttsp.h

clean:
	rm *.o ttsp
