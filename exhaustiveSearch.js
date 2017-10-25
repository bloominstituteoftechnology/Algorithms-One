'use-strict';
/* eslint no-console: 0 */

/******************************************************************************
 * Travelling Salesman: Exhaustive Search, 4 Cities
 *
 *
 ******************************************************************************/

const Cities = [
  {
    name:'Denver',
    x:500,
    y:500},
  {
    name:'Salt Lake City',
    x:300,
    y:500},
  {
    name:'Cheyenne',
    x:500,
    y:600},
  {
    name:'Santa Fe',
    x:500,
    y:350}
];

for (let i = 0; i < Cities.length; i++) {
  console.log(`${Cities[i].name}: ${Cities[i].x}, ${Cities[i].y}`);
}

// Calcukate the distance between two points:
const distanceBetween = (city1, city2) => {
  console.log(`The distance between ${city1.name} & ${city2.name}:`);
  return Math.sqrt(Math.pow(city1.x - city2.x, 2) + Math.pow(city1.y - city2.y, 2));
};

console.log(distanceBetween(Cities[0], Cities[2]));
