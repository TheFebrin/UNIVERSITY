var Tree = function(value, left, right) {
    this.value = value;
    this.left = left;
    this.right = right;
}

var root = new Tree('root', 
                    new Tree('left', new Tree('left grandson'), undefined), 
                    new Tree('right', new Tree('right grandson'), undefined))

console.log(root)
