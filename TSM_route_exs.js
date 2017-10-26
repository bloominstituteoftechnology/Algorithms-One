const Cities = [
{name:"Denver", x:500, y:500},
{name:"Salt Lake City", x:300, y:500},
{name:"Cheyenne", x:500, y:600},
{name:"Santa Fe", x:500, y:350}
]

const distance_function = (city1, city2) => {
  return Math.sqrt(Math.pow(city1.x-city2.x,2) + Math.pow(city1.y-city2.y,2));
}
// best_trip_length = MAX
// best_trip = []
// for each ordering in the permutations of C:
//   current_trip_length = 0
//   for each pair in the ordering:
//     current_trip_length += distance_between(current_pair)
//   if(current_trip_length < best_trip_length)
//     best_trip_length = current_trip_length
//     best_trip = ordering

const TSM_route_exs = (Cities) => {
    let best_trip_length = Number.MAX_VALUE;
    let best_trip = [];
    permute_T = (input) => {
        let current_trip_length = 0;
        for (let i = 0; i < input.length-1; i++) {
        current_trip_length += distance_between(inputs[i], inputs[i+1]);
        }
        current_trip_length += distance_between(inputs[input.length-i], inputs[0]);

        if(current_trip_length < best_trip_length) {
        this.best_trip_length = current_trip_length;
        this.best_trip = input;
        }
    }
}

let arr = [], result = [];
function permute(input) {
    let i, j;
    for (i = 0; i < input.length; i++) {
        j = input.splice(i, 1)[0];
        result.push(j);
        if (input.length == 0) {
        arr.push(result.slice());
        }
    permute(input);
    input.splice(i, 0, j);
    result.pop();
  }
  return arr;
};

const allPermutationsTSP = (input) => {
//   let n = input.length;
  
  permute(input);
  console.log(TSM_route_exs.best_trip_length);
  console.log(TSM_route_exs.best_trip);
}

allPermutationsTSP(Cities);

const fs = require('fs');
let usaTSP = fs.readFileSync('usa115475.tsp').toString().split('\n');

const HEADER_LENGTH = 7;
const NUMBER_OF_CITIES = 11;

let usaCitiesUnformatted = usaTSP.slice(0+HEADER_LENGTH,NUMBER_OF_CITIES+HEADER_LENGTH);

const usaCities = usaCitiesUnformatted.map((city) => {
  const values = city.split(' ');
  return {name: values[0], x: values[1], y: values[2]};
});
// tsp.initialize();
console.log(usaCities);
allPermutationsTSP(usaCities);
