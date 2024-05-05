#include <node_api.h>
#include <chrono>
#include <thread>
#include <functional>
#include <iostream>

class AccurateTimer 
{
public:
    AccurateTimer(){}
    AccurateTimer(napi_env env) : env_(env), callback_(nullptr), active_(false) {}
    ~AccurateTimer() {
        if (callback_) {
            napi_delete_reference(env_, callback_);
        }
    }

    void Say()
    {
        std::cout << "Hello there!" << std::endl;
    }

    void Start(int delay, napi_value callback) {

        if (active_) {
            Stop();
        }

        napi_status status = napi_create_threadsafe_function(
            env_,
            callback,
            nullptr,
            nullptr,
            // napi_create_string_utf8(env_, "Timer Callback", NAPI_AUTO_LENGTH),
            0,
            1,
            nullptr,
            nullptr,
            nullptr,
            CallJs,
            &js_callback_ref
        );
        
        if (status != napi_ok) { std::cout << "Start: napi_create_threadsafe_function() " << status << std::endl; }


        active_ = true;
        worker = std::thread([this, delay]() {
            if (active_)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(delay));
                std::cout << "Timer ends " << std::endl;
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
    napi_env env_;
    napi_ref callback_;
    napi_threadsafe_function js_callback_ref;
    bool active_;
    std::thread worker;
    
};



napi_value CreateTimer(napi_env env, napi_callback_info info) {
    napi_value jsthis;
    napi_valuetype val_type;
    napi_status ret_err_;
    
    ret_err_= napi_get_cb_info(env, info, nullptr, nullptr, &jsthis, nullptr);
    if (ret_err_ != napi_ok) { std::cout << "CreateTimer: napi_get_cb_info()" << std::endl; }

    AccurateTimer* obj;
    ret_err_ = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    if (ret_err_ != napi_ok) { std::cout << "CreateTimer: napi_unwrap() " << ret_err_ << std::endl; }

    return jsthis;
}

napi_value StartTimer(napi_env env, napi_callback_info info) {
    size_t argc = 2;
    napi_value args[2];
    napi_status ret_err_;
    napi_value jsthis;

    ret_err_ = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (ret_err_ != napi_ok) { std::cout << "StartTimer: napi_get_cb_info()" << std::endl; }

    AccurateTimer* obj;
    ret_err_ = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    if (ret_err_ != napi_ok) { std::cout << "StartTimer: napi_unwrap()" << std::endl; }

    int delay;
    ret_err_ = napi_get_value_int32(env, args[0], &delay);
    if (ret_err_ != napi_ok) { std::cout << "StartTimer: napi_get_value_int32()" << std::endl; }

    std::cout << "Delay: " << (int) delay << std::endl;
 
    // // test if the function gets called
    // napi_ref callback_;
    // napi_handle_scope scope;
    // napi_value global;
    // napi_value cb;
    // napi_value result;

    // ret_err_ = napi_create_reference(env, args[1], 1, &callback_);
    // if (ret_err_ != napi_ok) { std::cout << "StartTimer: napi_create_reference()" << std::endl; }
    // ret_err_ = napi_open_handle_scope(env, &scope);
    // if (ret_err_ != napi_ok) { std::cout << "StartTimer: napi_open_handle_scope()" << std::endl; }
    // ret_err_ = napi_get_global(env, &global);
    // if (ret_err_ != napi_ok) { std::cout << "StartTimer: napi_get_global()" << std::endl; }
    // ret_err_ = napi_get_reference_value(env, callback_, &cb);
    // if (ret_err_ != napi_ok) { std::cout << "StartTimer: napi_get_reference_value()" << std::endl; }
    // ret_err_ = napi_call_function(env, global, cb, 0, nullptr, &result);
    // if (ret_err_ != napi_ok) { std::cout << "StartTimer: napi_call_function()" << std::endl; }
    // ret_err_ = napi_close_handle_scope(env, scope);
    // if (ret_err_ != napi_ok) { std::cout << "StartTimer: napi_close_handle_scope()" << std::endl; }

    if (obj!=nullptr){
        obj->Say();
        obj->Start(delay, args[1]);
    } 

    return nullptr;
}

napi_value StopTimer(napi_env env, napi_callback_info info) {
    napi_value jsthis;
    napi_status ret_err_;

    ret_err_ = napi_get_cb_info(env, info, nullptr, nullptr, &jsthis, nullptr);
    if (ret_err_ != napi_ok) { std::cout << "StopTimer: napi_get_cb_info()" << std::endl; }

    AccurateTimer* obj;
    ret_err_ = napi_unwrap(env, jsthis, reinterpret_cast<void**>(&obj));
    if (ret_err_ != napi_ok) { std::cout << "StopTimer: napi_unwrap()" << std::endl; }

    if (obj !=nullptr){
        obj->Stop();
    }

    return nullptr;
}


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
        {"start", nullptr, StartTimer, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"stop", nullptr, StopTimer, nullptr, nullptr, nullptr, napi_default, nullptr}
    };

    size_t desc_count = sizeof(desc) / sizeof(*desc);
    napi_define_class(env, "AccurateTimer", NAPI_AUTO_LENGTH, NewTimer, nullptr, desc_count, desc, &js_class);
    napi_set_named_property(env, exports, "AccurateTimer", js_class);
    napi_define_properties(env, exports, desc_count , desc);

    return exports;
}



NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
