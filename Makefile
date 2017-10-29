ttsp:	heapsAlg.o loadCities.o travellingSalesman.o TTSP.o
	clang -o ttsp heapsAlg.c loadCities.c travellingSalesman.c TTSP.c

debug: 	heapsAlg.o loadCities.o travellingSalesman.o TTSP.o
	clang -g -std=c11 -Wall -Werror -pedantic-errors -o ttsp heapsAlg.c loadCities.c travellingSalesman.c TTSP.c

heapsAlg.o loadCities.o travellingSalesman.o TTSP.o:	ttsp.h

clean:
	rm *.o ttsp
