function *fib() {
    var data = [0,1];
    while (true) {
        yield data[1];
        var newRes = data[0] + data[1];
        data = [data[1], newRes];
    }
}

function* take(it, top) {
    for (var i = 0; i < top; i++) {
        yield it.next().value
    }
}




// zwróć dokładnie 10 wartości z potencjalnie
// "nieskończonego" iteratora/generatora
for (let num of take( fib(), 10 ) ) {
    console.log(num);
}