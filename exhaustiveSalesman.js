
const importfile = require('./minilab/importfile');
const perm = importfile.perm;
const Cities = importfile.Cities;

let BTL = Number.MAX_SAFE_INTEGER;
// console.log(BTL);
let BT = [];

// make the permutations based on how many cities there are
const permCities = perm(Cities);
// console.log(permCities);

for(let i = 0; i < permCities.length; i++) {
  // now we have to get the distance from 1 - 2 - 3 - 4 - 1
  let tempDist = 0;
  for(let j = 0; j < permCities[i].length; j++) {
    // add them all up
    if(j + 1 === permCities[i].length) {
      tempDist += distance_between(permCities[i][0], permCities[i][j]);
      if (tempDist <= BTL) {
        // compare to BTL. if smaller, replace BTL. replace BT
        // at the end of this whole loop, return BTL and BT
        BTL = tempDist;
        BT = permCities[i];
        console.log(BTL);
        console.log(BT);
      }
      // console.log(tempDist);
    } else {
    tempDist += distance_between(permCities[i][j], permCities[i][j + 1]);
    // console.log(tempDist);
    }
  }
}
// console.log(BTL);
// console.log(BT);