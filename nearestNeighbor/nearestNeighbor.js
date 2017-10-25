/******************************************************************************
 * Travelling Salesman: Nearest Neighbor
 *
 *
 ******************************************************************************/
'use-strict';
/* eslint no-console: 0 */
const cities = require('./cities');
const Cities = cities.Cities;
const count = require('./heapsAlgo');
const countSet = count.countSet;
const listOfCityIndexes = [];

// Construct array of index numbers from list of City name and coordinates object
for (let i = 0; i < Cities.length; i++) {
  listOfCityIndexes.push(i);
}

// exhaustively enumerate the permutations of the city objects contents
countSet(listOfCityIndexes);
