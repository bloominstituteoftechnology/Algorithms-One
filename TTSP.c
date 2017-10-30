/*
 * The Traveling Salesman Problem (TTSP)
 * TTSP.c main()
 * version 0.5_a
 * 2017-10-28
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "ttsp.h"

extern char *optarg;
extern int optind;
extern int optopt;
extern int opterr;
extern int optreset;

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

void
usage(char *program) {
  fprintf(stderr, "`%s'\nUSAGE: [-h] | [-l [num]] | [-n [num]]\n", program);
}

int main(int argc, char *argv[]) {

  char *optstring;
  int opt;
  int result, data_set, data_set_size;
  struct Dtype dtype;

  optstring = ":hl:n:";

  if ((opt = getopt(argc, argv, optstring)) == -1) {

    /* by default (no CL args), run the small data set */
    data_set = STRING_ARRAY;
    data_set_size = CITIES_SMALL;

  } else {
    switch (opt) {
    case 'h': case '?':
      usage(argv[0]);
      exit(EXIT_SUCCESS);
      break;
    case ':':
      switch (optopt) {
      case 'l':
        data_set = CITY_STRUCT;
        data_set_size = CITIES_BIG;
        break;
      case 'n':
        data_set = NEAREST_NEIGHBOR;
        data_set_size = CITIES_BIG;
        break;
      default:
        usage(argv[0]);
        exit(EXIT_FAILURE);
        break;
      }
      break;
    case 'l':
      data_set = CITY_STRUCT;
      data_set_size = atoi(optarg);
      break;
    case 'n':
      data_set = NEAREST_NEIGHBOR;
      data_set_size = atoi(optarg);
      break;
    }
  }

  if (data_set_size == 0) {
    fprintf(stderr, "ERROR: Data set value is zero\n");
    usage(argv[0]);
    exit(EXIT_FAILURE);
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

  case CITY_STRUCT: case NEAREST_NEIGHBOR:

    /* a bigger data set from text file of 115,000 plus cities */
    setOfCities = malloc(sizeof(struct City) * CITIES_SIZE);
    result = loadCities();
    printf("loaded %d records into setOfCities\n", result);

    if (data_set == CITY_STRUCT) {
      result = doPermutations(dtype, checkRoute);
      printf("Number of Permutations: %d\n", result);

    } else { /* case NEAREST_NEIGHBOR */
      fprintf(stderr, "NEAREST NEIGHBOR algorithm not implemented yet\n");
    }
    break;
  }

  return EXIT_SUCCESS;

} /* main() */

