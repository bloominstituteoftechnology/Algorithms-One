/*
 * nearestNeighbor.c
 * The Traveling Salesman Problem (TTSP)
 * Version 2.0
 * 2017-11-05
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <float.h>

#include "ttsp.h"

extern struct City *setOfCities;
/* global variable initialized in TTSP */

struct Route *
nearestNeighborSearch(struct Dtype dtype) {
  int c, n;
  static int count = 0;
  double pathDistance, shortestDistance;
  struct Route *nearestNeighborRoute;

  n = dtype.size; /* number of cities to iterate over */
  struct City sourceCities[n];
  struct City path[n];
  struct City *shortestPath = malloc(sizeof(struct City) * n);

  shortestDistance = DBL_MAX;
  for (c = 0; c < n; c++) {
    /* start with a fresh copy of cities */
    memcpy(sourceCities, setOfCities, (sizeof(struct City) * n));
    /* start with the next city */
    exchange(path, sourceCities, 0, c, n);
    /* calculate complete Nearest Neighbor solution for this starting city */
    pathDistance = nn(path, sourceCities, n, &count);
    if (pathDistance < shortestDistance) {
      shortestDistance = pathDistance;
      /* keep a copy of the current shortest path */
      memcpy(shortestPath, path, sizeof(struct City) * n);
    }
  }

  /* return the solution */
  nearestNeighborRoute = malloc(sizeof(struct Route));
  nearestNeighborRoute->route = malloc(sizeof(union Permuter));
  nearestNeighborRoute->route->cities_str = shortestPath;
  nearestNeighborRoute->distance = shortestDistance;
  nearestNeighborRoute->iterations = count;
  return nearestNeighborRoute;

} /* nearestNeighborSearch() */

double
nn(struct City *path, struct City *sourceCities, int n, int *count) {
  int i, j, k;
  int nearestNeighborSoFar;
  double currentDistance, totalDistance, nearestDistanceSoFar;

  struct City currentCity;
  struct City nextCity;
  struct Coord currentCoord;
  struct Coord nextCoord;

  i = 1;     /* index into path; already has the first city in it */
  j = 0;     /* index into sourceCities; start at zero */
  k = n - 1 ; /* number of cities in source; one has been moved out */
  totalDistance = 0;

  /* Nearest Neighbor Algorithm */
  while (i < n) {
    currentCity = path[i-1];
    currentCoord = currentCity.coord;
    nearestDistanceSoFar = DBL_MAX;
    nearestNeighborSoFar = -1;

    for (j = 0; j < k; j++) {
      nextCity = sourceCities[j];
      nextCoord = nextCity.coord;
      currentDistance = distance(currentCoord, nextCoord);

      if (currentDistance < nearestDistanceSoFar) {
        nearestDistanceSoFar = currentDistance;
        nearestNeighborSoFar = j;
      }
    }
    exchange(path, sourceCities, i, nearestNeighborSoFar, k);
    i++; k--;
    (*count)++;
    totalDistance += nearestDistanceSoFar;
  }

  /* Finish calculating the  distance from the last city  in the route
     to the first */
  currentCity = path[n-1];
  currentCoord = currentCity.coord;
  nextCity = path[0];
  nextCoord = nextCity.coord;
  currentDistance = distance(currentCoord, nextCoord);
  totalDistance += currentDistance;

  return totalDistance;
} /* nn */

