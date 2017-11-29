const fs = require('fs');

const Cities = [
{name:"Denver", x:500, y:500},
{name:"Salt Lake City", x:300, y:500},
{name:"Cheyenne", x:500, y:600},
{name:"Santa Fe", x:500, y:350}
];

const distance = (city1, city2) => Math.sqrt(Math.pow(city1.x - city2.x, 2) + Math.pow(city1.y - city2.y, 2));

// O(n ^ 3) but very accurate
// const nearestNeighbor = (l, n = l.length, ans, short = Number.MAX_VALUE) => {
//   const path = [];
//   let distPath = [];
//   path.push(l[n - 1]);
//   for (let i = 0; i < l.length - 1; i++) {
//       let best_nearest, best_nearest_distance = Number.MAX_VALUE;
//     for (let j = 0; j < l.length; j++) {
//       if (!path.includes(l[j])) {
//         let current = distance(l[j], path[i]);
//         if (best_nearest_distance > current) {
//           best_nearest_distance = current;
//           best_nearest = l[j];
//         }
//       }
//     }
//     path.push(best_nearest);
//     distPath.push(best_nearest_distance);
//   }
//   distPath = distPath.reduce((a, b) => a + b);
//   if (distPath < short) {
//     short = distPath;
//     ans = path;
//   }
//   n--;
//   return n > 1 ? nearestNeighbor(l, n, ans, short) : console.log(ans);
// }

//O(n^2) but not very accurate
const nearestNeighbor = (l) => {
  const path = [];
  path.push(l[0]);
  for (let i = 0; i < l.length - 1; i++) {
      let best_nearest, best_nearest_distance = Number.MAX_VALUE;
    for (let j = 0; j < l.length; j++) {
      if (!path.includes(l[j])) {
        let current = distance(l[j], path[i]);
        if (best_nearest_distance > current) {
          best_nearest_distance = current;
          best_nearest = l[j];
        }
      }
    }
    path.push(best_nearest);
  }
  console.log(path);
}


// let usa = fs.readFileSync('usa115475_cities.txt').toString().split('\n');

// usa = usa.map((city) => {
//   city = city.split(' ').filter(val => val !== '' && val !== '|');
//   return {
//     name: city[3],
//     x: parseFloat(city[0]),
//     y: parseFloat(city[1])
//   }
// });

// nearestNeighbor(usa);

nearestNeighbor(Cities);
