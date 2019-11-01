function wrapGen(MAX) {
    return function createGenerator() {
        var _state = 0;
        return {
            next : function() {
                return {
                value : _state,
                done : _state++ >= MAX
                }
            }
        }
    }
}

var foo = {
    [Symbol.iterator] : wrapGen(10)
};
for ( var f of foo )
    console.log(f);