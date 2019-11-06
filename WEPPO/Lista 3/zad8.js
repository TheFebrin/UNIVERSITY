function *fib() {
    var data = [0,1];
    while (true) {
        yield data[1];
        var newRes = data[0] + data[1];
        data = [data[1], newRes];
    }
}

function* take(it, MAX) {
    for (var i = 0; i < MAX; i++) {
        yield it.next().value
    }
}


for (let num of take( fib(), 5 ) ) {
    console.log(num);
}