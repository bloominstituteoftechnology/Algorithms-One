/*
  The Traveling Salesman Problem (TTSP)
  kNN.c
  Version 0.1_b
  2017-11-03
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <float.h>

#include "ttsp.h"

extern struct City *setOfCities;

struct Route *
kNN(struct Dtype dtype, int knn) {
  int n = dtype.size; /* size of list of cities */

  struct Route *kNNRoute = malloc(sizeof(struct Route)); /* solution */
  kNNRoute->route = malloc(sizeof(union Permuter));
  kNNRoute->route->cities_arr = malloc(sizeof(struct City));
  kNNRoute->distance = 0.0;
  /* all free'd in TTSP.c */

  /* list of cities obtained from master list in order; don't alias */
  struct City *sourceCities = calloc(n, sizeof(struct City));
  memcpy(sourceCities, setOfCities, sizeof(struct City) * n);
  /* FREE *sourceCities */

  /* ++++++++++++++ for Debugging ++++++++++++++++++++++ */
  double initialDistance = calcRouteDistance(sourceCities, n);
  union Permuter p = {.cities_str = sourceCities};
  struct Dtype d = {CITY_STRUCT, 10};
  display(&p, d);
  printf("initial route distance is %.2f\n", initialDistance);
  /* hand-checked ok */
  /* +++++++++++++++++++++++++++++++++++++++++++++++++++ */

  /* array of sorted linked lists, by distance */
  struct SortedCity **head = sortByDistance(sourceCities, n);
  printSortedCities(head, n);

  struct City *left = calloc(n, sizeof(struct City));
  struct City *right = calloc(n, sizeof(struct City));
  /* FREE *left, *right */
  memcpy(right, sourceCities, sizeof(struct City) * n);
  int left_size = 0;
  int right_size = n;

  kNNRecursive(knn, left, left_size, right, right_size, kNNRoute, n, head);
  
  return kNNRoute;
} /* kNN() */

void
kNNRecursive(int knn,
             struct City *left, int left_size,
             struct City *right, int right_size,
             struct Route *bestRoute, int size,
             struct SortedCity **head)
{
  int k;
  double distance;

  if (left_size == 0) {
    distance = calcRouteDistance(left, left_size);
    if (distance < bestRoute->distance) {
      bestRoute->distance = distance;
      memcpy(bestRoute->route->cities_str, left, left_size);
    }
  } else {

    for (k = 0; k < knn; k++) {
    
    }
  }
} /* kNNRecursive */

double
calcRouteDistance(struct City *path, int size) {
  int i;
  double dist = 0.0;
  struct City *firstCity;
  struct City *nextCity;

  firstCity = &path[0];
  /* printCity(firstCity); */
  for (i = 1; i < size; i++) {
    nextCity = &path[i];
    dist += distance(firstCity->coord, nextCity->coord);
    /* printCity(nextCity); */
    firstCity = nextCity;
  }
  firstCity = &path[0];
  nextCity = &path[size-1];
  dist += distance(firstCity->coord, nextCity->coord);
  /* printCity(nextCity); */

  return dist;
}
