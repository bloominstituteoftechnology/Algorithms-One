const importfile = require('./minilab/importfile');
const Cities = importfile.Cities;
const distance = importfile.distance;

let BTL = Number.MAX_SAFE_INTEGER;
let BT = [];

for(let h = 0; h < Cities.length; h++) {
  let tempDist = Number.MAX_SAFE_INTEGER;
  let remainingCities = Cities.slice();
  let cityBT = [];
  let cityBTL = 0;

  // needs to change following 2 lines 
  cityBT.push(remainingCities[h]);
  remainingCities.splice(h, 1);

  for(let i = remainingCities.length - 1; i > 0; i--) {
    let tempJ = NaN;
    for (let j = 0; j < remainingCities.length; j++) {
      if(distance(cityBT[cityBT.length - 1], remainingCities[j]) < tempDist) {
        tempDist = distance(cityBT[cityBT.length - 1], remainingCities[j]);
        tempJ = j;
        // console.log(remainingCities[tempJ], tempDist);
      }
    }
    let city = remainingCities.splice(tempJ, 1);
    cityBT.push(city[0]);
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
    BTL = cityBTL;
    BT = cityBT;
  }
}

console.log('BTL is');
console.log(BTL);
console.log('BT is');
console.log(BT);


