var http = require('http');
var express = require('express');
var app = express();

app.use(express.urlencoded({ extended: true }));

app.set('view engine', 'ejs');
app.set('views', './views');

app.get('/', (req, res) => {
    res.render('index', { Subject: '', NameSurname: '', Group: '', Date: '', Exercise: ['', '', '', '', '', '', '', '', '', ''], Sum: '', errorLabel: '' });
});

app.post('/', (req, res) => {
    var Subject = req.body.Subject
    var NameSurname = req.body.NameSurname;
    var Group = req.body.Group;
    var Date = req.body.Date;
    var Exercise = req.body.Exercise;
    var Sum = req.body.Sum;
    if (isDataValid(Subject, NameSurname, Group, Date)) {
        const sum = calculateSum(Exercise);
        res.render('print', { Subject: Subject, NameSurname: NameSurname, Group: Group, Date: Date, Exercise: Exercise.map(v => v == '' ? 0 : v), Sum: sum });
    }
    else {
        res.render('index', { Subject: '', NameSurname: '', Group: '', Date: '', Exercise: ['', '', '', '', '', '', '', '', '', ''], Sum: '', errorLabel: 'Popraw dane' });
    }
});

http.createServer(app).listen(3000);

function isDataValid(sub, ns, gr, dt) {
    return sub != '' && ns != '' && gr != '' && dt != '';
}

function calculateSum(ex) {
    let acc = 0;
    ex.forEach(element => {
        if (element != '') {
            acc += parseInt(element);
        }
    });
    return acc;
}