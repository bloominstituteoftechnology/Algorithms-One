/*
 * Heap's Algorithm
 * heapsAlg.c  Version 1.1_a
 * 2017-10-28
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
 * n is  the size of the  current data set; the  data set must be  a list of
 * strings, with the final element in the set a NULL value.  This allows for
 * variable-sized sets to be sent in.  Takes a function pointer as the final
 * argument  as a  callback; this  function makes  a call  with the  current
 * permutation as  its argument.  In  the normal this can  be a call  to the
 * display()  function to  print out  the  permutation, or  it can  be to  a
 * function  that   peforms  some  kind   of  calculation  on   the  current
 * permutation.
 ***************************************************************************/
int
permute(int n, union Permuter *permuter, int ptype, void (*cb)(union Permuter *, int)) {

  static int permutations = 0;
  
  if (n == 1) {
    permutations++;
    (*cb)(permuter, ptype);
  }

  else {
    for (int i = 0; i < n - 1; i++) {
      permute(n - 1, permuter, ptype, cb);
      swap( isodd(n) ? 0 : i, n - 1, permuter, ptype);
    }
    permute(n - 1, permuter, ptype, cb);
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
display(union Permuter *p, int ptype) {
  char **s;
  struct City *c;
  
  int size = p->size;
  switch (ptype) {

  case STRING_ARRAY:
    s = p->cities_arr;
    printf("[");
    for (int i = 0; i < size; i++)
      printf("%s%s", i>0?", ":"",s[i]);
    printf("]\n");

  case CITY_STRUCT:
    c = p->cities_str;
    printf("[");
    for (int i = 0; i < size; i++)
      printf("%s%s, %s", i>0?", ":"", c[i].name, c[i].state);
    printf("]\n");
  }
} /* display() */
