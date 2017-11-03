/*
  The Traveling Salesman Problem (TTSP)
  sortByDistance.c
  Version 0.1_a
  2017-11-03
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ttsp.h"

struct SortedCity **
sortByDistance(struct City *listOfCities, int size) {
  int i, j;

  struct SortedCity *city;
  struct SortedCity *nextCity;

  struct City city1;
  struct City city2;

  /* head of all chains */
  struct SortedCity **head = calloc(size, sizeof(struct SortedCity));
  /* FREE(*head[0..size]) */

  for (i = 0; i < size; i++) {
    city = malloc(sizeof(struct SortedCity));

    city->city = &listOfCities[i];
    city->position = i;
    city->distance = 0.0;
    city->next = NULL;

    head[i] = city;
    /* FREE(head[i]) */

    city1 = listOfCities[i]; /* for distance calculation */

    for (j = i + 1; j < size; j++) {
      nextCity = malloc(sizeof(struct SortedCity));
      /* FREE(nextCity) */
      city2 = listOfCities[j];
      nextCity->city = &listOfCities[j];
      nextCity->position = j;
      nextCity->distance = distance(city1.coord, city2.coord);
      nextCity->next = NULL;

      insertCity(city, nextCity);
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
    else
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
