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
  if (args.length === 1) return args[0]
  let i, j;
  for (i = 0; i < args.length; i++) {
    // console.log(i, args[i]);
    console.log(args.slice(1, args.length));
    // permutations = perm(args.slice(1, args.length))
  }
}

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
