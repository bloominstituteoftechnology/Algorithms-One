/*
 * Traveling Salesman Problem (TSP)
 * 2017-10-25
 *
 * Version 0.3_e
  */

#include "./travellingSalesman.h"

struct Route shortestRoute =
  {
    NULL,
    -1
  };

int
main (int argc, char *argv[]) {

  /* cities will contain the original set of names (city,st) to be permuted */
  char *cities[CITIES + 1];

  /* fill cities with names, states */
  for (int c = 0; c < CITIES; c++) {
    cities[c] = malloc(sizeof(char) * MAX_NAME_SIZE);

    /* city contains one of the cities from the set; need to extract the name and state from it */
    /* TODO: factor out the global variable CitiesSmallSet to use any set sent in */
    struct City city = CitiesSmallSet[c]; /* small data set, now contained in the header file */

    /* city contains both a city name and state; catenate them together to avoid duplicate names */
    /* combination cannot be larger than MAX_NAME_SIZE */
    strncat(cities[c], city.name, strlen(city.name));
    strncat(cities[c], ",", 1);
    strncat(cities[c], city.state, 2);
  }
  cities[CITIES] = NULL; /* necessary for data structure to work inside permute */

  /* TODO: factor out CITIES global variable to work with any size set */
  permute(CITIES, cities, checkRoute);

  printf("The shortest distance is: %.2lf\n", shortestRoute.distance);
  display(shortestRoute.route);

  /* TODO: need to free all malloced memory */
  return 0;
}

double
distance(char *city1, char *city2) {
  struct City *city1_s = lookup(city1);
  struct City *city2_s = lookup(city2);
  double dist_x = city2_s->x - city1_s->x;
  double dist_y = city2_s->y - city1_s->y;
  double dist = sqrt(dist_x * dist_x + dist_y * dist_y);

  return sqrt(dist_x * dist_x + dist_y * dist_y);
}

void
printCity(struct City *city) {
  printf("%s, %s (%f, %f)\n", city->name, city->state, city->x, city->y);
}

struct City *
lookup(char *city) { /* city will be string with city name and state concatenated together */
  int i = 0;

  while (&CitiesSmallSet[i] != NULL) {
    /* extract the city name and the state for comparison */
    char real_city[MAX_NAME_SIZE], real_state[3];
    memset(real_city, 0, MAX_NAME_SIZE);
    memset(real_state, 0, 3);
    strncpy(real_city, city, (size_t)(strlen(city) - 3)); /* avoid the comma */
    strncat(real_state, city + (strlen(city) - 2), (size_t)2);

    /* now find a match for both city and state */
    if (strncmp(CitiesSmallSet[i].name, real_city, MAX_NAME_SIZE) == 0 && strncmp(CitiesSmallSet[i].state, real_state, 2) == 0)
      return &CitiesSmallSet[i];
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




