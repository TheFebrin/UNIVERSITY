var fs = require('fs');
var https = require('https');
(async function () {
    var pfx = await fs.promises.readFile('certyfikat.pfx');
    var server = https.createServer({
        pfx: pfx,
        passphrase: 'test'
    },
        (req, res) => {
            res.setHeader('Content-type', 'certyfikat/html; charset=utf-8');
            res.end(`HELLO! ${new Date()}`);
        });
    server.listen(3000);
    console.log('Site started!');
})();
