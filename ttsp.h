/* 
 * ttsp.h
 * The Traveling Salesman Problem (TTSP)
 * header file
 * version 0.4_a
 * 2017-10-26
 */

struct City {
  char *name;
  char *state;
  double x;
  double y;
};

struct Route {
  char **route;
  double distance;
};

#define MAX_NAME_SIZE 0x20 /* max size of city name */
#define CITIES 4 /* number of data items in the original problem */
#define CITIES_SIZE 115475
#define READ "r"

int
permute(int, char **, void (*)(char **));

int
doPermutations (int, void (*)(char **));

int
loadCities(void);

int
elements(char **, int);

void
printCity(struct City *);

void
display(char **);

void
checkRoute(char **);

void
doNothing(char **);
