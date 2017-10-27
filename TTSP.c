/*
 * Traveling Salesman Problem (TSP)
 * 2017-10-25
 *
 * Version 0.3_h
 */

#include "./travellingSalesman.h"

int main(int argc, char *argv[]) {

struct City CitiesSmallSet[] =
  {
    "Denver",
    "CO",
    500.0,
    500.0,
    "Salt Lake City",
    "UT",
    300.0,
    500.0,
    "Cheyenne",
    "WY",
    500.0,
    600.0,
    "Santa Fe",
    "NM",
    500.0,
    350.0,
  };

/* This is the small data set used to test the TSP problem */

  /* get set of city names */

  /* first, use given small set */

  /* send to travellingSalesman doPermutations */

  int result = doPermutations(CitiesSmallSet, CITIES, display);

  /* receive back answer and report */
  printf("Result: %d\n", result);

}
