// let BTL = Number.MAX_SAFE_INTEGER;
// let BT = [];

// // need to have a start point of all things
// for(let h = 0; h < Cities.length; h++) {
//   let remainingCities = Cities.slice();
//   let cityBT = [];
//   let cityBTL = 0;

//   // needs to change following 2 lines 
//   // console.log(cityBT);
//   let city = remainingCities.splice(h, 1);
//   cityBT.push(city[0]);

//   while (cityBT.length !== Cities.length) {
//     // the above while loop will make the following run until the length if our temporary cityBT is equal to the original cities.length
//     let tempJ = NaN;
//     let tempDist = Number.MAX_SAFE_INTEGER;
//     // setting a temporary J variable so we know where to splice later
//     for (let j = 0; j < remainingCities.length; j++) {
//       // running a for loop over everything to check to see which two distances are the shortest
//       if(distance(cityBT[cityBT.length - 1], remainingCities[j]) < tempDist) {
//         // cityBT is initialized with one value in it which was spliced and pushed in. and then after the first case, it takes the last element and calculates distance
//         // from last part in the array. array[array.length - 1] is the last element
//         tempDist = distance(cityBT[cityBT.length - 1], remainingCities[j]);
//         tempJ = j;
//         // make a temp dist variable and a tempJ variable
//         // console.log(remainingCities[j], tempDist);
//       }
//     }
//     // after the above for loop is over, we can now use tempDist and tempJ which have stored the smallest distance index
//     // console.log(remainingCities[tempJ], tempDist);
//     city = remainingCities.splice(tempJ, 1);
//     cityBT.push(city[0]);
//     // console.log(cityBT);
//     cityBTL += tempDist;
//     // console.log("cityBT is ");
//     // console.log(cityBT);
//     // console.log("cityBTL is ");
//     // console.log(cityBTL);
//     if(remainingCities.length === 0) {
//       // console.log(cityBT);
//       cityBTL += distance(cityBT[0], cityBT[cityBT.length - 1]);
//       // console.log("cityBTL is ");
//       // console.log(cityBTL);
//     }
//   }
//   // console.log("cityBT is ");
//   // console.log(cityBT);
//   // console.log(cityBTL);
//   if(cityBTL < BTL) {
//     BTL = cityBTL;
//     BT = cityBT;
//   }
// }

// console.log('BTL is');
// console.log(BTL);
// console.log('BT is');
// console.log(BT);