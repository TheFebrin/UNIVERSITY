var http = require('http');
var filename = 'txt_from_site.txt';
var server =
    http.createServer(
        (req, res) => {
            res.setHeader('Content-Disposition', 'attachment;filename=' + filename);
            res.write('test site....');
            res.end();
        });
server.listen(3000);
console.log('Site started!');
