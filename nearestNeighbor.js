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
    // console.log('BEFORE++++++++++: ' + JSON.stringify(possiblePaths));
    path.push(start);
    // console.log('AFTER+++++++++++: ' + JSON.stringify(possiblePaths));
    rem.splice(i, 1);
    total = 0;
    // console.log('Path 21: ' + JSON.stringify(path));
    // console.log('Rem 22: ' + JSON.stringify(rem));
    // console.log('PRE WHILE ====== ' + JSON.stringify(possiblePaths));
    while(path.length !== arr.length) {
      // console.log(JSON.stringify(arr));
      // console.log("IMPORTANT!!!!!! " + path.length + ' ' + arr.length);
      short = Number.MAX_VALUE;
      // console.log('Short 27: ' + short);
      for(let j = 0; j < rem.length; j++) {
        current = measureDistance(path[path.length-1], rem[j]);
        // console.log('Current 30: ' + current);
        if(current < short) {
          short = current;
          // console.log('Short 33: ' + short);
          index = j;
          // console.log('Index 35: ' + index);
        }
      } // END FOR 2=================================
      total += short;
      // console.log('Total 39: ' + total);
      path.push(rem[index]);
      // console.log('Path 41: ' + JSON.stringify(path));
      rem.splice(index, 1);
      // console.log('Rem 43: ' + JSON.stringify(rem));
    } // END WHILE===================================
    total += measureDistance(path[path.length-1], path[0]);
    path.push(total);
    // console.log('Path 46: ' + JSON.stringify(path));
    possiblePaths.push(path);
    // console.log('PossiblePaths 48: ' + JSON.stringify(possiblePaths));
  } // END FOR 1 ===================================
  for (let z = 0; z < possiblePaths.length; z++) {
    console.log('PossiblePaths: ' + JSON.stringify(possiblePaths[z]));
  }
  return JSON.stringify(possiblePaths);
} // END FUNCTION

module.exports = nearestNeighbor;
