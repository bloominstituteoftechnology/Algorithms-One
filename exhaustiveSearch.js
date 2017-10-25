/******************************************************************************
 * Travelling Salesman: Exhaustive Search, 4 Cities
 *
 *
 ******************************************************************************/
'use-strict';
/* eslint no-console: 0 */
const cities = require('./cities');
const Cities = cities.Cities;
const distance = require('./distance');
const distanceBetween = distance.distanceBetween;
const count = require('./heapsAlgo');
const countSet = count.countSet;
const MAX_SAFE_NUMBER = 9007199254740991;

console.log('max safe number:', MAX_SAFE_NUMBER);

// console log each city's coordinates
for (let i = 0; i < Cities.length; i++) {
  console.log(`${Cities[i].name}: ${Cities[i].x}, ${Cities[i].y}`);
}

// console log the distance between two cities
console.log(distanceBetween(Cities[0], Cities[2]));

// enumerate the permutations
console.log(countSet([0, 1, 2, 3]));
