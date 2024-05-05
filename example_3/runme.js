const mySwigPlugin = require('./build/Release/example');

var unary = function(x) {
    return x * x;
};

var delegate = new mySwigPlugin.JsFunctionDelegate(unary);
assert(delegate.value(5) === 25);