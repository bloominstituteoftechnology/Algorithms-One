const permutator = (ArrayLength, Array) => {
  let n = ArrayLength.length;
  if (n < 2) return Array;

  for (let i = 0; i < n - 1; i++) {
    permutator(n -1);
    if (n % 2 === 0) {
      let temp = Array[i];
      Array[i] = Array[n-1];
      Array[n-1] = temp;
    }
    else {
      let temp = Array[0];
      Array[0] = Array[n-1];
      Array[n-1] = temp;
    }
  }
  permutator(n-1, Array)
}

let nums = [1, 2, 3];
let abcs = ['a', 'b', 'c', 'd'];
let words = ['corn', 'turkey', 'winter', 'algebra', 'window'];

permutator(3, nums);