const fs = require('fs');

fs.readFile('../TSP/usaCitiesSmall.txt', 'utf8', function(err, data) {  
    if (err) throw err;
    const arr = [];
    let ys = /   /g;
    let xs =/ /;
    let name = / \| /;
    let closebracket = /\r/;
    data = data.replace(ys, '","y":"');
    data = data.split('\n');
    for (let i = 0; i < data.length - 1; i++) {
      data[i] = data[i].replace(xs, '{"x":"');
      data[i] = data[i].replace(name, '","name":"');
      data[i] = data[i].replace(closebracket, '"}');
      arr.push(data[i]);
      // let obj = JSON.parse(data[i]);
      // arr.push(obj);
    }
    // console.log(Cities);
    console.log(arr);
    // console.log(data);
    fs.writeFile("../TSP/cityObj.js", Array.of(arr), 'utf8', function (err) {
    if (err) {
        return console.log(err);
    }
    console.log("The file was saved!");
  }); 
});

// console.log(Cities);
// console.log(arr);