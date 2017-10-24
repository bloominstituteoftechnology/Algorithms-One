'use-strict';
/* eslint no-console: 0 */

/******************************************************************************
 * Travelling Salesman: Exhaustive Search, 4 Cities
 *
 *
 ******************************************************************************/

const Cities = {
  Denver: {x: 500, y:500},
  SaltLakeCity: {x: 300, y:500},
  Cheyenne: {x: 500, y:600},
  SantaFe: {x: 500, y:350}
};

console.log('Denver:       ', Cities.Denver.x, Cities.Denver.y);
console.log('SaltLakeCity: ', Cities.SaltLakeCity.x, Cities.SaltLakeCity.y);
console.log('Cheyenne:     ', Cities.Cheyenne.x, Cities.Cheyenne.y);
console.log('SantaFe:      ', Cities.SantaFe.x, Cities.SantaFe.y);

// Calcukate the distance between two points:
const distanceBetween = (city1, city2) => {
  console.log(`The distance between ${city1} & ${city2}:`);
  return Math.sqrt(Math.pow(city1.x - city2.x, 2) + Math.pow(city1.y - city2.y, 2));
};

console.log(distanceBetween(Cities.Denver, Cities.Cheyenne));
