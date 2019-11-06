function MyGenerator(n) {
    return function createGenerator() {
        var _state = 0;
        return {
            next : function() {
                return {
                value : _state,
                done : _state ++ >= n
                }
            }
        }
    }
}

var foo = {
    [Symbol.iterator] : MyGenerator(5)
};
for ( var f of foo ) {
    console.log(f);
}