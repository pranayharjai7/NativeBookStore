#include <jni.h>
#include <string>
#include "BookStore.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_nokia_nativebookstore_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jint JNICALL
Java_com_nokia_nativebookstore_BookStore_calculateTotalRevenueInternal(JNIEnv *env,
                                                                       jobject bookStoreObj) {
    BookStore bookStore(env, bookStoreObj);
    return bookStore.calculateTotalRevenue();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_nokia_nativebookstore_BookStore_updateBookInternal(JNIEnv *env, jobject bookStoreObj,
                                                            jobject bookObj) {
    BookStore bookStore(env, bookStoreObj);
    bookStore.updateBook(bookObj);
}
