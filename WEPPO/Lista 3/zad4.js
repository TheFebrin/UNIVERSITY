

function createFs(n) {
    // tworzy tablicę n funkcji
    var fs = []; // i-ta funkcja z tablicy ma zwrócić i

    var _loop = function _loop(i) {
        fs[i] = function () {
            return i;
        };
    };

    for (var i = 0; i < n; i++) {
        _loop(i);
    };
    return fs;
}
var myfs = createFs(10);
console.log( myfs[0]() ); // zerowa funkcja miała zwrócić 0
console.log( myfs[2]() ); // druga miała zwrócić 2
console.log( myfs[7]() );
// 10 10 10