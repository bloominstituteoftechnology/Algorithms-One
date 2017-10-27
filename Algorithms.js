const data = require('./usaCitiesJSON/usaCitiesJSON.js');
const compPerm = require('./Computations.js');


const cities = [
  {name:"Denver", x:500, y:500},
  {name:"Salt Lake City", x:300, y:500},
  {name:"Cheyenne", x:500, y:600},
  {name:"Santa Fe", x:500, y:350}
]

const distanceBetween = (city1, city2) => {
  return Math.sqrt(Math.pow((city1.x - city2.x), 2) + Math.pow((city1.y - city2.y), 2))
}
// Exhaustive Algorithm:
const exhaustiveAlgorithm = (cities) => {
  //best_trip_length = MAX
  let bestTripLength = Number.MAX_VALUE;
  //best_trip = []
  let bestTrip = [];
  let permutations = compPerm(cities);
  //for each ordering in the permutations of C:
  for(let i = 0; i < permutations.length; i++) {
    //current_trip_length = 0
    let currentTripLength = 0;
    //for each pair in the ordering:
    for(let j = 0; j < permutations[i].length-1; j++) {
      //current_trip_length += distance_between(current_pair)
      currentTripLength += distanceBetween(permutations[i][j], permutations[i][j+1]);
    }
    //if(current_trip_length < best_trip_length)
    if(currentTripLength < bestTripLength) {       
      //best_trip_length = current_trip_length
      bestTripLength = currentTripLength;
      //best_trip = ordering */
      bestTrip = permutations[i]; 
    }
  }
  const result = [];
  i = 0;
  while(i < bestTrip.length) {
    result.push(cities[bestTrip])
    i++
  }
  return {bestTripLength, result}
}

// Nearest Neighbor search Pseudo Code:
const neighborSearch = (cities, number) => {
  const sites = cities.slice();
  let path = [];
  const pathEnd = sites.length;
  let startValue = number;
  let start = sites.splice(startValue, 1);
  let bestNearest = Number.MAX_VALUE;
  let bestLocation;
  let current = 0;
  let tripLength = 0;
  path.push(start[0]);
  while(path.length < pathEnd) {
    bestNearest = Number.MAX_VALUE;
    for(let i = 0; i < sites.length; i++) {
      current = distanceBetween(sites[i], start[0]);
      if(current < bestNearest) { 
        bestNearest = current
        bestLocation = i;
      }
    }
    tripLength += distanceBetween(start[0], sites[bestLocation])
    start = sites.splice(bestLocation, 1);
    path.push(start[0]);
  }
  return {path, tripLength};  
}

const nearestNeighborSearch = (cities) => {
  let random = Math.floor(Math.random()*cities.length);
  let result = neighborSearch(cities, random);
  return result;
}

const thomsonNeighborSearch = (cities) => {
  let bestPath,
      result,
      currentPath,
      currentDistance;
  let bestDistance = Number.MAX_VALUE;
  for(let i = 0; i < cities.length; i++) {
    result = neighborSearch(cities, i);
    currentPath = result.path;
    currentDistance = result.tripLength;
    if (currentDistance < bestDistance) {
      bestDistance = currentDistance;
      bestPath = currentPath;
    }
  }
  return {bestPath, bestDistance};
}

const arr = data();
const checkTime = arr.splice(0, arr.length);
console.log("Amount is:" + checkTime.length)
console.log(thomsonNeighborSearch(checkTime));
