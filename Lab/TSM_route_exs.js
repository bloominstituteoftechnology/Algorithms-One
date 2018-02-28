const Cities = [
{name:"Denver", x:500, y:500},
{name:"Salt Lake City", x:300, y:500},
{name:"Cheyenne", x:500, y:600},
{name:"Santa Fe", x:500, y:350}
]

const distance_between = (city1, city2) => {
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

const TSM_route_exs = {
  best_trip_length: Number.MAX_VALUE,
  best_trip : undefined,
  permute_T(input) {
    let current_trip_length = 0;
    for (let i = 0; i < input.length-1; i++) {
      current_trip_length += distance_between(input[i], input[i+1]);
    }
    current_trip_length += distance_between(input[input.length-1], input[0]);
    if(current_trip_length < this.best_trip_length) {
      this.best_trip_length = current_trip_length;
      this.best_trip = input;
    }
  },
  initialize() {
    let best_trip_length = Number.MAX_VALUE;
    let best_trip = undefined;
    }
}

const permute = (n, input) => {
  if(n === 1) {
    // console.log(input);
    // TODO: Call an outside function to compute distance on this input
    if(input[0].x !== undefined) {
      TSM_route_exs.permute_T(input);
    }
    else {
      // just output it if not
      console.log(input);
    }
  }
  else {
    for(let i = 0; i < n-1 ; i++) {
      permute(n - 1, input);
      if(n%2===0) {
        let x = input[i];
        input[i] = input[n-1];
        input[n-1] = x;
      }
      else {
        let x = input[0];
        input[0] = input[n-1];
        input[n-1] = x;
      }
    }
    permute(n - 1, input);
  }
}

const allPermutationsTSP = (input) => {
  let n = input.length;
  
  permute(n, input);
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
TSM_route_exs.initialize();
console.log(usaCities);
allPermutationsTSP(usaCities);
