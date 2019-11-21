function Foo() {
    console.log('Foo');
}

Foo.prototype.Bar = function () {
    function Qux() {
        console.log('Qux');
    }
    Qux();
    console.log('Bar');
}

var f = new Foo();

f.Bar();
//f.Qux(); - "prywatne"
f.Bar.Qux();