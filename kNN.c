/*
 * The Traveling Salesman Problem (TTSP)
 * kNN.c
 * Calculate TTSP by k-NN Recursive algorithm
 * Version 0.1_c
 * 2017-11-04
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <float.h>

#include "ttsp.h"

extern struct City *setOfCities;

struct Route *
kNN(struct Dtype dtype, int knn) {
  int i;
  int n = dtype.size; /* size of list of cities */
  struct City *sourceCities; /* original set of cities in path */
  struct City *left; /* path used to build up a route */
  struct City *right; /* path used to build up a route */

  /* holds the solution (shortest route and its distance) */
  struct Route *kNNRoute = malloc(sizeof(struct Route));
  kNNRoute->route = malloc(sizeof(union Permuter));
  /* all free'd in TTSP.c */

  sourceCities = deepCityCopy(setOfCities, n);

  /* array of sorted linked lists, each city sorted by distance from a
     reference city*/
  struct SortedCity **head = sortByDistance(sourceCities, n);
  printSortedCities(head, n);

  /* ++++++++++++++ for Debugging ++++++++++++++++++++++ */
  double initialDistance = calcRouteDistance(sourceCities, n);
  union Permuter p = {.cities_str = sourceCities};
  struct Dtype d = {CITY_STRUCT, n};
  display(&p, d);
  printf("initial route distance is %.2f\n", initialDistance);
  kNNRoute->route->cities_str = deepCityCopy(p.cities_str, n);
  kNNRoute->distance = initialDistance;
  /* hand-checked ok */
  /* +++++++++++++++++++++++++++++++++++++++++++++++++++ */

  /* iterate over the source path placing each city at the beginning
     of the route and then calculating the route distance by k-NN
     recursive algorithm */
  for (i = 0; i < n; i++) {
    /* start with fresh copies of left and right */
    left = calloc(n, sizeof(struct City)); /* initially empty */
    right = deepCityCopy(sourceCities, n); /* contains all cities */
    int left_size = 0;
    int right_size = n;
    /* place city in right at index i into left at index 0 to initialize
       route */
    exchange(left, right, left_size++, i, right_size--);
    
    kNNRecursive(knn, left, left_size, right, right_size, kNNRoute, n, head);
    deepCityFree(right, n);
    deepCityFree(left, n);
  }
  /* FREE *sourceCities: kNN.c 31 */

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

  struct City *newLeft;
  struct City *newRight;

  if (right_size == 0) {
    printPath(left, left_size);
    distance = calcRouteDistance(left, left_size);
    if (distance < bestRoute->distance) {
      /* found a shorter route; place into bestRoute */
      bestRoute->distance = distance;
      deepCityFree(bestRoute->route->cities_str, size);
      bestRoute->route->cities_str = deepCityCopy(left, left_size);
    }
  } else {
    /* find kth neighbor routes at each iteration */
    for (k = 0; k < knn; k++) {
      getKthNeighbor(k, left, &left_size, right, &right_size, head, size);
      newLeft = deepCityCopy(left, size);
      newRight = deepCityCopy(right, size);
      kNNRecursive(knn == 1 ? 1 : knn - 1, newLeft, left_size, newRight, right_size, bestRoute, size, head);
      deepCityFree(newLeft, size);
      deepCityFree(newRight, size);
    }
  }
} /* kNNRecursive */


struct City *
deepCityCopy(struct City *cityPath, int size) {
  int i;
  struct City *newCityPath = malloc(sizeof(struct City) * size);
  /* FREE in deepCityFree() */
  for (i = 0; i < size; i++) {
    memcpy(&newCityPath[i], cityPath + i, sizeof(struct City));
  }
  return newCityPath;
} /* deepCityCopy() */


void
deepCityFree(struct City *cityPath, int size) {
  free(cityPath);
} /*deepCityFree() */


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
} /* calcRouteDistance() */


void
getKthNeighbor(int k,
               struct City *left,  int *left_size,
               struct City *right, int *right_size,
               struct SortedCity **head, int size)
{
  int i, j, stop;
  struct City *refCity = &left[*left_size-1];
  struct SortedCity *kthNeighbor;

  if (*right_size > 1) {
    i = findCityInSortedCities(refCity, head, size);
    kthNeighbor = head[i]->next; /* first neighbor */
    j = stop = 0;
    while (stop == 0) {
      if (j >= k && findCityInPath(kthNeighbor->city, left, *left_size) == -1)
        stop = 1;
      else {
        j++;
        kthNeighbor = kthNeighbor->next;
      }
    }

    j = findCityInPath(kthNeighbor->city, right, *right_size);
  } else j = 0;
  
  exchange(left, right, (*left_size)++, j, (*right_size)--);
} /* getKthNeighbor() */


int
findCityInSortedCities(struct City *city, struct SortedCity **head, int size) {
  int i = 0;
  while (i < size && !compareCities(city, head[i]->city))
    i++;

  if (i == size) {
    fprintf(stderr, "FATAL ERROR: attempting to find a city (%s) that is not in Sorted Cities\n", city->name);
    exit(EXIT_FAILURE);
  }
  return i;
} /* findCityInSortedCities() */


int
findCityInPath(struct City *city, struct City *path, int size) {
  int i = 0;
  while (i < size && !compareCities(city, &path[i]))
    i++;
  if (i == size) {
    return -1;
  }
  return i;
} /* findCityInPath */


int
compareCities(struct City *city1, struct City *city2) {
  return city1->coord.x == city2->coord.x && city1->coord.y == city2->coord.y;
} /* compareCities() */


void
printPath(struct City *path, int size) {
  int i;
  static int c;

  printf("[%d] ", c++);
  for (i = 0; i < size; i++) {
    printf("(%s, %s), ", path[i].name, path[i].state);
  }
  putchar('\n');
}
