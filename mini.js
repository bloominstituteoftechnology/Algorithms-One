/*
Mini lab
Write code in your language of choice to generate
all permutations of the following sets:
(1, 2, 3)
('a', 'b', 'c', 'd')
('corn', 'turkey', 'winter', 'algebra', 'window')
e.g.
!3: 123, 132, 213, 231, 312, 321
!4: abcd, abdc, acbd, acdb, adbc, adcb, etc...
*/

const perm = (...args) => {
  let i;
  for (i = 0; i < args.length; i++) {
    console.log(i, args[i]);
  }
}

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
