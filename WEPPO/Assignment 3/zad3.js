function forEach(array, f) {
    for (var i = 0; i < array.length; i++) {
        f(array[i]);
    }
}

function filter(arr, f) {
    var ans = []
    for (var i = 0; i < arr.length; i++) {
        if (f(arr[i])) {
            ans.push(arr[i]);
        }
    }
    return ans;
}

function map(arr, f) {
    for (var i = 0; i < arr.length; i++) {
        arr[i] = f(arr[i]);
    }
    return arr;
}


var list = [1, 2, 3, 4, 5]
map(list, (a) => a * a);
forEach(list, (elem) => console.log(`${elem}`))
console.log('Even: ', filter(list, (i) => i % 2 == 0));


