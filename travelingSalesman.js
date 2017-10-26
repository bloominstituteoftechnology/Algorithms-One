const cities = [
  {
    name: 'Denver',
    x: 500,
    y: 500,
  },
  {
    name: 'Salt Lake City',
    x: 300,
    y: 500,
  },
  {
    name: 'Cheyenne',
    x: 500,
    y: 600,
  },
  {
    name: 'Santa Fe',
    x: 500,
    y: 350,
  },
];

const distance_function = (city1, city2) => {
    return Math.sqrt(Math.pow(city1.x - city2.x,2) + Math.pow(city1.y - city2.y,2));
}

const tsp = {
    shortest_path_length: Number.MAX_VALUE,
    shortest_path: undefined,
    do_TSP(set) {
        let set_path_length = 0;
        for (let i = 0; i < set.length - 1; i++) {
            set_path_length += distance_function(set[i], set[i + 1]);
        }
        set_path_length += distance_function(set[set.length - 1], set[0]);
        if (set_path_length < this.shortest_path_length) {
            this.shortest_path_length = set_path_length;
            this.shortest_path = set;
        }
    },
    initialize() {
        this.shortest_path_length = Number.MAX_VALUE;
        this.shortest_path = undefined;
    }
}

const heapsAlgorithmTSP = (n, set) => {
    if (n === 1) {
        if (set[0].x !== undefined) {
            tsp.do_TSP(set);
        }
        else {
            console.log(set)
        }
    }
    else {
        for (let i = 0; i < n - 1; i++) {
            heapsAlgorithmTSP(n - 1, set);
            if (n % 2 === 0) {
                let x = set[i];
                set[i] = set[n - 1];
                set[n - 1] = x;
            }
            else {
                let x = set[0];
                set[0] = set[n - 1];
                set[n - 1] = x;
            }
        }
        heapsAlgorithmTSP(n - 1, set);
    }
}

const allPermutationsTSP = (set) => {
    let n = set.length;

    heapsAlgorithmTSP(n, set);
    console.log(tsp.shortest_path_length);
    console.log(tsp.shortest_path);
}

allPermutationsTSP(cities);

const fs = require('fs');
let usaTSP = fs.readFileSync('usa115475.tsp').toString().split('\n');

const HEADER_LENGTH = 7;
const NUMBER_OF_CITIES = 11;

let usaCitiesUnformatted = usaTSP.slice(0+HEADER_LENGTH, NUMBER_OF_CITIES + HEADER_LENGTH);

const usaCities = usaCitiesUnformatted.map((city) => {
    const values = city.split(' ');
    return { name: values[0], x: values[1], y: values[2]};
});
tsp.initialize();
console.log(usaCities);
allPermutationsTSP(usaCities);
