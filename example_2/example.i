%module timer

%{
#include "example.h"
%}

%include "example.h"

%typemap(jstype) Callback "function";
%typemap(js2c) Callback {
    if (!SWIG_IsOK(SWIG_AsFunctionPtr($input, (void(**)(void)) &$1))) {
        SWIG_exception_fail(SWIG_ArgError(SWIG_TypeError), "Expected a function callback");
    }
}