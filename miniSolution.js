const set1 = [1,2,3,4];
const set2 = ['a', 'b', 'c', 'd'];
const set3 = ['banana', 'script', 'rocks', 'cs1'];

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