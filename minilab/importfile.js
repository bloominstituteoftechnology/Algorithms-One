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

const Cities = [
  {name:"Salt Lake City", x:300, y:500},
  {name:"Denver", x:500, y:500},
  {name:"Cheyenne", x:500, y:600},
  {name:"Santa Fe", x:500, y:350},
  // {name: "New York", x:967, y: 789},
  // {name: "San Fran", x: 0, y: 250},
  // {name: "Atlantis", x: -335, y: -391},
  // {name: "Asgard", x: 777, y: 777},
  // {name: "Ryan Hamblin's House", x: 123, y: 456},
  // {name: "Lambda School HQ", x: 0, y: 0},
  // // doesnt work after this
  // {name: "???", x: 676, y: 51},
];

const distance = (city1, city2) => {
  return Math.sqrt(Math.pow((city1.x - city2.x), 2) + Math.pow((city1.y - city2.y), 2));
}

module.exports = {
  perm,
  Cities,
  distance,
}
// console.log(perm([0, 1, 2, 3]));
// console.log(perm('a', 'b', 'c', 'd'));
// console.log(perm('corn', 'turkey', 'winter', 'algebra', 'window'));