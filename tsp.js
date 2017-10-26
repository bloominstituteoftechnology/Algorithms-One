/******************************************************************
* Imports and implements both solution algorithms
******************************************************************/
const measureDistance = require('./measureDistance');
const Permutations = require('./permutations');
const perm = Permutations.perm;
const fast = Permutations.fast;
const fastestRoute = Permutations.fastestRoute;
const nearestNeighbor = require('./nearestNeighbor');

const cities = [
  {name: "Denver", x: 500, y: 500},
  {name: "Salt Lake City", x: 300, y: 500},
  {name: "Cheyenne", x: 500, y: 600},
  {name: "Santa Fe", x: 500, y: 350},
  // {name: "Minneapolis", x: 1200, y: 1450}
];
// /*
perm(cities);
const nNS = nearestNeighbor(cities);
// console.log(nNS);
console.log('FAST: ' + fast);
console.log('FASTEST ROUTE: ' + fastestRoute);
// */
/*
const nNS = nearestNeighbor(cities);
// console.log(nNS);
perm(cities);
console.log('FAST: ' + fast);
console.log('FASTEST ROUTE: ' + fastestRoute);
*/
