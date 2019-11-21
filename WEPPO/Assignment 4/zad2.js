var Tree = function(value, left, right) {
    this.value = value;
    this.left = left;
    this.right = right;
}

Tree.prototype.say = function() {console.log('It s me Tree')};
Tree.prototype = {[Symbol.iterator]:GenIterator};

function * GenIterator (){
    const stack = [this];
    while (stack.length) {
        const item = stack.pop();
        if(item.right){
            stack.push(item.right)
        }
        if(item.left){
            stack.push(item.left)
        }
        yield item.value
    }
}


var root = new Tree(1, 
                    new Tree(2, new Tree(4)), 
                    new Tree(3, new Tree(5)))

// console.log(Symbol.iterator)

for ( var e of root ){
    console.log( e );
}