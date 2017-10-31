#! /usr/bin/env bash

# filter to make all data space-separated to enable scanning in c code;
# makes all cities one word by turning spaces into underscores

perl -F'/\s\|\s/' -ae '$F[0] =~ s/^ //; $F[0] =~ s/[[:space:]]{2,}/ /; $F[1] =~ s/\s/_/g; $F[2] =~ s/\s/_/g; s/^\s//; print "@F"' usa115475_cities.txt > usa115475_cities_a.txt
