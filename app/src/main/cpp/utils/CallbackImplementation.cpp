//
// Created by harjai on 27-Nov-23.
//

#include "CallbackInterface.h"
#include <iostream>
#include <jni.h>
#include <android/log.h>

class CallbackImplementation : public CallbackInterface {
public:
    void onCallbackSuccess(char *message) override {
        __android_log_print(ANDROID_LOG_INFO, "Success", "log: %s", message);
    }

    void onCallbackFailure(char *message) override {
        __android_log_print(ANDROID_LOG_INFO, "Failure", "log: %s", message);
    }
};

extern "C"
JNIEXPORT void JNICALL
Java_com_nokia_nativebookstore_BookStore_onCallbackSuccessCppInternal(JNIEnv *env,
                                                                      jobject bookStoreObj,
                                                                      jstring message) {
    const char *info = env->GetStringUTFChars(message, nullptr);
    CallbackImplementation callbackImplementation;
    callbackImplementation.onCallbackSuccess(const_cast<char *>(info));
    // Release the string
    env->ReleaseStringUTFChars(message, info);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_nokia_nativebookstore_BookStore_onCallbackFailureCppInternal(JNIEnv *env, jobject thiz,
                                                                      jstring message) {
    const char *info = env->GetStringUTFChars(message, nullptr);
    CallbackImplementation callbackImplementation;
    callbackImplementation.onCallbackFailure(const_cast<char *>(info));
    // Release the string
    env->ReleaseStringUTFChars(message, info);
}