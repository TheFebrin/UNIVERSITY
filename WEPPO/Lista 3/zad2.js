function fib(n) {
    let memo = {0: 0, 1: 1};
    function aux(m) {
        if (typeof memo[m] == 'undefined') {
            memo[m] = aux(m-1) + aux(m-2);
        }
        return memo[m]
    }
    return aux(n) 
}

function bad_fib(n) {
    if(n == 0) return 0;
    if(n == 1) return 1;
    return bad_fib(n - 1) + bad_fib(n - 2);
}

function countTime(n) {
    console.time("count");
    console.log('Bad fib: ')
    console.log(n, ' -> ', bad_fib(n))
    console.timeEnd("count");

    console.log()
    console.time("count");
    console.log('Better fib: ')
    console.log(n, ' -> ', fib(n))
    console.timeEnd("count");
}

countTime(35)
