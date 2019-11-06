

function createFs(n) {
    var fs = []; //i'th function from 'fs'array should return i

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
console.log( myfs[0]() ); 
console.log( myfs[2]() );
console.log( myfs[7]() );