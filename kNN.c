/*
 * The Traveling Salesman Problem (TTSP)
 * kNN.c
 * Calculate TTSP by k-NN Recursive algorithm
 * Version 0.1_e
 * 2017-11-05
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

  /* kNNRoute will hold  the solution to the TTSP  (shortest route and
     round trip distance) */
  struct Route *kNNRoute = malloc(sizeof(struct Route));
  kNNRoute->route = malloc(sizeof(union Permuter));
  /* both free'd in TTSP.c */

  sourceCities = deepCityCopy(setOfCities, n);

  /* In an attempt to speed up  the algorithm, pre-sort all the cities
     by distance from a reference  city; array of sorted linked lists,
     each city sorted by distance from a reference city, an element in
     the array;  head is  a pointer  to head  of the  array; n  is the
     length of the array */
  struct SortedCity **head = sortByDistance(sourceCities, n);
  /* printSortedCities(head, n); */

  /* Calculate the distance around the route without any sorting, then
     use that value as the best route found so far */
  double initialDistance = calcRouteDistance(sourceCities, n);
  union Permuter p = {.cities_str = sourceCities};
  struct Dtype d = {CITY_STRUCT, n};
  if (n < 100) display(&p, d);
  printf("initial route distance (alphbetical order) is %.2f\n", initialDistance);
  kNNRoute->route->cities_str = deepCityCopy(p.cities_str, n);
  /* free'd in TTSP.c */
  kNNRoute->distance = initialDistance;

  /* Beginning of  the k-NN  Algorithm for  solving the  TTSP; iterate
     over the  source path placing each  city at the beginning  of the
     route and then  calculating the route distance  by k-NN recursive
     algorithm */
  for (i = 0; i < n; i++) {
    /* start with fresh copies of left and right */
    /* left will contain cities in sorted order */
    left = calloc(n, sizeof(struct City)); /* initially empty */
    /* right contains the cities remaining to be sorted */
    right = deepCityCopy(sourceCities, n); /* contains all cities */
    int left_size = 0;
    int right_size = n;

    /* move a city from the right array found at index i into the left
       array at index 0 to initialize route */
    exchange(left, right, left_size++, i, right_size--);

    /* Call the recursive algorithm with this setup */
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
  static int count;
  int k, this_knn;
  int new_left_size, new_right_size;
  double distance;

  struct City *newLeft;
  struct City *newRight;

  count++;
  this_knn = knn;

  if (right_size == 0) {
    bestRoute->iterations = count;
    /* printPath(left, left_size); */
    distance = calcRouteDistance(left, left_size);
    if (distance < bestRoute->distance) {
      /* found a shorter route; place into bestRoute */
      bestRoute->distance = distance;
      deepCityFree(bestRoute->route->cities_str, size);
      bestRoute->route->cities_str = deepCityCopy(left, left_size);
    }
  } else {
    /* find kth neighbor routes at each iteration */
    for (k = 0; k < this_knn; k++) {
      newLeft = deepCityCopy(left, size);
      new_left_size = left_size;
      newRight = deepCityCopy(right, size);
      new_right_size = right_size;
      getKthNeighbor(k, newLeft, &new_left_size, newRight, &new_right_size, head, size);
      kNNRecursive(knn=1 ? 1 : knn-1, newLeft, new_left_size, newRight, new_right_size, bestRoute, size, head);
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

  for (i = 0; i < size; i++) {
    printf("(%s, %s), ", path[i].name, path[i].state);
  }
  putchar('\n');
}
