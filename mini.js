const permutation = (arr, length) => {
  console.log('arr: ' + arr)
  let results = []

  let c = new Array(length)
  c.fill(0)

  let i = 0;
  while (i < length) {
    if (c[i] < i) {
      if (!(i % 2)) arr[i] = [arr[0], arr[0] = arr[i]][0]; // swap(arr[0], arr[i])
      else arr[i] = [arr[c[i]], arr[c[i]] = arr[i]][0]; // swap(arr[c[i]], arr[i])
      console.log('a: ' + arr)
      results.push(arr)
      c[i]++
      i = 0
    }
    else {
      c[i] = 0
      i++
    }
  }
  return results
}

// const numbers = [1, 2, 3]
// const letters = ['a', 'b', 'c', 'd']
// const words = ['corn', 'turkey', 'winter', 'algebra', 'window']
//
// permutation(numbers)
// permutation(letters)
// permutation(words)

module.exports = {
  permutation
}
