const addon = require('./build/Release/timer');

// let timer = addon.createTimer();

let timer = new addon.AccurateTimer();

timer.createTimer(2000, () => console.log("Timer expired after 1 second"));

setTimeout(() => timer.stop(), 5000); // Stop the timer before it expires