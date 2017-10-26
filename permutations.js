const measureDistance = require('./measureDistance');
const nearestNeighbor = require('./nearestNeighbor');

// Test data sets
// 6 possible permutations
const data1 = [1, 2, 3];
// 24 possible permutations
const data2 = ['a', 'b', 'c', 'd'];
// 120 possible permutations
const data3 = ['corn', 'turkey', 'winter', 'algebra', 'window'];

// Real data
const cities = [
  {name: "Denver", x: 500, y: 500},
  {name: "Salt Lake City", x: 300, y: 500},
  {name: "Cheyenne", x: 500, y: 600},
  {name: "Santa Fe", x: 500, y: 350},
  // {name: "Minneapolis", x: 1200, y: 1450}
];
const fastestRoute = [];
const fast = [Number.MAX_VALUE];

// Finds number of possible permutations for a given data set
const possiblePerm = (arr) => {
  const len = arr.length;
  let possible = len;

  for(let i = len - 1; i > 0; i--) {
    possible *= i;
  }
  console.log('Possible permutations: ' + possible);
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
    console.log(arr);
    for(let j = 0; j < arr.length-1; j++) {
      tarr.push(measureDistance(arr[j], arr[j+1]));
    }

    tarr.push(measureDistance(arr[arr.length-1], arr[0]));
    result = tarr.reduce((sum, value) => sum + value);
    console.log(result);

    if (result < fast[0]) {
      fast[0] = result;
      fastestRoute.length = 0;
      for(let i = 0; i < arr.length; i++) {
        fastestRoute.push(arr[i].name);
      }
      // console.log('SHORT: ' + fast[0]);
      // console.log('SHORTEST ROUTE: ' + fastestRoute);
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
  // console.log('FAST: ' + fast[0]);
  // console.log('FASTEST ROUTE: ' + fastestRoute);
}

// perm(cities);
// console.log("FAST: " + fast[0]);
// console.log("Fastest route: " + fastestRoute);
// nearestNeighbor(cities);
// perm(data1);
// perm(data2);
// perm(data3);

module.exports = {
  perm: perm,
  fast: fast,
  fastestRoute: fastestRoute
};
