/*
 * permsHeap.c
 * Permutations by Heap's Algorithm
 * 2017-10-24
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

void permute(int, char **);
void swap(int, int, char **);
int isodd(int);
int elements(char **, int);
void display(char **);

#define MAXSIZE 10 /* largest number of elements allowed in a row */
int count; /* count of permutations for a set */

int main(int argc, char *argv[]) {
  char *S[][MAXSIZE] = {
    {"a", "b", "c", NULL},
    {"va", "wb", "xc", "yd", "ze", NULL},
    {"corn", "turkey", "winter", "algebra", "window", "book", NULL},
    {NULL}
  };

  int rows = elements(*S, MAXSIZE); /* *S represents the address of the first element in the first row */

  for (int row = 0; row < rows; row++) { /* iterate over the arrays and permute each one */
    char **set = S[row]; /* set represents a pointer to the row'th array */
    int cols = elements(set, 1); /* cols represents the actual number of elements in this row */

    count = 0;
    permute(cols, S[row]);
    printf("count = %d\n\n", count);
  }
}

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
