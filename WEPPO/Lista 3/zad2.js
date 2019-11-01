function fib(n) {
    var memo = {0: 1, 1: 1};
    function aux(_n) {
        if (!memo._n) {
            memo._n = aux(_n-1) + _aux(_n-2);
        }
        return memo._n
    } 
}

function countTime(f) {
    const start = new Date()
    f();
    const end = new Date()
    return end.getTime() - start.getTime()
}

list = [1, 10, 20, 30, 32, 35]
odp1 = list.slice().map(i => countTime(() =>fib(i)))
console.log(odp1)
