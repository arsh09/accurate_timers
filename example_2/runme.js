const timerModule = require('./build/Release/example');
const timer = new timerModule.Timer();

function callback()
{
  console.log('Timer expired after 3 seconds');

}

// Start the timer with a 3000 ms timeout
timer.start(3000, callback());
