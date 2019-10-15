function fib_rec(n)
{
    if(n == 0) return 0;
    if(n == 1) return 1;
    return fib_rec(n - 1) + fib_rec(n - 2);
}

function fib_iter(n)
{
    var a = 0;
    var b = 1;
    while(-- n)
    {
        b += a;
        a = b - a;
    }
    return b;
}

var no = 42
console.log('Fibonacci iter: ')
console.time("iter");
console.log(no, ' -> ', fib_iter(no))
console.timeEnd("iter");

console.time("rec");
console.log('\n\nFibonacci rec: ')
console.log(no, ' -> ', fib_rec(no))
console.timeEnd("rec");