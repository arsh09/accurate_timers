const timerModule = require('./build/Release/example');
const timer = new timerModule.Timer();

function callback(a)
{
  console.log('Timer expired after 3 seconds');

}

const a = 0
// Start the timer with a 3000 ms timeout
timer.start(3000, function(a){
  console.log("AD")
});
