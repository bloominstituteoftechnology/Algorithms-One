/*
 * Heap's Algorithm
 * heapsAlg.c  Version 2.0
 * 2017-10-29
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ttsp.h"

void
swap(int, int, union Permuter *, int);
/*****************************************************************/

int
isodd(int);
/*****************************************************************/


/***************************************************************************
 * Heap's Algorithm for permuting a set;
 * =====================================
 * n is the size  of the current data set; the data  set can be either
 * an array of strings, in which case display only should be chosen as
 * the callback,  or it  can be  a set  of city  and state  names with
 * coordinates housed  in an array  of City struct elements  that will
 * allow efficient distance calculations.  The callback checkRoute can
 * be used  to solve  the Traveling Salesman  Problem by  passing only
 * pointers.   Takes a  function pointer  as the  final argument  as a
 * callback; this function  makes a call with  the current permutation
 * as its argument.
 ***************************************************************************/
int
permute(int n, union Permuter *permuter, struct Dtype dtype, void (*cb)(union Permuter *, struct Dtype)) {

  static int permutations = 0;
  
  if (n == 1) {
    permutations++;
    (cb)(permuter, dtype);
  }

  else {
    for (int i = 0; i < n - 1; i++) {
      permute(n - 1, permuter, dtype, cb);
      swap( isodd(n) ? 0 : i, n - 1, permuter, dtype.dtype);
    }
    permute(n - 1, permuter, dtype, cb);
  }
  return permutations;
} /* permute() */


/***************************************************************************
 * swaps two positions in a character array
 ***************************************************************************/
void
swap(int a, int b, union Permuter *p, int ptype) {
  char **s; char *t;
  struct City *c; struct City tc;
  
  switch (ptype) {
  case STRING_ARRAY:
    s = p->cities_arr;
    t = s[a];
    s[a] = s[b];
    s[b] = t;
    p->cities_arr = s;
    break;

  case CITY_STRUCT:
    c = p->cities_str;
    tc = c[a];
    c[a] = c[b];
    c[b] = tc;
    p->cities_str = c;
    break;
  }
} /* swap */


/***************************************************************************
 * determines whether an integer is odd
 ***************************************************************************/
int
isodd(int a) {
  return (int)fmod((double)a, 2.0);
} /* isodd() */


/***************************************************************************
 * this will print out the contents of the data set for visual inspection
 ***************************************************************************/
void
display(union Permuter *p, struct Dtype dtype) {
  char **s;
  struct City *c;
  
  int size = dtype.size;
  switch (dtype.dtype) {

  case STRING_ARRAY:
    s = p->cities_arr;
    printf("[");
    for (int i = 0; i < size; i++)
      printf("%s%s", i>0?", ":"",s[i]);
    printf("]\n");
    break;

  case CITY_STRUCT: case NEAREST_NEIGHBOR:
    c = p->cities_str;
    printf("[");
    for (int i = 0; i < size; i++)
      printf("%s%s, %s", i>0?", ":"", c[i].name, c[i].state);
    printf("]\n");
    break;
  }
} /* display() */
