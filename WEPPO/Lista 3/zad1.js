obj = {
    data: [],
    get first() {
        return this.data == [] ? undefined : this.data[0];
    },
    set push(item) {
        this.data.push(item);
    }
}


console.log(obj.first)
obj.push = 'Pierwszy'
console.log(obj.first)
obj.data2 = [1,2];
obj.funData2 = () => {
    return 'taka oto fucnkacja';
}
console.log(obj.funData2())

Object.defineProperty(obj, 'my', {
    get: function() { return bValue; },
    set: function(newValue) { bValue = newValue; },
    enumerable: true,
    configurable: true
});

