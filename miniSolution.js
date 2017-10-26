const heaps = (num) => { 
  const arr = num.toString().split('');
  const permutations = [];   

  const swap = (a, b) => {
    let temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
  }

  const generate = (n) => {
    if (n === 1) {
      permutations.push(arr.join(''));
    } else {
      for (let i = 0; i != n; ++i) {
        generate(n - 1);
        swap(n % 2 ? 0 : i, n - 1);
      }
    }
  }

  generate(arr.length);
  return permutations;
}