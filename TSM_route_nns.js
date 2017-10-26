const Cities = [
{name:"Denver", x:500, y:500},
{name:"Salt Lake City", x:300, y:500},
{name:"Cheyenne", x:500, y:600},
{name:"Santa Fe", x:500, y:350}
]

const distance_function = (city1, city2) => {
  return Math.sqrt(Math.pow(city1.x-city2.x,2) + Math.pow(city1.y-city2.y,2));
}
// given a list of cities to be visited l
// path = []
// for each city start in l:
//   add start to path
//   while(path.length != l.length)
//     for each city in l not in path:
//       current = distance(city, start);
//       if(distance < best_nearest)
//         best_nearest_distance = distance
//         best_nearest = city
//     path.add(best_nearest)


const TSM_route_nns = (l) => {
    let path = [];
    for(let i = 0 ; i < l-1; i++) {
        path.push(start);
        while(path.length != l.length) {
            for(let j = 0 ; j < l.length-1; j++) {
                current = distance(city, start);
                if(distance < best_nearest) {
                    best_nearest_distance = distance;
                    best_nearest = city;
                }
            }
            path.add(best_nearest);
        }
    }
}