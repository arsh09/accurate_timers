%module(directors="1") timer

%{
#include "Timer.h"
%}

%feature("director") Timer;  // Enable director for Timer class

%include "Timer.h"
