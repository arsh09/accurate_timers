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

### Possible Usecase 

There are a lot of ElectronJS application out there that requires a better timer module. The reason being that `setInterval` tends to queue in NodeJS uv-event management. The motivation for this module comes from removing a bottleneck introduced due to `setInterval` for a biofeedback software written in Vue-ElectronJS. Replacing the `setInterval` improves not only the performance and reactivity of the overall app, it alsp frees up the event queue for Node processes as well.

### ToDos

- Create a similar structure as `setInterval`, `setTimeout` and `setImmediate`.
- Release on npm.
- Add tests.
- Add CI/CD via GHA.