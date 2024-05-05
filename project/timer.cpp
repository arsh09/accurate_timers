#include <node_api.h>
#include <chrono>
#include <thread>
#include <functional>
#include <iostream>
#include <assert.h>

class AccurateTimer 
{
public:
    AccurateTimer(){}
    // AccurateTimer(napi_env env) : env_(env), callback_(nullptr), active_(false) {}
    AccurateTimer(napi_env env, napi_value callback) 
    : env(env), active_(false), js_callback_ref(nullptr) {

        napi_status status;
        napi_value fn_name; 
        status = napi_create_string_utf8(env, "Timer Callback", NAPI_AUTO_LENGTH, &fn_name),
        assert( status == napi_ok );

        status = napi_create_threadsafe_function(
            env,
            callback,
            nullptr,
            fn_name,
            0,
            1,
            nullptr,
            nullptr,
            nullptr,
            CallJs,
            &js_callback_ref
        );
        assert(status == napi_ok);
    }

    ~AccurateTimer() { 
        napi_release_threadsafe_function(js_callback_ref, napi_tsfn_release);
    }

    void Say()
    {
        std::cout << "Hello there!" << std::endl;
    }

    void Start(int delay) {

        if (active_) {
            Stop();
        }
        active_ = true;
        worker = std::thread([this, delay]() {
            while (active_)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(delay));
                std::cout << "Hello there! " << delay << std::endl;
                napi_call_threadsafe_function(js_callback_ref, nullptr, napi_tsfn_blocking);
            }
        });
        worker.detach();
    }

    void Stop() {
        active_ = false;
        if ( worker.joinable() ) { worker.join(); }
    }

    static void CallJs(napi_env env, napi_value js_callback, void* context, void* data) {
        // Call the JavaScript callback
        napi_value undefined;
        napi_get_undefined(env, &undefined);
        napi_call_function(env, undefined, js_callback, 0, nullptr, nullptr);
    }

private:
    napi_env env;
    napi_threadsafe_function js_callback_ref;
    std::atomic<bool> active_;
    std::thread worker;
    
};



napi_value CreateTimer(napi_env env, napi_callback_info info) {
    size_t argc = 2;
    napi_value args[2];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

    int delay;
    napi_get_value_int32(env, args[0], &delay);

    AccurateTimer* timer = new AccurateTimer(env, args[1]);
    timer->Start(delay);

    napi_value result;
    napi_get_undefined(env, &result);
    return result;
}

// napi_value StartTimer(napi_env env, napi_callback_info info) {

//     size_t argc = 2;
//     napi_value args[2];
//     napi_status ret_err_;
//     napi_value jsthis;

//     ret_err_ = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
//     if (ret_err_ != napi_ok) { std::cout << "StartTimer: napi_get_cb_info()" << std::endl; }

//     AccurateTimer* obj;
//     ret_err_ = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
//     if (ret_err_ != napi_ok) { std::cout << "StartTimer: napi_unwrap()" << std::endl; }

//     int delay;
//     ret_err_ = napi_get_value_int32(env, args[0], &delay);
//     if (ret_err_ != napi_ok) { std::cout << "StartTimer: napi_get_value_int32()" << std::endl; }

//     std::cout << "Delay: " << (int) delay << std::endl;
  
//     if (obj!=nullptr){
//         obj->Say();
//         obj->Start(delay, args[1]);
//     } 

//     return nullptr;
// }

// napi_value StopTimer(napi_env env, napi_callback_info info) {
//     napi_value jsthis;
//     napi_status ret_err_;

//     ret_err_ = napi_get_cb_info(env, info, nullptr, nullptr, &jsthis, nullptr);
//     if (ret_err_ != napi_ok) { std::cout << "StopTimer: napi_get_cb_info()" << std::endl; }

//     AccurateTimer* obj;
//     ret_err_ = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
//     if (ret_err_ != napi_ok) { std::cout << "StopTimer: napi_unwrap()" << std::endl; }

//     if (obj !=nullptr){
//         obj->Stop();
//     }

//     return nullptr;
// }


napi_value NewTimer(napi_env env, napi_callback_info info) {

    napi_status ret_err_;
    napi_value jsthis;
    napi_get_cb_info(env, info, nullptr, nullptr, &jsthis, nullptr);

    AccurateTimer* obj = new AccurateTimer();
    ret_err_ = napi_wrap(env, jsthis, obj, [](napi_env env, void* finalize_data, void* hint) {
        delete static_cast<AccurateTimer*>(finalize_data);
    }, nullptr, nullptr);

    if (ret_err_ != napi_ok) { std::cout << "NewTimer: napi_wrap()" << std::endl; }

    return jsthis;
}

napi_value Init(napi_env env, napi_value exports) {
    napi_value js_class;

    napi_property_descriptor desc[] = {
        {"createTimer", nullptr, CreateTimer, nullptr, nullptr, nullptr, napi_default, nullptr},
        // {"start", nullptr, StartTimer, nullptr, nullptr, nullptr, napi_default, nullptr},
        // {"stop", nullptr, StopTimer, nullptr, nullptr, nullptr, napi_default, nullptr}
    };

    size_t desc_count = sizeof(desc) / sizeof(*desc);
    napi_define_class(env, "AccurateTimer", NAPI_AUTO_LENGTH, NewTimer, nullptr, desc_count, desc, &js_class);
    napi_set_named_property(env, exports, "AccurateTimer", js_class);
    napi_define_properties(env, exports, desc_count , desc);

    return exports;
}



NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
