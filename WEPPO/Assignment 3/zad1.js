my_object = {
    data: [],

    get get_data() {
        return this.data == [] ? undefined : this.data[0];
    },

    set push_data(item) {
        this.data.push(item);
    }
}

// Use get and set methods from our object
console.log(my_object.get_data)
my_object.push_data = 'item'
console.log(my_object.get_data)

// Add a new field
my_object.data2 = [];

// Add a new method
my_object.foo = () => {
    return 'foo from my_object';
}

// Add property
Object.defineProperty(my_object, 'my', {
    get: function() { return bValue; },
    set: function(newValue) { bValue = newValue; },
    enumerable: true,
    configurable: true
});

