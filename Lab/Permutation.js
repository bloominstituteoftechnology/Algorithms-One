let arr = [], result = [];
const permute = (input) => {
    let i, j;
    for (i = 0; i < input.length; i++) {
        j = input.splice(i, 1)[0];
        result.push(j);
        if (input.length == 0) {
        arr.push(result.slice());
        }
        permute(input);
        input.splice(i, 0, j);
        result.pop();
    }
  return arr;
};

console.log(permute([1,2,3]));
arr = [], result = [];
console.log(permute(['a', 'b', 'c', 'd']));
arr = [], result = [];
console.log(permute(['corn', 'turkey', 'winter', 'algebra', 'window']));