/*
 * permsHeap.c
 * Permutations by Heap's Algorithm
 * 2017-10-24
 * 
 */

#include "./heapsAlg.h"

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
    char** p = permute(cols, S[row]);
    printf("count = %d\n\n", count);
    display(p);
  }
}

