// Calculate the distance between two points

const measureDistance = (city1, city2) => {
  return Math.round(Math.sqrt((Math.pow((city1.x - city2.x), 2) + (Math.pow((city1.y - city2.y), 2)))));
}

module.exports = measureDistance;
