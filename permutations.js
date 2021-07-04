const measureDistance = require('./measureDistance');
const nearestNeighbor = require('./nearestNeighbor');

const fastestRoute = [];
const fast = [Number.MAX_VALUE];

// Finds number of possible permutations for a given data set
const possiblePerm = (arr) => {
  const len = arr.length;
  let possible = len;

  for(let i = len - 1; i > 0; i--) {
    possible *= i;
  }
  console.log('Number of possible routes: ' + possible);
  return len;
}

// Swaps values in an array
const swap = (arr, x, y) => {
  const temp = arr[x];
  arr[x] = arr[y];
  arr[y] = temp;
}

// Prints each possible permutation of a given data set
const perm = (arr, n = 0) => {
  let temp;
  const tarr = [];
  // console.log(arr);

  if (n === 0) {
    n = possiblePerm(arr);
  }

  if (n === 1) {
    // Uncomment next line to print every permutation
    // console.log(arr);
    for(let j = 0; j < arr.length-1; j++) {
      tarr.push(measureDistance(arr[j], arr[j+1]));
    }

    tarr.push(measureDistance(arr[arr.length-1], arr[0]));
    result = tarr.reduce((sum, value) => sum + value);
    // Uncomment next line to print the distance of each route
    // console.log(result);

    if (result < fast[0]) {
      fast[0] = result;
      fastestRoute.length = 0;
      for(let i = 0; i < arr.length; i++) {
        fastestRoute.push(arr[i].name);
      }
    }
  } else {
    for(let i = 0; i < n - 1; i++) {
      perm(arr, n - 1);
      if (n % 2 === 0) {
        swap(arr, i, n - 1);
      } else {
        swap(arr, 0, n - 1);
      }
    }
    perm(arr, n - 1);
  }
}

module.exports = {
  perm: perm,
  fast: fast,
  fastestRoute: fastestRoute
};
