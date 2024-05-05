const addon = require('./build/Release/timer');

let old_time = new Date().getTime()

let timer = new addon.AccurateTimer(20, () => {
    const dt = ( new Date().getTime() - old_time );
    console.log("Timer expired after 1 second: ", dt)
    old_time = new Date().getTime()
});

timer.start()

setTimeout(() => timer.stop(), 15000); 