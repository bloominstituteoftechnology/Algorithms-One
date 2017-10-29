/*
 * loadCities.c
 * 2017-10-28
 *
 * Version 0.4
 *
 * Load usa115475_cities_a.txt and usa115475.tsp
 * format for use by Traveling Salesman Problem
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "ttsp.h"

#define CITIES_FILE "./TSP/usa115475.tsp"
/* NOTE: usa115475_cities.txt must first be processed by cityfilter.pl
         to produce usa115475_cities_a.txt so that the sscan library
         function will work properly */
#define CITIES_NAMES "./TSP/usa115475_cities_a.txt"
#define BUFSIZE 100
#define READ "r"
extern struct City *setOfCities;
extern int errno;


void
findFirstCity(FILE *);
/******************************************************************/

int
getCity(FILE *, char *);
/******************************************************************/

void
fillCity(char *, char *, struct City *);
/******************************************************************/

void
printCityInfo(struct City *);
/******************************************************************/


int
loadCities(void) {
  FILE *cities, *cities_names;
  char city[BUFSIZE];
  char city_name[BUFSIZE];
  int result, city_index;

  struct City *cityStr;

  /* open the two files for reading */
  cities = fopen(CITIES_FILE, READ);
  cities_names = fopen(CITIES_NAMES, READ);
  if (cities == NULL || cities_names == NULL) {
    fprintf(stderr, "Failed to open cities or cities_names\n");
    exit(EXIT_FAILURE);
  }

  /* position the file pointers to the beginning of the data */
  findFirstCity(cities);
  findFirstCity(cities_names);

  /* read city data and place the city's name, state, and
   * coordinates in a structure */

  city_index = 0;

  /* add city data to structs */
  while ((result = getCity(cities, city)) == 1) {
    /* get a city name line */
    result = getCity(cities_names, city_name);
    if (result != 1) {
      fprintf(stderr, "Error reading cities_names\n");
      exit(EXIT_FAILURE);
    }
  
    cityStr = malloc(sizeof(struct City));
    fillCity(city, city_name, cityStr);
    setOfCities[city_index++] = *cityStr;
  }

  if (result == -1)
    fprintf(stderr, "Success\n");
  else
    fprintf(stderr, "Error\n");

  printf("successfully loaded city data\n");

  return city_index;

  /* NOTE: free city data at conclusion */

} /***************************************************/



void
findFirstCity(FILE *fp) {
  char line[BUFSIZE];
  char *rl;
  char c;

  while (1) {
    clearerr(fp);
    c = getc(fp);
    if (c == EOF) {
      if (ferror(fp))
        fprintf(stderr, "Error %d\n", errno);
      else if (feof(fp))
        fprintf(stderr, "Reached eof too early\n");
        
      fprintf(stderr, "Error trying to find the first city (getc)\n");
      exit(EXIT_FAILURE);
    }
    if (isspace(c))
      continue;
    if (isdigit(c)) {
      ungetc(c, fp);
      return;
    }
    /* putchar(c); */
    rl = fgets(line, BUFSIZE, fp);
    /* printf("%s", line); */
    if (rl == NULL) {
      fprintf(stderr, "Error trying to find the first city (fgets)\n");
      exit(EXIT_FAILURE);
    }
  }
}



int
getCity(FILE *fp, char *city) {
  char *rl = fgets(city, BUFSIZE, fp);
  if (rl == NULL) {
    if (feof(fp)) {
      return EOF;
    }
    if (ferror(fp)) {
      fprintf(stderr, "Error reading a city line: %d\n", errno);
      exit(EXIT_FAILURE);
    }
    fprintf(stderr, "Some strange error\n");
    exit(EXIT_FAILURE);
  }
  return 1;
}

void
fillCity(char *city, char *city_name, struct City *city_str) {
  int c, l;
  double x1, y1, x2, y2;
  struct Coord city_coord;
  char name[BUFSIZE], county[BUFSIZE], state[2];
  char *n, *s;

  /* read the next line from city file */
  if ((c = sscanf(city, "%d %lf %lf\n", &l, &x1, &y1)) != 3) {
    fprintf(stderr, "Failed to read three numbers in city\n");
    exit(EXIT_FAILURE);
  }
  city_coord.x = x1;
  city_coord.y = y1;

  /* read the nextline from city_name file; the cities must be the same */
  if ((c = sscanf(city_name, "%lf %lf %s %s %s", &x2, &y2, name, county, state)) != 5) {
    fprintf(stderr, "Failed to read five numbers in city names; read %d %s\n", c, name);
    exit(EXIT_FAILURE);
  }

  /* check coordinates for equality */
  if (fabs(x1 - x2) > .01) {
    fprintf(stderr, "Different coordinates in line %d, city and state: %s, %s\n", l, name, state);
  }

  n = malloc(strlen(name));
  s = malloc(2);
  /* TODO: free n & s */
  strcpy(n, name);
  strcpy(s, state);

  city_str->name = n;
  city_str->state = s;
  city_str->coord = city_coord;
}

void
printCityInfo(struct City *city) {
  printf("%s, %s (%f, %f)\n", city->name, city->state, city->coord.x, city->coord.y);
}
