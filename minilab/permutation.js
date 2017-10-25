

export default const perm = (args) => {
  const result = [];
  const permute = (arr, memo = []) => {
    let i, current;
    for (i = 0; i < arr.length; i++) {
      current = arr.splice(i, 1);
      if (arr.length === 0) {
        result.push(memo.concat(current));
      }
      permute(arr.slice(), memo.concat(current));
      arr.splice(i, 0, current[0]);
    }
    return result;
  };
  return permute(args);
};

// console.log(perm([0, 1, 2, 3]));
// console.log(perm('a', 'b', 'c', 'd'));
// console.log(perm('corn', 'turkey', 'winter', 'algebra', 'window'));