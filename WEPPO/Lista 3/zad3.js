function forEach(array, f) {
    for (var i = 0; i < array.length; i++) {
        f(array[i]);
    }
}

function filter(arr, f) {
    var resArr = []
    for (var i = 0; i < arr.length; i++) {
        if (f(arr[i]))
            resArr.push(arr[i]);
        
    }
    return resArr;
}

function map(arr, f) {
    for (var i = 0; i < arr.length; i++) {
        arr[i] = f(arr[i]);
    }
    return arr;
}

console.log('Zad2')
var list = [1,2,3]
map(list, (a) => 1 + a);
forEach(list, (item) => console.log(`${item};`))
console.log(filter(list, (i) => i < 4));


