/*
 * nearestNeighbor.c
 * The Traveling Salesman Problem (TTSP)
 * Version 1.0_a
 * 2017-10-31
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
  double currentDistance, totalDistance, nearestDistanceSoFar;
  int nearestNeighborSoFar;
  int i, j, k, n;

  /* nearestNeighborRoute will hold the solution (path and distance)
     to the Nearest Neighbor Problem;
     nearestNeighborPath will hold the solution path and will go
     inside nearestNeighborRoute; */
  struct Route *nearestNeighborRoute = malloc(sizeof(struct Route));
  union Permuter *nearestNeighborPath = malloc(sizeof(union Permuter));

  struct City currentCity;
  struct City nextCity;
  struct Coord currentCoord;
  struct Coord nextCoord;

  n = dtype.size;
  i = 0;
  j = 0;
  k = n;

  /* sourceCities will be a mutable copy (not alias) of the source cities */
  struct City sourceCities[n];
  memcpy(sourceCities, setOfCities, (sizeof(struct City) * n));

  /* path will hold the solution path to the Nearest Neighbor Problem, and
     go inside nearestNeighborPath at the end; */
  struct City *path = malloc(sizeof(struct City) * n);

  /* place the first city inside path; then calculate nearest neighbors
     from that starting point */
  exchange(path, sourceCities, &i, &j, &k);
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
    exchange(path, sourceCities, &i, &j, &k);
    totalDistance += nearestDistanceSoFar;
  }

  /* return the solution */
  nearestNeighborPath->cities_str = path;
  nearestNeighborRoute->route = nearestNeighborPath;
  nearestNeighborRoute->distance = totalDistance;
  return nearestNeighborRoute;

} /* nearestNeighborSearch() */
