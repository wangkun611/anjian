#include <node.h>

#include <windows.h>
#include <atlbase.h>

void HookKeyboard();
bool moveTo(int x, int y);

namespace anjian {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

void Method(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  args.GetReturnValue().Set(String::NewFromUtf8(isolate, "world"));
}

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "hello", Method);

  HookKeyboard();
}

NODE_MODULE(addon, init)

}  // namespace demo