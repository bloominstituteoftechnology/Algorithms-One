/*
 * loadCities.h
 * 2017-10-25
 *
 * Version 0.2_d
 *
 * Load usa115475_cities_a.txt and usa115475.tsp
 * format for use by Traveling Salesman Problem
 */

#ifndef LOADCITIES
#define LOADCITIES
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "./travellingSalesman.h"

#define CITIES_FILE "./TSP/usa115475.tsp"
/* NOTE: usa115475_cities.txt must first be processed by cityfilter.pl
         to produce usa115475_cities_a.txt so that the sscan library
         function will work properly */
#define CITIES_NAMES "./TSP/usa115475_cities_a.txt"
#define CITIES_SIZE 115475
#define READ "r"
#define BUFSIZE 100

extern int errno;

/********* PROTOTYPES ***********/

struct City *
loadCities(void);

/* Find the first line at which cities begins,
 * i.e., skip over header lines */
void
findFirstCity(FILE *);

/* Get the next city line; returns EOF
 * on eof or 1 on successful read */
int
getCity(FILE *, char *);

/* Given a line containing city coordinates,
 * and a line containing a city and state,
 * fill a City struct */
void
fillCity(char *, char *, struct City *);

/* Given a line, extract its coordinates */
double
getCoord(char *);

/* Print a city's name, state, and x and y coordinates */
void
printCityInfo(struct City *);

/********************************/

#endif
