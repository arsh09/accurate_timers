const addon = require('./build/Release/timer');

let timer = addon.createTimer();

timer.start(200, () => console.log("Timer expired after 1 second"));

setTimeout(() => timer.stop(), 5000); // Stop the timer before it expires