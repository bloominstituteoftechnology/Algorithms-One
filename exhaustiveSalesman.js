
// import perm from './minilab/permutation';

const perm = (args) => {
  const result = [];
  const permute = (arr, memo = []) => {
    let i, current;
    for (i = 0; i < arr.length; i++) {
      current = arr.splice(i, 1);
      if (arr.length === 0) {
        result.push(memo.concat(current));
      }
      permute(arr.slice(), memo.concat(current));
      arr.splice(i, 0, current[0]);
    }
    return result;
  };
  return permute(args);
};


distance_between = (city1, city2) => {
  return Math.sqrt(Math.pow((city1.x - city2.x), 2) + Math.pow((city1.y - city2.y), 2));
}


const Cities = [
  {name:"Salt Lake City", x:300, y:500},
  {name:"Santa Fe", x:500, y:350},
  {name:"Denver", x:500, y:500},
  {name:"Cheyenne", x:500, y:600},
  // {name: "New York", x:1000, y: 1000},
];

let BTL = 999999999999;
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