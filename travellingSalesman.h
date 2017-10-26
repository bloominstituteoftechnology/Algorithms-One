/*
 * Traveling Salesman Problem (TSP)
 * Header file: travellingSalesman.h
 * 2017-10-25
 *
 */

#ifndef TSP
#define TSP

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "./minilab/heapsAlg.h"

#define CITIES 4

void
printCity(struct City *);

double
distance(char *, char *);

struct City *
lookup(char *);

double
roundTrip(char **);

void
checkRoute(char **);

#endif
