const heapAlg = (array, n = -1) => {
  if (n === 1) console.log(array);
  else {
    if (n === -1) n = array.length;
    for (let i = 0; i < n - 1; i++) {
      heapAlg(array, n - 1);
      if (n % 2 === 0) [array[i], array[n -1]] = [array[n - 1], array[i]];
      else [array[0], array[n - 1]] = [array[n - 1], array[0]];
    }
    heapAlg(array, n - 1);
  }
}


heapAlg([1,2,3]);
heapAlg(['a','b','c','d']);
heapAlg(['corn','turkey','winter','algebra','window', 'kevin']);

