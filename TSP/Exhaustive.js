const Cities = [
{name:"Denver", x:500, y:500},
{name:"Salt Lake City", x:300, y:500},
{name:"Cheyenne", x:500, y:600},
{name:"Santa Fe", x:500, y:350}
];

const perms = [];
const distance = (city1, city2) => Math.sqrt(Math.pow(city1.x - city2.x, 2) + Math.pow(city1.y - city2.y, 2));

const heapAlg = (arr, n = arr.length) => {
  if (n === 1) perms.push(arr.slice());
  else {
    for (let i = 0; i < n - 1; i++) {
      heapAlg(arr, n - 1);
      n % 2 === 0 ? [arr[i], arr[n -1]] = [arr[n - 1], arr[i]] : [arr[0], arr[n - 1]] = [arr[n - 1], arr[0]];
    }
    heapAlg(arr, n - 1);
  }
};

const exhaust = (perms) => {
  let shortest_trip_length = Number.MAX_VALUE, shortest_trip;
  for (let i = 0; i < perms.length; i++) {
    let current_trip_length = 0;
    for (let j = 1; j < perms[i].length; j++) {
      current_trip_length += distance(perms[i][j], perms[i][j - 1]);
    }
    if (current_trip_length < shortest_trip_length) {
      shortest_trip_length = current_trip_length;
      shortest_trip = perms[i];
    }
  }
  return shortest_trip;
}

const run = (arr) => {
  heapAlg(arr);
  console.log(exhaust(perms));
};

run(Cities);