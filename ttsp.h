/* 
 * ttsp.h
 * The Traveling Salesman Problem (TTSP)
 * header file
 * version 0.4_b
 * 2017-10-28
 */

#define MAX_NAME_SIZE 0x20 /* max size of city name */
#define READ "r"
#define CITIES 4 /* number of data items in the original problem */
#define CITIES_SIZE 115475 /* number of cities in the usa city text files */
#define STRING_ARRAY 1 /* type of permuter: array of city names */
#define CITY_STRUCT  2 /* type of permuter: struct City */

struct Coord {
  double x;
  double y;
};
/***************************************************************************
 * Coordinates of a city
 * =========================================================================
 *
 * double x: x-coordinate
 * --------
 *
 * double y: y-coordinate
 * --------
 *
 ***************************************************************************/

struct City {
  char *name;
  char *state;
  struct Coord coord;
};
/***************************************************************************
 * A set of city names along with the city's coordinates
 * =========================================================================
 *
 * char *name: string as city name
 * ----------
 *
 * char *state: string as state associated with city
 * -----------
 *
 * struct Coord: city coordinates
 * ------------
 *
 ***************************************************************************/


union Permuter {
  char **cities_arr;
  struct City *cities_str;
  int size;
} *permuter;
/***************************************************************************
 * Wrapper data structure that can hold either an array of strings as city
 * names, or a set of City's.
 * =========================================================================
 *
 * char **cities_arr: an array of strings as city names
 * -----------------
 *
 * struct City *cities_str: a set of struct City data items
 * -----------------------
 *
 * int size: the number of items in a set
 * --------
 *
 ***************************************************************************/


struct Route {
  union Permuter *route;
  double distance;
};
/***************************************************************************
 * The shortest route between cities
 * =========================================================================
 * 
 * union Permuter *permuter: the permutation representing the shortest route
 * ------------------------
 * 
 * double distance: the shortest distance
 * ---------------
 *
 ***************************************************************************/


int
permute(int, union Permuter *, int, void (*)(union Permuter *, int));
/***************************************************************************
 * main entry into Heap's Algorithm; recursive
 * =========================================================================
 *
 * int: size of current data set
 * ---
 *
 * union Permuter: object that holds the current data set:
 * --------------  char ** | struct City *
 *
 * int: type identifier of the Permuter: STRING_ARRAY |
 * ---                                   CITY_STRUCT
 *
 * (*)(union Permuter *, int): callback function for the permute
 * -------------------------- procedure; int param is type of
 * Permuter
 *
 * RETURN VALUE: number of permutations performed
 * ------------
 *
 ***************************************************************************/

int
doPermutations (int, int, void (*)(union Permuter *, int));
/***************************************************************************
 * main() call into Heap's Algorithm
 * =========================================================================
 *
 * int: size of data set in the permuter object
 * ---
 *
 * int: type of permuter: STRING_ARRAY := char ** | 
 * ---                    CITY_STRUCT  := struct City *
 *                        
 * (*)(union Permuter *, int): the callback function called by permute() 
 * --------------------------  after every permutation; can be one of:
 *    display(), checkRoute(), ordoNothing() at this point.
 *
 * RETURN VALUE: the result returned from permute()
 * ------------
 *
 ***************************************************************************/

int
loadCities(void);
/***************************************************************************
 * Routine loads and merges cities from the two text data files
 * =========================================================================
 *
 * RETURN VALUE: number of cities loaded
 * ------------
 *
 ***************************************************************************/

struct City *
lookup(char *, int);
/***************************************************************************
 * Given a city name, find which data set it belongs to in order to get its
 * coordinates.  Not necessary if a struct City is placed inside a Permuter.
 * =========================================================================
 *
 * char *: city name
 * ------
 *
 * int: size of data set
 * ---
 *
 * RETURN VALUE: struct City * representing the data set with that name
 * ------------
 *
 ***************************************************************************/


void
printCity(struct City *);
/***************************************************************************
 * Pretty print a City data item
 * =========================================================================
 *
 * struct City *: the city to pretty print
 * -------------
 *
 ***************************************************************************/

void
display(union Permuter *, int);
/***************************************************************************
 * Displays the contents of the Permuter in a visually explcit way
 * =========================================================================
 *
 * union Permuter *: the Permuter to display
 * ----------------
 *
 * int: the Permuter's type: STRING_ARRAY | CITY_STRUCT
 * ---
 *
 ***************************************************************************/

double
distance(struct Coord, struct Coord);
/***************************************************************************
 * Given two coordinates, calculates the distance between them
 * =========================================================================
 *
 * struct Coord: (x, y) pair
 * ------------
 *
 * struct Coord: (x, y) pair
 * ------------
 *
 * RETURN VALUE: double as a distance
 * ------------
 ****************************************************************************/

double
roundTrip(union Permuter *, int);
/***************************************************************************
 * Calculates the round trip distance between a set of cities
 * =========================================================================
 * 
 * union Permuter *: the Permuter containing the data
 * ----------------
 *
 * int: the type of Permuter: STRING_ARRAY | CITY_STRUCT
 * ---
 *
 * RETURN VALUE: double as round trip distance
 * ------------
 *
 ***************************************************************************/

void
checkRoute(union Permuter *, int);
/***************************************************************************
 * Calculates the distance between the sets of cities and keeps
 * track of the shortest route; called as a callback if called at all.
 * =========================================================================
 *
 * union Permuter *: the Permuter containing the data
 * ----------------
 *
 * int: type of Permuter: STRING_ARRY | CITY_STRUCT
 * ---
 *
 ***************************************************************************/

void
doNothing(union Permuter *, int);
/***************************************************************************
 * Callback that does nothing
 * =========================================================================
 *
 * union Permuter *:
 * ----------------
 *
 * int: type of Permuter
 * ---
 *
 ***************************************************************************/
