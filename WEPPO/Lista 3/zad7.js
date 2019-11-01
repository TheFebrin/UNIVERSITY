// function fib() {
//     var data = [0,1]
//     return {
//         next : function() {
//             var newRes = data[0] + data[1];
//             data = [data[1], newRes];
//             return {
//                 value : data[1],
//                 done  : false
//             }
//         }
//     }
// }
function *fib() {
    var data = [1,1];
    while (true) {
        yield data[1];
        var newRes = data[0] + data[1];
        data = [data[1], newRes];
    }
}


// var _it = fib();
// for ( var _result; _result = _it.next(), !_result.done; ) {
//     if(_result.value > 100)
//         break;
//     console.log( _result.value );
// }

for ( var i of fib() ) {
    if(i > 100)
            break;
    console.log( i );
}