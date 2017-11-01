/*
 * travellingSalesman.c
 * The Traveling Salesman Problem (TTSP)
 * Version 1.0_b
 * 2017-11-01
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>

#include "ttsp.h"


extern struct City *setOfCities;
/* this  variable holds  the  set  of cities  to  be  permuted; it  is
   initialized in TTSP */


struct Route
shortestRoute = {NULL, DBL_MAX};
/* if  checkRoute() is  used  as a  callback  in doPermutations,  this
   variable will hold the shortest route found so far. */


int
doPermutations (struct Dtype dtype, void (*cb)(union Permuter *, struct Dtype)) {
  int c, result;
  char *cities[dtype.size]; /* variable length array */
  struct City *city;

  /* prepare the Permuter */
  permuter = malloc(sizeof(union Permuter)); /* declared in header */

  switch (dtype.dtype) {

  case STRING_ARRAY:
    /* fill cities array with combined city names and state abbr's */
    for (c = 0; c < dtype.size; c++) {
      cities[c] = malloc(sizeof(char) * MAX_NAME_SIZE);
      city = &setOfCities[c];
      /* 'city'  contains both  a  city name  and  state; catenate  them
         together  to  disambiguate  duplicate city  names;  combination
         cannot be larger than MAX_NAME_SIZE */
      strncpy(cities[c], city->name, strlen(city->name));
      strncat(cities[c], ",", 1);
      strncat(cities[c], city->state, 2);
    }
    permuter->cities_arr = cities;
    break;

  case CITY_STRUCT:
    permuter->cities_str = setOfCities;
    break;
  } /* end switch dtype */

  /* now call  Heap's Algorithm  permute function; include the callback
     that will be called after every permutation */
  result = permute(dtype.size, permuter, dtype, cb);

  /* free allocated memory before returning */
  if (dtype.dtype == STRING_ARRAY)
    for (c = 0; c < dtype.size; c++)
      free(cities[c]);
  free(permuter);

  /* upon return, display shortest route information if it was calculated */
  if (shortestRoute.route != NULL) {
    printf("The shortest distance is: %.2f\n", shortestRoute.distance);
    display(shortestRoute.route, dtype);
  }

  /* TODO: need to free all malloced memory */
  return result;
} /* doPermutations() */

void
exchange(struct City *cities1, struct City *cities2, int i, int j, int k) {
  cities1[i] = cities2[j];
  cities2[j] = cities2[k-1];
} /* exchange() */


double
distance(struct Coord city1, struct Coord city2) {
  double dist_x = city2.x - city1.x;
  double dist_y = city2.y - city1.y;
  double dist = sqrt(dist_x * dist_x + dist_y * dist_y);
  return dist;
} /* distance() */


void
printCity(struct City *city) {
  printf("%s, %s (%f, %f)\n", city->name, city->state, city->coord.x, city->coord.y);
} /* printCity() */


struct City *
lookup(char *city, int size) {
  int i = 0;

  /* city will be string with city name and state concatenated together */
  while (i < size) {
    /* extract the city name and the state for comparison */
    char real_city[MAX_NAME_SIZE], real_state[3];
    memset(real_city, 0, MAX_NAME_SIZE);
    memset(real_state, 0, 3);
    strncpy(real_city, city, (size_t)(strlen(city) - 3)); /* avoid the comma */
    strncat(real_state, city + (strlen(city) - 2), (size_t)2);

    /* now find a match for both city and state */
    if (strncmp(setOfCities[i].name, real_city, MAX_NAME_SIZE) == 0 &&
        strncmp(setOfCities[i].state, real_state, 2) == 0)
      return &setOfCities[i];
    i++;
  }
  fprintf(stderr, "Failed to find city %s\n", city);
  exit(EXIT_FAILURE);
} /* lookup() */


double
roundTrip(union Permuter *permuter, struct Dtype dtype) {
  int i, n;
  double roundTripDistance = 0;
  struct City *tripset_str, *city1, *city2;
  char **tripset_arr;

  n = dtype.size;
  if (n == 1) return 0;

  switch (dtype.dtype) {
  case STRING_ARRAY:
    tripset_arr = permuter->cities_arr;
    for (i = 1; i < n; i++) {
      /* This is the reason for  the Permuter: to avoid this expensive
         lookup for each permutation to obtain a city's coordinates to
         calculate distance */
      city1 = lookup(tripset_arr[i - 1], n);
      city2 = lookup(tripset_arr[i], n);
      roundTripDistance += distance(city1->coord, city2->coord);
    }
    /* and these lookups */
    city1 = lookup(tripset_arr[0], n);
    city2 = lookup(tripset_arr[n-1], n);
    roundTripDistance += distance(city1->coord, city2->coord);
    break;

  case CITY_STRUCT:
    tripset_str = permuter->cities_str;
    for (i = 1; i < n; i++) {
      city1 = &tripset_str[i-1];
      city2 = &tripset_str[i];
      roundTripDistance += distance(city1->coord, city2->coord);
    }
    city1 = &tripset_str[0];
    city2 = &tripset_str[n-1];
    roundTripDistance += distance(city1->coord, city2->coord);
    break;
  }

  return roundTripDistance;
} /* roundTrip() */


void
checkRoute(union Permuter *permuter, struct Dtype dtype) {
  double distance = roundTrip(permuter, dtype);

  if (distance < shortestRoute.distance) {
    shortestRoute.distance = distance;
    shortestRoute.route = permuter;
  }
} /* checkRoute() */


void
doNothing(union Permuter *nada, struct Dtype empty) {}
/* doNothing() */
