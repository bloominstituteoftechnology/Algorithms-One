/*
  The Traveling Salesman Problem (TTSP)
  kNN.c
  Version 0.1_a
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
  struct Route *kNNRoute = malloc(sizeof(struct Route)); /* solution */
  kNNRoute->route = malloc(sizeof(union Permuter));
  kNNRoute->route->cities_arr = malloc(sizeof(struct City));
  kNNRoute->distance = 0.0;
  /* all free'd in TTSP.c */

  struct SortedCity **head; /* array of sorted linked lists, by distance */

  int n = dtype.size; /* size of list of cities */

  /* list of cities obtained from master list in order; don't alias */
  struct City *sourceCities = calloc(n, sizeof(struct City));
  memcpy(sourceCities, setOfCities, sizeof(struct City) * n);

  /* first, sort the cities and place into an array of linked lists */
  head = sortByDistance(sourceCities, n);
  /* printSortedCities(head, n); */

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
  return 0;
}
