#include <node_api.h>

napi_value Method(napi_env env, napi_callback_info args) {
    napi_value greeting;
    napi_status status = napi_create_string_utf8(env, "Hello, World!", NAPI_AUTO_LENGTH, &greeting);
    return (status == napi_ok) ? greeting : nullptr;
}

napi_value Init(napi_env env, napi_value exports) {
    napi_status status;
    napi_value fn;

    status = napi_create_function(env, nullptr, 0, Method, nullptr, &fn);
    if (status != napi_ok) return nullptr;

    status = napi_set_named_property(env, exports, "hello", fn);
    if (status != napi_ok) return nullptr;

    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
