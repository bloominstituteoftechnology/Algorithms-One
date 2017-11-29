const cities = [
    {name:"Denver", x:500, y:500},
    {name:"Salt Lake City", x:300, y:500},
    {name:"Cheyenne", x:500, y:600},
    {name:"Santa Fe", x:500, y:350}
  ]
  
  const distance_between = (city1, city2) => {
    return Math.pow(city1.x - city2.x, 2) + Math.pow(city1.y - city2.y, 2)
  }
  
  // Nearest Neighbor search
  const nearestNeighbor = (list) => {
    let path = []
    let best_nearest, current
    let list_length = list.length
    let start = 0
    path = list.splice(start, 1)
    while (path.length < list_length) {
      let best_nearest_distance = Number.MAX_VALUE
      for (let i = 0; i < list.length; i++) {
        current = distance_between(list[i], path[start])
        if (current < best_nearest_distance) {
          best_nearest_distance = current
          best_nearest = i
        }
      }
      path.push(list[best_nearest])
      list.splice(best_nearest, 1)
    }
    return path
  }
  
  console.log('Path: ' + JSON.stringify(nearestNeighbor(cities), null, 4))
  