var http = require('http');
var filename = 'a.txt';
var server =
    http.createServer(
        (req, res) => {
            res.setHeader('Content-Disposition', 'attachment;filename=' + filename);
            res.write('asdf');
            res.end();
        });
server.listen(3000);
console.log('started');
