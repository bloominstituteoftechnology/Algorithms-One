/*
 * Heap's Algorithm
 * heapsAlg.c
 * 2017-10-25
 *
 */

#include "./heapsAlg.h"

/***************************************************************************
 * Heap's Algorithm for permuting a set
 ***************************************************************************/
void
permute(int n, char **s) {
  if (n == 1)
    display(s);

  else {
    for (int i = 0; i < n - 1; i++) {

      permute(n - 1, s);

      swap( isodd(n) ? 0 : i, n - 1, s);
    }
    permute(n - 1, s);
  }
}
/***************************************************************************/

void
swap(int a, int b, char **s) {
  char *t = s[a];
  s[a] = s[b];
  s[b] = t;
}

int
isodd(int a) {
  return (int)fmod((double)a, 2.0);
}

/* this will  return the number of  elements of both rows  and columns
 * provided the size represents the  size of an element, i.e., MAXSIZE
 * (10) for rows and 1 for columns */
int
elements(char *s[], int size) { /* size represents the max size of an element */
  int i = 0;
  while (s[i++ * size] != NULL)
    ;
  return i - 1;
}

void
display(char *s[]) {
  count++;
  int size = elements(s, 1);
  printf("[");
  for (int i = 0; i < size; i++)
    printf("%s%s", i>0?", ":"",s[i]);
  printf("]\n");
}
