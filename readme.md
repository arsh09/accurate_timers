### C++ Timers for NodeJS 

```bash
$ npm install -g node-gyp
```

```bash 
$ swig -javascript -node -c++ -o example_wrap.cpp example.i 
$ node-gyp configure build 
$ node runme.js
```