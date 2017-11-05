/* 
 * The Traveling Salesman Problem (TTSP)
 * ttsp.h
 * ------
 * TTSP Header file
 *
 * version 2.0
 * 2017-11-05
 */

#define MAX_NAME_SIZE 0x20 /* max size of city name */
#define READ "r"
#define CITIES_SMALL 4 /* number of data items in the original problem */
#define CITIES_SIZE 115475 /* number of cities in the usa city text files */
#define CITIES_BIG 10 /* number of data items to use from city text files */
#define STRING_ARRAY 1 /* type of permuter: array of city names */
#define CITY_STRUCT  2 /* type of permuter: struct City */
#define NEAREST_NEIGHBOR 3
#define KNN 4

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

struct Dtype {
  int dtype;
  int size;
};
/***************************************************************************
 * Structure to hold the type of data structure being used in the Permuter
 * and the number of data items in the structure.
 * =========================================================================
 *
 * int ptype: STRING_ARRAY | CITY_STRUCT
 * ---------
 *
 * int size: number of data items in the set being permuted
 * --------
 *
 ***************************************************************************/

union Permuter {
  char **cities_arr;
  struct City *cities_str;
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
  int iterations;
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
 * int iterations: the number of iterations performed
 * ______________
 *
 ***************************************************************************/


int
permute(int, union Permuter *, struct Dtype, void (*)(union Permuter *, struct Dtype));
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
 * struct Dtype: structure holding type of data structure and size
 * ------------  type := STRING_ARRAY | CITY_STRUCT
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
doPermutations (struct Dtype, void (*)(union Permuter *, struct Dtype));
/***************************************************************************
 * main() call into Heap's Algorithm
 * =========================================================================
 *
 * struct Ptype: structuret that holds the type of data structure, and the
 * ____________  size of data structure
 * int: type of data structure: STRING_ARRAY := char ** | 
 *                              CITY_STRUCT  := struct City *
 *                        
 * (*)(union Permuter *, int): the callback function called by permute() 
 * --------------------------  after every permutation; can be one of:
 *    display(), checkRoute(), ordoNothing() at this point.
 *
 * RETURN VALUE: the result returned from permute()
 * ------------
 *
 ***************************************************************************/

struct Route *
nearestNeighborSearch(struct Dtype);
/***************************************************************************
 * Routine to calculate nearest neighbor solution to The Traveling Salesman
 * Problem.
 * =========================================================================
 *
 * struct Dtype: structure containing the type of data structure used, and
 * ------------  its size.  Type := STRING_ARRAY | CITY_STRUCT; for the
 *               Nearest Neighbor Problem, will always use a CITY_STRUCT,
 *               but it would be possible to use a STRING_ARRAY.
 *
 * RETURN VALUE: a struct Route containing a Permuter struct City * path
 * ------------  and total distance for Nearest Neighbor path.
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
display(union Permuter *, struct Dtype);
/***************************************************************************
 * Displays the contents of the Permuter in a visually explcit way
 * =========================================================================
 *
 * union Permuter *: the Permuter to display
 * ----------------
 *
 * struct Dtype: structure holding the data structure type and size
 * ------------  type := STRING_ARRAY | CITY_STRUCT
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
roundTrip(union Permuter *, struct Dtype);
/***************************************************************************
 * Calculates the round trip distance between a set of cities
 * =========================================================================
 * 
 * union Permuter *: the Permuter containing the data
 * ----------------
 *
 * struct Dtype: structure holding the type of data structure and size
 * ------------  type := STRING_ARRAY | CITY_STRUCT
 *
 * RETURN VALUE: double as round trip distance
 * ------------
 *
 ***************************************************************************/

void
checkRoute(union Permuter *, struct Dtype);
/***************************************************************************
 * Calculates the distance between the sets of cities and keeps
 * track of the shortest route; called as a callback if called at all.
 * =========================================================================
 *
 * union Permuter *: the Permuter containing the data
 * ----------------
 *
 * struct Dtype: structure holding the type of data structure and size
 * ------------  type := STRING_ARRAY | CITY_STRUCT
 *
 ***************************************************************************/

void
doNothing(union Permuter *, struct Dtype);
/***************************************************************************
 * Callback that does nothing
 * =========================================================================
 *
 * union Permuter *:
 * ----------------
 *
 * struct Dtype:
 * ------------
 *
 ***************************************************************************/

void
exchange(struct City *, struct City *, int, int, int);
/***************************************************************************
 * cities1 is the path being created; cities2 is the source of cities;
 * i is the current length of cities1; j is the city in cities2 to be moved
 * into cities1; k is the length of cities2.  This routine moves a city
 * from cities2 into cities1, then fills in the hole by moving the last
 * city in cities2 into the slot just vacated by k.
 * =========================================================================
 *
 * struct City *: path of cities being created
 * -------------
 *
 * struct City *: source of cities being moved into cities1
 * -------------
 * 
 * int: length of cities1
 * ---
 *
 * int: source city to move into cities1
 * ---
 * 
 * int: length of cities2
 * ---
 *
 ***************************************************************************/

double
nn(struct City *, struct City *, int, int *);
/***************************************************************************
 * The bare nearest neighbor routine; it receives a path with the first city
 * inside, and the remaining cities to iterate over in another structure,
 * and returns the total distance for the shortest route found.
 * =========================================================================
 *
 * struct City *: the shortest path found; originally has the starting city
 * -------------
 * 
 * struct City *: the source cities to find paths to; originally all except
 * -------------  the first city;
 *
 * int: the total number of cities
 * ---
 *
 * int *: iteration count variable
 * -----
 *
 * RETURN VALUE: the shortest distance found for this set of cities
 * ------------
 *
 ***************************************************************************/

struct SortedCity {
  struct City *city;
  int position;
  double distance;
  struct SortedCity *next;
};
/***************************************************************************
 * A node in an array of linked lists of cities sorted by distance from a
 * reference city.  Each entry in the array represents the reference city;
 * each entry in a node represents a city with a distance from the
 * reference; the nodes are sorted by distance from the reference; there
 * is only one node per couple, with the smaller index being the reference
 * in every case.  A list of 1000 cities sorts in under a second; a list of
 * 10,000 cities sorts in about ten minutes; quite O(n^2); consider
 * saving the sorted items on disk.
 * =========================================================================
 *
 * struct City *city: the City struct is the value of this node
 * -----------------
 *
 * int position: the city's position in the main list of cities
 * ------------
 *
 * double distance: this city's distance from its reference city
 * ---------------
 *
 * struct SortedCity *next: a pointer to the next city in the sorted list
 * ----------------------- in reference to the refernce city
 *
 ***************************************************************************/


struct Route *
kNN(struct Dtype, int);
/***************************************************************************
 * Main routine for k-NN algorithm; it first obtains a sorted list for this
 * set of cities; then calculatest the shortest path by k-NN recursive
 * searches.
 * =========================================================================
 *
 * struct Dtype: contains the number of items to place into the list; could
 * ------------  also in the future contain a list of random or picked
 *               cities.
 *
 * int: the value for k in the k-NN search
 * ---
 *
 * RETURN VALUE: a pointer to a Route structure containing the shortest
 * ------------  route and its distance.
 *
 ***************************************************************************/


struct SortedCity **
sortByDistance(struct City *, int);
/***************************************************************************
 * Routine to produce an array of sorted lists of cities, sorted by distance
 * in reference to a reference city; each array entry is a reference city,
 * and the array entry contains a linked list to the other cities in
 * sorted order.  There is only one entry per pair of cities, with the city
 * of the smaller index being first.
 * =========================================================================
 *
 * struct City *: the source list of cities to sort
 * -------------
 *
 * int: the size of the list
 * ---
 *
 * RETURN VALUE: an array of linked lists; each entry in the array is a city
 * ------------  and each city is the head of a sorted linked list by
 *               distance.
 *
 ***************************************************************************/


void
insertCity(struct SortedCity *, struct SortedCity *);
/***************************************************************************
 * Routine to insert a city into a linked list sorted by distance in
 * reference to a reference city.
 * =========================================================================
 *
 * struct Sorted City *: The head of the linked list into which the value
 * --------------------  is to be inserted
 *
 * struct SortedCity *: The node to insert into the linked list.
 * -------------------
 *
 ***************************************************************************/


void
printSortedCities(struct SortedCity **, int);
/***************************************************************************
 * A debugging tool; it prints the array of linked lists.
 * =========================================================================
 * 
 * struct SortedCity **: the array of linked lists
 * --------------------
 * 
 * int: size of array
 * ---
 *
 ***************************************************************************/


void
printPath(struct City *, int);
/***************************************************************************
 * Prints a set of cities in a path
 * =========================================================================
 * struct City *: the path to print
 * -------------
 *
 * int: size of path
 * ---
 *
 ***************************************************************************/


void
kNNRecursive(int,
             struct City *, int, struct City *, int,
             struct Route *, int, struct SortedCity **);
/***************************************************************************
 * Recurses into a solution; at the base case (right is length zero), it
 * calculates the overall route distance and stores the smallest route found
 * so far.
 * =========================================================================
 *
 * int: current value of knn (less one)
 * ---
 *
 * struct City *: left path; current route being built up
 * -------------
 *
 * int: left size
 * ---
 *
 * struct City *: right path; source cities left for building a path
 * -------------
 *
 * int: right size
 * ---
 *
 * struct Route *: best route found so far
 * --------------
 *
 * int: best route size
 * ---
 *
 * struct Sorted City **: array of linked lists containing sorted cities by
 * ---------------------  from a reference city.
 *
 ***************************************************************************/

double
calcRouteDistance(struct City *, int);
/***************************************************************************
 * Given a path of cities, calculates the round trip distance
 * =========================================================================
 *
 * struct City *: path of cities
 * -------------
 *
 * int: size
 * ---
 *
 * RETURN VALUE: distance
 * ------------
 *
 ***************************************************************************/

void
getKthNeighbor(int,
               struct City *, int *,
               struct City *, int *,
               struct SortedCity **, int);
/***************************************************************************
 * Given a city and a knn value, find that city's kth neighbor from the list
 * of sorted cities.
 * =========================================================================
 *
 * int: knn value (less one)
 * ---
 *
 * struct City *: path left; the reference city is the last city in the path
 * -------------
 *
 * int: size of left
 * ---
 *
 * struct City *: path right; the source of cities to choose the kth neighbor
 * -------------  from
 *
 * int: size of right
 * ---
 *
 * struct SortedCity **: array of linked lists to find the kth neighbor
 * --------------------  without a lot of searching and sorting
 *
 * int: size of array
 * ---
 *
 ***************************************************************************/

int
compareCities(struct City *, struct City *);
/***************************************************************************
 * Given two cities, determine whether they are the same or not
 * =========================================================================
 *
 * struct City *: city 1
 * -------------
 *
 * struct City *: city 2
 * -------------
 *
 * RETURN VALUE: 1 if two cities are the same; 0 if not
 * ------------
 *
 ***************************************************************************/

int
findCityInSortedCities(struct City *, struct SortedCity **, int);
/***************************************************************************
 * Looks for a city in the SortedCity array; returns the city's index when
 * found.
 * =========================================================================
 *
 * struct City *: the city to look for
 * -------------
 *
 * struct SortedCity **: the array of sorted cities
 * --------------------
 *
 * int: the size of the array
 * ---
 *
 * RETURN VALUE: the index of the found city; a fatal error if the city is
 * ------------  not found.
 *
 ***************************************************************************/

int
findCityInPath(struct City *, struct City *, int);
/***************************************************************************
 * Looks for a city in a path
 * =========================================================================
 *
 * struct City *: the city to look for
 * -------------
 *
 * struct City *: the path to look in
 * -------------
 *
 * int: the size of the path
 * ---
 *
 * RETURN VALUE: the index of the path in which the city is found, or -1 if
 * ------------  the city was not found
 *
 ***************************************************************************/

struct City *
deepCityCopy(struct City *, int);
/***************************************************************************
 * Makes a deep copy of a City path (each City is separately copied) to
 * avoid aliasing the individual cities.
 * =========================================================================
 *
 * struct City *: pointer to a City path to be copied
 * -------------
 *
 * int: size of the path to be copied
 * ---
 *
 * RETURN VALUE: pointer to a new City path copied from the original
 * ------------
 *
 ***************************************************************************/

void
deepCityFree(struct City *, int);
/***************************************************************************
 * Frees a City path, including each City inside it
 * =========================================================================
 *
 * struct City *: the City path to free
 * -------------
 *
 * int: size
 * ---
 *
 ***************************************************************************/
