/*
 * permsHeap.h
 * Header file for Heap's Algorithm
 * 2017-10-25
 *
 */

#ifndef HEAPSALG
#define HEAPSALG

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

void permute(int, char **, void (*fn)(char **));
void swap(int, int, char **);
int isodd(int);
int elements(char **, int);
void display(char **);

#define MAXSIZE 10 /* largest number of elements allowed in a row */
int count; /* count of permutations for a set */

#endif
