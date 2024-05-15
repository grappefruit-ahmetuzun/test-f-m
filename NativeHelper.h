

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)


#define JNI_HELPER_PATH             "../cocos2d/cocos/platform/android/jni/JniHelper.h"
#define CCCOMMON_PATH               "../cocos2d/cocos/platform/android/CCCommon-android.cpp"

#include "cocos2d.h"

namespace NativeHelper
{
    
    void callFunc(const char* funcName);
    void callFuncWithCallback(const char* funcName, std::function<void(const char *data)> callback);
    void callFuncForHeyzapWithCallback(const char* funcName, std::function<void(const char *data, int state)> callback);
    
    void setHeyzapCallback(std::function<void(const char *data, int state)> callback);
    void setInterstitialCallback(std::function<void(int state)> callback);
    
    void callFuncStrWithCallback(const char* funcName, const char* idunit, std::function<void(const char *data)> callback);
    void callFuncStrWithCallback2(const char* funcName, const char* idunit, const char* idunit2, std::function<void(const char *data, const char *key)> callback);
    
    void callFuncStr(const char* funcName, const char* idunit);
    void callFuncStr(const char* funcName, const char* idunit1, const char* idunit2);
    void callFuncStr(const char* funcName, const char* idunit1, const char* idunit2, const char* idunit3);
    void callFuncStr(const char* funcName, const char* idunit1, const char* idunit2, const char* idunit3, const char* idunit4);

    bool getBoolFromFunc(const char* funcName);
    
    void setShareCallback(std::function<void(bool)> callback);
    void callFuncShareCallback(const char* funcName, std::function<void(bool)> callback);
    
    void show(std::string message, int interval, int tag);
    void cancel(int tag);
    
    // subscriptions
    
    void setSubscriptionCallback(std::function<void(bool)> callback);
    
}

#endif
