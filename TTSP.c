/*
 * Traveling Salesman Problem (TSP)
 * main()
 * version 0.4_b
 * 2017-10-28
 */

#include <stdlib.h>
#include <stdio.h>
#include "ttsp.h"

#define CITIES 4 /* number of data items in the original problem */
#define CITIES_SIZE 115475 /* number of data items in usa115475 files */

static struct City CitiesSmallSet[] =
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




/*****************************************************************
 * 'setOfCities' holds a pointer to  the data set to be permuted;
 * it is a global variable, accessible from any c file as long as
 * it is  declared extern;  many functions  use it  to accomplish
 * their task.  Just  set the pointer to point to  a data set and
 * call 'doPermutation()'  with the number of  variables you want
 * to permute.  For example, the  small data set defined above is
 * first  permuted in  main  below,  then a  larger  data set  is
 * permuted by loading  the entire data set  in usa115475.tsp and
 * calling 'doPermutation()' again.
 *****************************************************************/
struct City *setOfCities;



/*****************************************************************/
int main(int argc, char *argv[]) {

  int result;

  /* the  original data  set of  four items;  see CitiesSmallSet,
     above */
  setOfCities = CitiesSmallSet;
  result = doPermutations(CITIES, STRING_ARRAY, display);
  printf("Result: %d\n", result);

  /* a bigger data set from text file of 115,000 plus cities */
  /* setOfCities = malloc(sizeof(struct City) * CITIES_SIZE); */
  /* result = loadCities(); */
  /* printf("loaded %d records into setOfCities\n", result); */

  /* result = doPermutations(10, checkRoute); */
  /* printf("Number of Permutations: %d\n", result); */
}
