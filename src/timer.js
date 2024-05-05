const AccurateTimer = require("accurate_timer");

let old_time = new Date().getTime()

let timer = new AccurateTimer(20, () => {
    const dt = ( new Date().getTime() - old_time );
    console.log(`Time elapsed: ${dt}-ms`)
    old_time = new Date().getTime()
});

timer.start()

setTimeout(() => timer.stop(), 15000); 