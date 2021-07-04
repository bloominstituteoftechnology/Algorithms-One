/*******************************************************************
* Implements the Nearest Neighbor approach to find the shortest path
* between a list of cities
********************************************************************/
const measureDistance = require('./measureDistance');

const nearestNeighbor = (arr) => {
  let start;
  let short;
  let current;
  let index;
  let total;
  const possiblePaths = [];

  for(let i = 0; i < arr.length; i++) {
    const rem = arr.slice();
    let start = arr[i];
    const path = [];
    path.push(start);
    rem.splice(i, 1);
    total = 0;
    while(path.length !== arr.length) {
      short = Number.MAX_VALUE;
      for(let j = 0; j < rem.length; j++) {
        current = measureDistance(path[path.length-1], rem[j]);
        if(current < short) {
          short = current;
          index = j;
        }
      }
      total += short;
      path.push(rem[index]);
      rem.splice(index, 1);
    }
    total += measureDistance(path[path.length-1], path[0]);
    path.push(total);
    possiblePaths.push(path);
  }
  for (let z = 0; z < possiblePaths.length; z++) {
    console.log('Shortest path starting from ' + possiblePaths[z][0].name + ': '
    + JSON.stringify(possiblePaths[z]));
    console.log('Distance of trip starting from ' + possiblePaths[z][0].name +
    ': ' + possiblePaths[z][possiblePaths.length] + '\n');
  }
  return JSON.stringify(possiblePaths);
}

module.exports = nearestNeighbor;
