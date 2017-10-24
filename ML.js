function permutationArr(str) 
{ 
  var arr = str.split(''),
  permutations = [];   

  function swap(a, b)
  {
    var tmp = arr[a];
    arr[a] = arr[b];
    arr[b] = tmp;
  }

  function generate(n) {
    if (n == 1) {
      permutations.push(arr.join());
    } else {
      for (var i = 0; i != n; ++i) {
        generate(n - 1);
        swap(n % 2 ? 0 : i, n - 1);
      }
    }
  }

  generate(arr.length);
  console.log(permutations);
}    

console.log(permutationArr('abcde')); 






// procedure generate(n : integer, A : array of any):
// if n = 1 then
//       output(A)
// else
//     for i := 0; i < n - 1; i += 1 do
//         generate(n - 1, A)
//         if n is even then
//             swap(A[i], A[n-1])
//         else
//             swap(A[0], A[n-1])
//         end if
//     end for
//     generate(n - 1, A)
// end if