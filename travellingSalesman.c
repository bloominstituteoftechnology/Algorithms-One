/*
 * Traveling Salesman Problem (TSP)
 * 2017-10-25
 *
 * Version 0.4_a
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ttsp.h"



double
distance(char *, char *);
/*****************************************************************/

struct City *
lookup(char *);
/*****************************************************************/

double
roundTrip(char **);
/*****************************************************************/



struct Route
shortestRoute = /* keeps track of shortest route found so far */
  {
    NULL,
    -1
  };

extern struct City *setOfCities;


/***************************************************************************/
int
doPermutations (int numCities, void (*cb)(char **)) {
  /* fn  is  a  callback  that  will  be  sent  into  the  permutation
     algorithm */

  /* 'numCities' contains the number of  data elements to be permuted;
     'cities' will contain the original set of names (city,st) */

  char *cities[numCities + 1];

  /* fill cities with names and states combined */
  for (int c = 0; c < numCities; c++) {
    cities[c] = malloc(sizeof(char) * MAX_NAME_SIZE);
    struct City *city = &setOfCities[c];
    /* 'city'  contains both  a  city name  and  state; catenate  them
       together  to  disambiguate  duplicate city  names;  combination
       cannot be larger than MAX_NAME_SIZE */
    strncpy(cities[c], city->name, strlen(city->name));
    strncat(cities[c], ",", 1);
    strncat(cities[c], city->state, 2);
  }
  cities[numCities] = NULL; /* represents the end of the data set */

  /* call Heap's  Algorithm permute function; include  a callback that
     will be called after every permutation */
  int result = permute(numCities, cities, cb);

  /* only display shortest route information if it was calculated */
  if (shortestRoute.route != NULL) {
    printf("The shortest distance is: %.2f\n", shortestRoute.distance);
    display(shortestRoute.route);
  }

  /* TODO: need to free all malloced memory */
  return result;
}


/***************************************************************************/
double
distance(char *city1, char *city2) {
  struct City *city1_s = lookup(city1);
  struct City *city2_s = lookup(city2);
  double dist_x = city2_s->x - city1_s->x;
  double dist_y = city2_s->y - city1_s->y;
  double dist = sqrt(dist_x * dist_x + dist_y * dist_y);
  return dist;
}



/***************************************************************************/
void
printCity(struct City *city) {
  printf("%s, %s (%f, %f)\n", city->name, city->state, city->x, city->y);
}



/***************************************************************************/
struct City *
lookup(char *city) {
  /* city will be string with city name and state concatenated together */
  int i = 0;

  while (&setOfCities[i] != NULL) {
    /* extract the city name and the state for comparison */
    char real_city[MAX_NAME_SIZE], real_state[3];
    memset(real_city, 0, MAX_NAME_SIZE);
    memset(real_state, 0, 3);
    strncpy(real_city, city, (size_t)(strlen(city) - 3)); /* avoid the comma */
    strncat(real_state, city + (strlen(city) - 2), (size_t)2);

    /* now find a match for both city and state */
    if (strncmp(setOfCities[i].name, real_city, MAX_NAME_SIZE) == 0 && strncmp(setOfCities[i].state, real_state, 2) == 0)
      return &setOfCities[i];
    i++;
  }
  fprintf(stderr, "Failed to find city %s\n", city);
  exit(EXIT_FAILURE);
}



/***************************************************************************/
double
roundTrip(char **tripset) {
  double roundTripDistance = 0;
  int n = elements(tripset, 1);
  if (n == 1) return 0;

  for (int i = 1; i < n; i++)
    roundTripDistance += distance(tripset[i-1], tripset[i]);
  roundTripDistance += distance(tripset[0], tripset[n-1]);
  return roundTripDistance;
}



/***************************************************************************/
void
checkRoute(char **tripset) {
  double distance = roundTrip(tripset);
  if (shortestRoute.distance == -1 || distance < shortestRoute.distance) {
    shortestRoute.route = tripset;
    shortestRoute.distance = distance;
  }
}

void
doNothing(char **nothing) {}
