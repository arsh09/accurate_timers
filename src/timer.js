const AccurateTimer =  require('../build/Release/accurate_timers').AccurateTimer;

let old_time = new Date().getTime()

let timer = new AccurateTimer(20, () => {
    const dt = ( new Date().getTime() - old_time );
    console.log(`Time elapsed: ${dt}-ms`)
    old_time = new Date().getTime()
});

timer.start()

setTimeout(() => timer.stop(), 15000); 