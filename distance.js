export let distance_between = (city1, city2) => {
      return Math.sqrt((city1.x - city2.x)^2 + (city1.y - city2.y)^2);
}