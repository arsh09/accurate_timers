%module timer

%{
#include <node_object_wrap.h>

class JsFunctionDelegate : public node::ObjectWrap {
 public:
  ~JsFunctionDelegate(){};
  double value(double x) {
    auto isolate = v8::Isolate::GetCurrent();
    v8::HandleScope scope(isolate);
    auto context = isolate->GetCurrentContext();
    auto global = context->Global();

    const int argc = 1;
    v8::Handle<v8::Value> argv[argc];
    argv[0] = v8::Number::New(isolate, x);

    auto fn = v8::Local<v8::Function>::New(isolate, javascriptCallback);
    auto returnValue = fn->Call(Null(isolate), argc, argv);

    return returnValue->NumberValue();
  };
  explicit JsFunctionDelegate(v8::Persistent<v8::Function, v8::CopyablePersistentTraits<v8::Function>>& cb) : javascriptCallback(cb) {};
 private:
  v8::Persistent<v8::Function, v8::CopyablePersistentTraits<v8::Function>> javascriptCallback;
};

%}

%feature("director") JsFunctionDelegate;

class JsFunctionDelegate {
  public:
    virtual JsFunctionDelegate(v8::Persistent<v8::Function, v8::CopyablePersistentTraits<v8::Function>>&);
    virtual ~JsFunctionDelegate();
    virtual double value(double x);
};
