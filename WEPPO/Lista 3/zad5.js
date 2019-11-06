function sum() {
    return Object.values(arguments).reduce((acc, item) => acc + item);
}

console.log(sum(1,2,3,4,5))