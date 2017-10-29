/*
 * The Traveling Salesman Problem (TTSP)
 * TTSP.c main()
 * version 0.5
 * 2017-10-28
 */

#include <stdlib.h>
#include <stdio.h>
#include "ttsp.h"

static struct City CitiesSmallSet[] =
  {
    {"Denver",         "CO", {500.0, 500.0}},
    {"Salt Lake City", "UT", {300.0, 500.0}},
    {"Cheyenne",       "WY", {500.0, 600.0}},
    {"Santa Fe",       "NM", {500.0, 350.0}},
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


int main(int argc, char *argv[]) {
  int result, data_set, data_set_size;
  struct Dtype dtype;

  /* be default, run the small data set */
  data_set = STRING_ARRAY;
  data_set_size = CITIES_SMALL;

  if (argc >= 2) {
    if (*argv[1] == 'L') { /* usage: `ttsp L' */
      data_set = CITY_STRUCT;
      data_set_size = CITIES_BIG;
      if (argc == 3)
        data_set_size = atoi(argv[2]);
    }
  }

  dtype.dtype = data_set;
  dtype.size = data_set_size;
  
  switch (data_set) {

  case STRING_ARRAY:
    
    /* a small default data set; see above */
    setOfCities = CitiesSmallSet;
    result = doPermutations(dtype, display);
    printf("Result: %d\n", result);
    break;

  case CITY_STRUCT:

    /* a bigger data set from text file of 115,000 plus cities */
    setOfCities = malloc(sizeof(struct City) * CITIES_SIZE);
    result = loadCities();
    printf("loaded %d records into setOfCities\n", result);
    result = doPermutations(dtype, checkRoute);
    printf("Number of Permutations: %d\n", result);
    break;
  }

  return EXIT_SUCCESS;

} /* main() */
