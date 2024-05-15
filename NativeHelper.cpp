//
// Created by Estoty
//
//

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "NativeHelper.h"
#include <string.h>
#include <jni.h>
#include <iostream>

#include JNI_HELPER_PATH

std::function<void(const char *data)> lastcallBack = nullptr;
std::function<void(const char *data, int state)> callBackForHeyzap = nullptr;
std::function<void(int state)> callBackForInterstitial = nullptr;
std::function<void(const char *data, const char *key)> lastcallBackKey = nullptr;

std::function<void(bool)> shareCallback;
std::function<void(bool)> subscriptionsCallback = nullptr;

extern "C" {
    
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_onShareDidFinish(JNIEnv*  env, jobject thiz,int done) {
        if (shareCallback) {
            shareCallback(done);
        }
    }
    
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_onSubscriptionState(JNIEnv*  env, jobject thiz,int is_active) {
        if (subscriptionsCallback) {
            subscriptionsCallback(is_active);
        }
    }
    
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_nativeReturnName(JNIEnv*  env, jobject thiz, jstring rowName) {
        const char* chars = env->GetStringUTFChars(rowName, nullptr);
        std::string ret(chars);
        env->ReleaseStringUTFChars(rowName, chars);
        
        if (lastcallBack) {
            lastcallBack(ret.c_str());
        }
        
    }
    
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_heyzapVideoCompleted(JNIEnv*  env, jobject thiz, jstring tag, int state) {
        const char* chars = env->GetStringUTFChars(tag, nullptr);
        std::string ret(chars);
        env->ReleaseStringUTFChars(tag, chars);
        
        if (callBackForHeyzap) {
            callBackForHeyzap(ret.c_str(), state);
        }
        
    }
    
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_interstitialCallback(JNIEnv*  env, jobject thiz, int state) {
        
        if (callBackForInterstitial) {
            callBackForInterstitial(state);
        }
    }
    
    JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_AppActivity_nativeReturnName2(JNIEnv*  env, jobject thiz, jstring rowName, jstring key2) {
        const char* chars = env->GetStringUTFChars(rowName, nullptr);
        const char* chars2 = env->GetStringUTFChars(key2, nullptr);
        std::string ret(chars);
        std::string ret2(chars2);
        env->ReleaseStringUTFChars(rowName, chars);
        if (lastcallBackKey) {
            lastcallBackKey(ret.c_str(), ret2.c_str());
        }
    }
}


void NativeHelper::callFunc(const char* funcName) {
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t,
                                                "org/cocos2dx/cpp/AppActivity",
                                                funcName,
                                                "()V"))
    {
        
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }

}

//

void NativeHelper::show(std::string message, int interval, int tag)
{
    cocos2d::JniMethodInfo methodInfo;
    if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo,
                                                "org/cocos2dx/cpp/AppActivity",
                                                "showLocalNotification",
                                                "(Ljava/lang/String;II)V"))
    {
        jstring stringArg = methodInfo.env->NewStringUTF(message.c_str());
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, stringArg, interval, tag);
        methodInfo.env->DeleteLocalRef(stringArg);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
    }
    
}

void NativeHelper::cancel(int tag)
{
    
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t,
                                                "org/cocos2dx/cpp/AppActivity",
                                                "cancelLocalNotification",
                                                "(I)V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID, tag);
        t.env->DeleteLocalRef(t.classID);
    }
    
}

//

void NativeHelper::callFuncWithCallback(const char* funcName, std::function<void(const char *data)> callback) {
    
    lastcallBack = callback;
    
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t,
                                                "org/cocos2dx/cpp/AppActivity",
                                                funcName,
                                                "()V"))
    {
        
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
    
    
}

void NativeHelper::setHeyzapCallback(std::function<void(const char *data, int state)> callback){
    callBackForHeyzap = callback;
}

void NativeHelper::callFuncForHeyzapWithCallback(const char* funcName, std::function<void(const char *data, int state)> callback) {
    
    callBackForHeyzap = callback;
    
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t,
                                                "org/cocos2dx/cpp/AppActivity",
                                                funcName,
                                                "()V"))
    {
   
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
    
}

void NativeHelper::setInterstitialCallback(std::function<void(int state)> callback){
    callBackForInterstitial = callback;
}

