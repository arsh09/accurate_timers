const addon = require('./build/Release/timer');

// let timer = addon.createTimer();

let timer = new addon.AccurateTimer();

// const n = timer.createTimer();

timer.start(1000, () => console.log("Timer expired after 1 second"));

setTimeout(() => timer.stop(), 5000); // Stop the timer before it expires