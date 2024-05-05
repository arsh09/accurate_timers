### C++ Timers for NodeJS 

Accurate timer as a replacement for `setInterval` in NodeJS. In C++, `chrono` and `thread::sleep` are used. 

### How To

```bash
$ npm install -g node-gyp
$ npm install git+https://github.com/arsh09/accurate_timers.git
```

### Example

```javascript
const AccurateTimer = require("accurate_timers");
let old_time = new Date().getTime()
let timer = new AccurateTimer(20, () => {
    const dt = ( new Date().getTime() - old_time );
    console.log(`Time elapsed: ${dt}-ms`)
    old_time = new Date().getTime()
});

timer.start()
setTimeout(() => timer.stop(), 15000); 
```