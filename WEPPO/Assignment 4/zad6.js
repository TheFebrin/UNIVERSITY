var fs = require('fs');

fs.readFile('zad1.js','utf-8', (err,data) => {
    if(err) {
        throw err;
    }
	console.log(data);
});