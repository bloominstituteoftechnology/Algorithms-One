/*
 * Traveling Salesman Problem (TSP)
 * Header file: travellingSalesman.h
 * 2017-10-25
 *
 * Version 0.3_g
 */

/*
 * Travelling Salesman Problem (TSP)
 * 
 * The  TSP   is  one  of   the  most  famous  problems   in  Computer
 * Science. Imagine a map containing n  cities that need to be visited
 * in an  optimal order. This  problem is  known to be  somewhere less
 * than O(n!) and greater than O(x^n).
 * TSP is one of the most  popular benchmark problems and a great many
 * algorithms have  been tested against  it. For the interest  time of
 * time and  experience, only  two algorithms  are prescribed  in this
 * assignment:

 * Solution Methods:

 * Exhaustive search (Breadth-first or Depth-first search)

 * Exhaustive  search  is  fundamentally   the  most  difficult  case:
 * calculate  the   length  of   every  possible  path,   keeping  the
 * shortest. This  method is guaranteed  to return the  shortest path,
 * but is  intractable for lists of  cities greater than ~20,  as this
 * algorithm is  NP-Complete and O(n!). The  algorithm to exhaustively
 * search involves starting from the  first ordered list of all cities
 * as integers, then  swapping a pair, calculating the  length of that
 * trip, storing  it if l(x) <  B, and repeating until  all swaps have
 * been performed:

 * Exhaustive Algorithm Psuedo Code:

best_trip_length = MAX
best_trip = []
for each ordering in the permutations of C:
  current_trip_length = 0
  for each pair in the ordering:
    current_trip_length += distance_between(current_pair)
  if(current_trip_length < best_trip_length)
    best_trip_length = current_trip_length
    best_trip = ordering

 * Nearest Neighbor search

 * Nearest neighbor  search (Choose only  the nearest neighbor  from a
 * given city).   This algorithm takes a  decidedly different approach
 * than exhaustive  and is  only O(n^2). It  doesn't produce  the best
 * result, but it tends to produce a  result that is within 25% of the
 * best result.  It is neither the  fastest nor the "most  optimal" of
 * the  decideable  algorithms,  but  it  is  easy  to  implement  and
 * understand.

given a list of cities to be visited l
path = []
for each city start in l:
  add start to path
  while(path.length != l.length)
    for each city in l not in path:
      current = distance(city, start);
      if(distance < best_nearest)
        best_nearest_distance = distance
        best_nearest = city
    path.add(best_nearest)


 * Implement the  above two algorithms.   Use the short and  long city
 * datasets  provided in  this  assignment and  compare their  running
 * times and the length and shapes of the paths they return.
 */

#ifndef TSP
#define TSP

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "./minilab/heapsAlg.h"
#include "./loadCities.h"

#define CITIES 4 /* number of data items in the original problem */
#define MAX_NAME_SIZE 0x20 /* max size of city name */

/* This is the small data set used to test the TSP problem */
struct City CitiesSmallSet[] =
  {
    "Denver",
    "CO",
    500.0,
    500.0,
    "Salt Lake City",
    "UT",
    300.0,
    500.0,
    "Cheyenne",
    "WY",
    500.0,
    600.0,
    "Santa Fe",
    "NM",
    500.0,
    350.0,
  };


struct Route {
  char **route;
  double distance;
};

int
doPermutations(struct City **, int, void(*fn)(char **));

/* Given a City struct, print its components */
void
printCity(struct City *);

/* Given two city names, search for the cities
 * in the data structure to obtain their coordinates,
 * then calculate the distance separating them */
double
distance(char *, char *, struct City *);

/* Given a city name, look up its data structure and
 * return it */
struct City *
lookup(char *, struct City *);

/* Given a set of cities, calculate the round trip
 * distance between them all */
double
roundTrip(char **, struct City *);

/* Given a set of cities, keep track of the shortest
 * distance set */
void
checkRoute(char **, struct City *);

#endif
