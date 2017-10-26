const importfile = require('./minilab/importfile');
const TCList = require('./TSP/smallcityObj');
const Cities = TCList.Cities;
const distance = importfile.distance;

// need to have a start point of all things
let BTL = Number.MAX_SAFE_INTEGER;
let BT = [];

for(let h = 0; h < Cities.length; h++) {
  let remainingCities = Cities.slice();
  let cityBT = [];
  let cityBTL = 0;

  cityBT.push(remainingCities[h]);
  remainingCities.splice(h, 1);

  for(let i = remainingCities.length - 1; i > 0; i--) {
    // the above while loop will make the following run until 
    // the length if our temporary cityBT is equal to the original cities.length
    let tempJ = NaN;
    let tempDist = Number.MAX_SAFE_INTEGER;
    // have to initialize and reset tempJ and tempDist everytime
    // setting a temporary J variable so we know where to splice later
    for (let j = 0; j < remainingCities.length; j++) {
      if(distance(cityBT[cityBT.length - 1], remainingCities[j]) < tempDist) {
        // cityBT is initialized with one value in it which was spliced and pushed in. and then after the first case, it takes the last element and calculates distance
        // from last part in the array. array[array.length - 1] is the last element
        tempDist = distance(cityBT[cityBT.length - 1], remainingCities[j]);
        tempJ = j;
        // console.log(remainingCities[tempJ], tempDist);
      }
    }
    // after the above for loop is over, we can now use tempDist and tempJ which have stored the smallest distance index
    // console.log(remainingCities[tempJ], tempDist);
    let city = remainingCities.splice(tempJ, 1);
    // splice out the city that we are "using"
    cityBT.push(city[0]);
    // pushing spliced out city into our cityBT
    cityBTL += tempDist;
    // console.log("cityBT is ");
    // console.log(cityBT);
    // console.log(cityBTL);
    if(remainingCities.length === 1) {
      cityBT.push(remainingCities[0]);
      cityBTL += distance(cityBT[cityBT.length - 2],cityBT[cityBT.length - 1]);
      cityBTL += distance(cityBT[0],cityBT[cityBT.length - 1]);
    }
  }
  // console.log("cityBT is ");
  // console.log(cityBT);
  // console.log(cityBTL);
  if(cityBTL < BTL) {
    // checking to see if this cityBTL(path) is shorter than the saved BTL(path)
    BTL = cityBTL;
    BT = cityBT;
    // if it is, we update our BTL with our newest shortest path
  }
}

console.log('BTL is');
console.log(BTL);
console.log('BT is');
console.log(BT);
