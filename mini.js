'use-strict';
/* eslint no-console: 0 */
/******************************************************************************
 * Mini lab
 * Write code in your language of choice to generate all permutations of the following sets:
 * (1, 2, 3)
 * ('a', 'b', 'c', 'd')
 * ('corn', 'turkey', 'winter', 'algebra', 'window')
 * e.g.
 * !3: 123, 132, 213, 231, 312, 321                    = 6 permutations
 * !4: abcd, abdc, acbd, acdb, adbc, adcb, etc...      = 24 permutations
 * !5: (corn, turkey, winter, algebra, window),
 *     (corn, turkey, winter, window, algebra), etc... = 120 permutations
 ******************************************************************************/

const perm = (...args) => {
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

console.log(perm());
console.log(perm('Scooby Snacks'));
console.log(perm(1, 2, 3));
console.log(perm('a', 'b', 'c', 'd'));
console.log(perm('corn', 'turkey', 'winter', 'algebra', 'window'));


// const allAnagrams = (str, start = '') => {
//   if (str.length === 1) return [start + str];
//   const anagrams = [];
//
//   for (let i = 0; i < str.length; i++) {
//     const result = allAnagrams(str.substr(0, i) + str.substr(i + 1), str[i]);
//     for (let j = 0; j < result.length; j++) {
//       anagrams.push(start + result[j]);
//     }
//   }
//   return anagrams;
// };
//
// console.log(allAnagrams('abcd'));
