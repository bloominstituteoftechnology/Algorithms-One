/*
 * Traveling Salesman Problem (TSP)
 * 2017-10-25
 *
 * Version 0.3_c
  */

#include "./travellingSalesman.h"

struct City Cities[] = /* Cities[] is a global variable */
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

struct Route shortestRoute =
  {
    NULL,
    -1
  };

int
main (int argc, char *argv[]) {

  char *cities[CITIES + 1];

  for (int c = 0; c < CITIES; c++) {
    struct City city = Cities[c];
    /* city contains both a city name and state; catenate them together to avoid duplicate names */
    strncat(cities[c], city.name, strlen(city.name)); /* don't want to modify the original */
    strncat(cities[c], ",", 1);
    strncat(cities[c], city.state, 2);
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
  double dist_x = city2_s->x - city1_s->x;
  double dist_y = city2_s->y - city1_s->y;
  double dist = sqrt(dist_x * dist_x + dist_y * dist_y);

  return sqrt(dist_x * dist_x + dist_y * dist_y);
}

void
printCity(struct City *city) {
  printf("%s, %s (%d, %d)\n", city->name, city->state, city->x, city->y);
}

struct City *
lookup(char *city) { /* city will be string with city name and state concatenated together */
  int i = 0;
  while (&Cities[i] != NULL) {
    /* extract the city name and the state for comparison */
    char *real_city, *real_state;
    strncat(real_city, city, strlen(city - 3)); /* avoid the comma */
    strncat(real_state, city + strlen(city - 2), 2);

    /* now find a match for both city and state */
    if (strncmp(Cities[i].name, real_city, 0xf) == 0 && strncmp(Cities[i].state, real_state, 2) == 0)
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




