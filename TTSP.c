/*
 * The Traveling Salesman Problem (TTSP)
 * TTSP.c main()
 * version 1.0_c
 * 2017-11-04
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
freeup(struct Route *);

void
usage(char *program) {
  fprintf(stderr, "`%s'\nUSAGE: [-h] | [-l [num]] | [-n [num]]\n", program);
}

int main(int argc, char *argv[]) {

  char *optstring;
  int opt, knn;
  int result, data_set, data_set_size;
  struct Dtype dtype;

  /* -l [num] := Heap's Alg (default 10)
   * -n [num] := Nearest Neighbor Alg (default 10)
   * -k [num] := k-NN Alg (default 2)
   */
  optstring = ":hl:n:k:";

  /* by default (no CL args), run the small data set
   * and knn == 1 */
  data_set = STRING_ARRAY;
  data_set_size = CITIES_SMALL;
  knn = 1;

  while ((opt = getopt(argc, argv, optstring)) != -1) {

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
      case 'k':
        data_set = KNN;
        knn = 2;
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
    case 'k':
      data_set = KNN;
      knn = atoi(optarg);
      if (knn <= 0 || knn > 8) {
        usage(argv[0]);
        fprintf(stderr, "knn == %d is not correct; should be 2 <= knn <= 8\n", knn);
        exit(EXIT_FAILURE);
      }
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

  case CITY_STRUCT: case NEAREST_NEIGHBOR: case KNN:

    /* a bigger data set from text file of 115,000 plus cities */
    setOfCities = malloc(sizeof(struct City) * CITIES_SIZE);
    result = loadCities();
    printf("loaded %d records into setOfCities\n", result);

    if (data_set == CITY_STRUCT) {
      result = doPermutations(dtype, checkRoute);
      printf("Number of Permutations: %d\n", result);

    } else if (data_set == NEAREST_NEIGHBOR) {
      struct Route *nearestNeighborRoute = nearestNeighborSearch(dtype);
      printf("Total distance = %.2f\n", nearestNeighborRoute->distance);
      display(nearestNeighborRoute->route, dtype);
      freeup(nearestNeighborRoute);
    } else { /* case KNN */
      struct Route *nearestNeighborRoute = kNN(dtype, knn);
      printf("Total distance = %.2f\n", nearestNeighborRoute->distance);
      display(nearestNeighborRoute->route, dtype);
      freeup(nearestNeighborRoute);
    }
  }

  return EXIT_SUCCESS;

} /* main() */

void
freeup(struct Route *nearestNeighborRoute) {
  /* free allocated memory for the nearestNeighborRoute */
  free(nearestNeighborRoute->route->cities_str); /* path */
  free(nearestNeighborRoute->route); /* nearestNeighborPath */
  free(nearestNeighborRoute);
  free(setOfCities);
}
