const readline = require('readline');
const fs = require('fs');

const rl = readline.createInterface({
  input: fs.createReadStream('sample.txt'),
  crlfDelay: Infinity
});


var data = {};
rl.on('line', (line) => {
    const ip = line.split(' ')[1];
    if (data[ip] !== undefined)
        data[ip]++;
    else
        data[ip] = 1;
    // console.log(Object.keys(data))
}).on('close',() => {
    var sortable = [];
    for (var vehicle in data) {
        sortable.push([vehicle, data[vehicle]]);
    }
    
    sortable.sort(function(a, b) {
        return b[1] - a[1];
    });   

    [0,1,2].forEach((item)=> console.log(sortable[item][0]))
})
