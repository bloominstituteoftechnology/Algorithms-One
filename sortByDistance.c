/*
 * The Traveling Salesman Problem (TTSP)
 * sortByDistance.c
 * ----------------
 * Prepare an array of linked lists of sorted cities
 *
 * Version 0.1_b
 * 2017-11-04
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ttsp.h"

struct SortedCity **
sortByDistance(struct City *listOfCities, int size) {
  int i, j;

  struct SortedCity **head;     /* array of linked lists */
  struct SortedCity *reference; /* linked list */
  struct SortedCity *nextCity;  /* link to next city */

  struct City city1; /* reference city */
  struct City city2; /* a neighbor of reference city */

  /* head of all linked lists */
  head = calloc(size, sizeof(struct SortedCity));
  /* FREE(**head) */

  /* use each city in path of cities as a reference city */
  for (i = 0; i < size; i++) {
    reference = malloc(sizeof(struct SortedCity)); /* reference city */
    city1 = listOfCities[i]; /* for distance calculation */
    reference->city = &listOfCities[i];
    reference->position = i;
    reference->distance = 0.0;
    reference->next = NULL;

    head[i] = reference; /* place reference into the array */
    /* FREE(head[i]) */

    for (j = 0; j < size; j++) {
      if (j == i) continue; /* skip over the same */
      /* to be inserted into city */
      nextCity = malloc(sizeof(struct SortedCity)); 
      /* FREE(nextCity) */
      city2 = listOfCities[j]; /* for distance calculation */
      nextCity->city = &listOfCities[j];
      nextCity->position = j;
      nextCity->distance = distance(city1.coord, city2.coord);
      nextCity->next = NULL;

      /* inserts nextCity into linked list in distance order */
      insertCity(reference, nextCity);
    }
  }

  return head;
} /* sortByDistance() */


void
insertCity(struct SortedCity *a, struct SortedCity *b) {
  struct SortedCity *prior = NULL;

  while (b->distance > a->distance) {
    if (a->next == NULL) {
      a->next = b;
      return;
    }
    prior = a;
    a = a->next;
  }
  b->next = prior->next;
  prior->next = b;
  return;
} /* insertCity() */


void
printSortedCities(struct SortedCity **sortedCities, int size) {
  int i;

  struct SortedCity *nextCity;

  printf("\nSorted Cities\n");

  for (i = 0; i < size; i++) {
    printf("[%d] %-16s\n", i, sortedCities[i]->city->name);

    nextCity = sortedCities[i]->next;
    while (nextCity != NULL) {
      printf("\t[%d] %-16s\t%.2f\n", nextCity->position, nextCity->city->name, nextCity->distance);
      nextCity = nextCity->next;
    }
  }
} /* printSortedCities() */
