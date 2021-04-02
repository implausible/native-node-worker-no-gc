#include <nan.h>
#include <node.h>
#include <iostream>

using namespace v8;

class Test : public Nan::ObjectWrap {
public:
  static NAN_MODULE_INIT(Init) {
    Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("Test").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());
    Nan::Set(target, Nan::New("Test").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
  }

private:
  double value;

  Test(double value = 0) : value(value) {
    std::cout << "new Test()" << std::endl;
  }

  ~Test() {
    std::cout << "~Test()" << std::endl;
  }

  static NAN_METHOD(New) {
    if (info.IsConstructCall()) {
      double value = info[0]->IsUndefined() ? 0 : Nan::To<double>(info[0]).FromJust();
      Test *obj = new Test(value);
      obj->Wrap(info.This());
      info.GetReturnValue().Set(info.This());
    } else {
      const int argc = 1;
      Local<Value> argv[argc] = {info[0]};
      Local<Function> cons = Nan::New(constructor());
      info.GetReturnValue().Set(Nan::NewInstance(cons, argc, argv).ToLocalChecked());
    }
  }

  static inline Nan::Persistent<Function> & constructor() {
    thread_local static Nan::Persistent<Function> my_constructor;
    return my_constructor;
  }
};

NAN_MODULE_WORKER_ENABLED(addon, Test::Init)
