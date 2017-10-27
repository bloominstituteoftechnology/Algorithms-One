const { permutation } = require("./mini")

const cities = [
  {name:"Denver", x:500, y:500},
  {name:"Salt Lake City", x:300, y:500},
  {name:"Cheyenne", x:500, y:600},
  {name:"Santa Fe", x:500, y:350}
]

const distance_between = (city1, city2) => {
  return Math.pow(city1.x - city2.x, 2) + Math.pow(city1.y - city2.y, 2)
}

// TODO: All 4! permutations of Cities:

// const city_list = [cities[0].name, cities[1].name, cities[2].name, cities[3].name]
// const list = permutation(city_list, city_list.length)
// console.log('list: ' + list)

// const list1 = list2 = list3 = list4 = []
// list.forEach((element) => {
//   if (element)
// })

 const denver = [
                  [0,1,2,3],
                  [0,1,3,2],
                  [0,2,1,3],
                  [0,2,3,1],
                  [0,3,1,2],
                  [0,3,2,1]
                ]

const slc = [
              [1,0,2,3],
              [1,0,3,2],
              [1,2,0,3],
              [1,2,3,0],
              [1,3,0,2],
              [1,3,2,0]
            ]

const cheyenne = [
                   [2,0,1,3],
                   [2,0,3,1],
                   [2,1,0,3],
                   [2,1,3,0],
                   [2,3,0,1],
                   [2,3,1,0]
                 ]

const santeFe = [
                  [3,0,1,2],
                  [3,0,2,1],
                  [3,1,0,2],
                  [3,1,2,0],
                  [3,2,0,1],
                  [3,2,1,0]
                ]

const city_list = [denver, slc, cheyenne, santeFe]

// Exhaustive search
const exhaustiveSearch = (list) => {
  let best_trip_length = Number.MAX_VALUE
  let best_trip;
  list.forEach((city, num) =>  { // for each ordering in the permutations of C:
    city.forEach((order) => {
      let current_trip_length = 0
      for (let i = 1; i < order.length; i++) { // for each pair in the ordering:
        current_trip_length += distance_between(cities[order[i-1]], cities[order[i]])
      }
      if (current_trip_length < best_trip_length) {
        best_trip_length = current_trip_length
        best_trip = order
      }
    })
  })
  return best_trip
}

console.log('Best Trip: ' + exhaustiveSearch(city_list))
