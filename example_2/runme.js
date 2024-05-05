const timerModule = require('./build/Release/timer');

class MyTimer extends timerModule.Timer {
    constructor() {
        super();
    }

    onTimeout(ms) {
        console.log(`Timer callback after ${ms} ms`);
    }
}

let myTimer = new MyTimer();
console.log("Starting periodic timer...");
myTimer.startTimer(1000);  // Set timer to 1000 ms

setTimeout(() => {
    console.log("Stopping timer...");
    myTimer.stopTimer();
}, 10000);  // Stop after 10 seconds
