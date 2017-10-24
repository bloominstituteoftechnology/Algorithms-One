/*Compute all Permutations of the following Sets
    (1, 2, 3)
    ('a', 'b', 'c', 'd')
    ('corn', 'turkey', 'winter', 'algebra', 'window')
*/

const set1 = [1, 2, 3];
const set2 = ['a', 'b', 'c', 'd'];
const set3 = ['corn', 'turkey', 'winter', 'algebra', 'window'];


const computePermutations = (set) => {
  const results = [];
  const permute = (arr, memo = []) => {
    let current;
    for(let i = 0; i < arr.length; i++){
      current = arr.splice(i, 1);
      if (arr.length === 0) {
        results.push(memo.concat(current));
      }
      permute(arr.slice(), memo.concat(current));
      arr.splice(i, 0, current[0]);
    }
   return results;
  }
  return permute(set);
}
console.log(computePermutations(set1));
console.log(computePermutations(set2));
console.log(computePermutations(set3));
