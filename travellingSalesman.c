/*
 * Traveling Salesman Problem (TSP)
 * 2017-10-25
 * 
 * version 0.2_b
 */

/*
 * Travelling Salesman Problem (TSP)
 * 
 * The  TSP   is  one  of   the  most  famous  problems   in  Computer
 * Science. Imagine a map containing n  cities that need to be visited
 * in an  optimal order. This  problem is  known to be  somewhere less
 * than O(n!) and greater than O(x^n).

 * TSP is one of the most  popular benchmark problems and a great many
 * algorithms have  been tested against  it. For the interest  time of
 * time and  experience, only  two algorithms  are prescribed  in this
 * assignment:

 * Solution Methods:

 * Exhaustive search (Breadth-first or Depth-first search)

 * Exhaustive  search  is  fundamentally   the  most  difficult  case:
 * calculate  the   length  of   every  possible  path,   keeping  the
 * shortest. This  method is guaranteed  to return the  shortest path,
 * but is  intractable for lists of  cities greater than ~20,  as this
 * algorithm is  NP-Complete and O(n!). The  algorithm to exhaustively
 * search involves starting from the  first ordered list of all cities
 * as integers, then  swapping a pair, calculating the  length of that
 * trip, storing  it if l(x) <  B, and repeating until  all swaps have
 * been performed:
 */

#include "./travellingSalesman.h"

struct City {
  char *name;
  int x;
  int y;
} Cities[] = /* Cities[] is a global variable */
  {
    "Denver",
    500,
    500,
    "Salt Lake City",
    300,
    500,
    "Cheyenne",
    500,
    600,
    "Santa Fe",
    500,
    350,
  };

struct Route {
  char **route;
  double distance;
} shortestRoute = { /* shortestRoute is a global variable */
  NULL, -1
};

int
main (int argc, char *argv[]) {

  char *cities[CITIES + 1];

  for (int c = 0; c < CITIES; c++) {
    struct City city = Cities[c];
    cities[c] = city.name;
  }
  cities[CITIES] = NULL;

  permute(CITIES, cities, checkRoute);

  printf("The shortest distance is: %.2lf\n", shortestRoute.distance);
  display(shortestRoute.route);

  return 0;
}

double
distance(char *city1, char *city2) {
  struct City *city1_s = lookup(city1);
  struct City *city2_s = lookup(city2);
  int dist_x = city2_s->x - city1_s->x;
  int dist_y = city2_s->y - city1_s->y;
  double dist = sqrt(dist_x * dist_x + dist_y * dist_y);

  return sqrt(dist_x * dist_x + dist_y * dist_y);
}

void
printCity(struct City *city) {
  printf("%s (%d, %d)\n", city->name, city->x, city->y);
}

struct City *
lookup(char *city) {
  int i = 0;
  while (&Cities[i] != NULL) {
    if (strncmp(Cities[i].name, city, 0xf) == 0)
      return &Cities[i];
    i++;
  }
  fprintf(stderr, "Failed to find city %s\n", city);
  exit(EXIT_FAILURE);
}

double
roundTrip(char **tripset) {
  double roundTripDistance = 0;
  int n = elements(tripset, 1);
  if (n == 1) return 0;

  for (int i = 1; i < n; i++)
    roundTripDistance += distance(tripset[i-1], tripset[i]);
  roundTripDistance += distance(tripset[0], tripset[n-1]);
  return roundTripDistance;
}

void checkRoute(char **tripset) {
  double distance = roundTrip(tripset);
  if (shortestRoute.distance == -1 || distance < shortestRoute.distance) {
    shortestRoute.route = tripset;
    shortestRoute.distance = distance;
  }
}

/*
 * The  distance between  two  cities is:  distance_between =  (city1,
 * city2) ->  { return Math.sqrt((city1.x  - city2.x)^2 +  (city.1.y -
 * city2.y)^2)) }
 *
 * All 4! permutations of Cities:
 */