void NativeHelper::setShareCallback(std::function<void(bool)> callback){
    shareCallback = callback;
}

void NativeHelper::callFuncShareCallback(const char* funcName, std::function<void(bool)> callback) {
    
    shareCallback = callback;
    
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t,
                                                "org/cocos2dx/cpp/AppActivity",
                                                funcName,
                                                "()V"))
    {
        
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
    
}


void NativeHelper::callFuncStrWithCallback2(const char* funcName, const char* idunit, const char* idunit2, std::function<void(const char *data, const char* key)> callback) {
    
    lastcallBackKey = callback;
    
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t,
                                                "org/cocos2dx/cpp/AppActivity",
                                                funcName,
                                                "(Ljava/lang/String;Ljava/lang/String;)V"))
    {
        jstring adUnitIDArg1 = t.env->NewStringUTF(idunit);
        jstring adUnitIDArg2 = t.env->NewStringUTF(idunit2);
        
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID, adUnitIDArg1, adUnitIDArg2);
        t.env->DeleteLocalRef(t.classID);
    }
    
}


void NativeHelper::callFuncStr(const char* funcName, const char* idunit) {
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t,
                                                "org/cocos2dx/cpp/AppActivity",
                                                funcName,
                                                "(Ljava/lang/String;)V"))
    {
        jstring adUnitIDArg = t.env->NewStringUTF(idunit);
        
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID, adUnitIDArg);
        t.env->DeleteLocalRef(t.classID);
    }
}

void NativeHelper::callFuncStr(const char* funcName, const char* idunit1, const char* idunit2) {
    
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t,
                                                "org/cocos2dx/cpp/AppActivity",
                                                funcName,
                                                "(Ljava/lang/String;Ljava/lang/String;)V"))
    {
        jstring adUnitIDArg1 = t.env->NewStringUTF(idunit1);
        jstring adUnitIDArg2 = t.env->NewStringUTF(idunit2);
        
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID, adUnitIDArg1, adUnitIDArg2);
        t.env->DeleteLocalRef(t.classID);
    }
}

void NativeHelper::callFuncStr(const char* funcName, const char* idunit1, const char* idunit2, const char* idunit3) {
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t,
                                                "org/cocos2dx/cpp/AppActivity",
                                                funcName,
                                                "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V"))
    {
        jstring adUnitIDArg1 = t.env->NewStringUTF(idunit1);
        jstring adUnitIDArg2 = t.env->NewStringUTF(idunit2);
        jstring adUnitIDArg3 = t.env->NewStringUTF(idunit3);
        
        
        t.env->CallStaticVoidMethod(t.classID, t.methodID, adUnitIDArg1, adUnitIDArg2, adUnitIDArg3);
        t.env->DeleteLocalRef(t.classID);
    }

}

void NativeHelper::callFuncStr(const char* funcName, const char* idunit1, const char* idunit2, const char* idunit3, const char* idunit4) {
    cocos2d::JniMethodInfo t;
    if (cocos2d::JniHelper::getStaticMethodInfo(t,
                                                "org/cocos2dx/cpp/AppActivity",
                                                funcName,
                                                "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V"))
    {
        jstring adUnitIDArg1 = t.env->NewStringUTF(idunit1);
        jstring adUnitIDArg2 = t.env->NewStringUTF(idunit2);
        jstring adUnitIDArg3 = t.env->NewStringUTF(idunit3);
        jstring adUnitIDArg4 = t.env->NewStringUTF(idunit4);


        t.env->CallStaticVoidMethod(t.classID, t.methodID, adUnitIDArg1, adUnitIDArg2, adUnitIDArg3, adUnitIDArg4);
        t.env->DeleteLocalRef(t.classID);
    }

}


bool NativeHelper::getBoolFromFunc(const char* funcName){
    
    cocos2d::JniMethodInfo t;
    jboolean retV;
    if (cocos2d::JniHelper::getStaticMethodInfo(t,
                                                "org/cocos2dx/cpp/AppActivity",
                                                funcName,
                                                "()Z"))
    {
        
        retV = t.env->CallStaticBooleanMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
    
    return retV;
    
}

// Subscriptions

void NativeHelper::setSubscriptionCallback(std::function<void(bool)> callback){
    subscriptionsCallback = callback;
}

#endif
