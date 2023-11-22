//
// Created by harjai on 13-Nov-23.
//

#include <jni.h>

jobject getBookList(JNIEnv *env, jobject obj, jclass bookStore);

jmethodID getPriceMethodID(JNIEnv *env);

jsize getListSize(JNIEnv *env, jobject list);

jmethodID listGet(JNIEnv *env);

jclass List;

extern "C"
JNIEXPORT jint JNICALL
Java_com_nokia_nativebookstore_BookStore_calculateTotalRevenue(JNIEnv *env, jobject obj) {
    jclass bookStore = env->GetObjectClass(obj);

    jobject bookList = getBookList(env, obj, bookStore);
    List = env->GetObjectClass(bookList);

    jmethodID getPrice = getPriceMethodID(env);
    jint totalRevenue = 0;

    jsize listSize = getListSize(env, bookList);
    jmethodID get = listGet(env);

    for (jsize i = 0; i < listSize; i++) {
        jobject book = env->CallObjectMethod(bookList, get, i);
        jint price = env->CallIntMethod(book, getPrice);
        totalRevenue += price;
    }

    return totalRevenue;
}

jmethodID listGet(JNIEnv *env) {
    return env->GetMethodID(List, "get", "(I)Ljava/lang/Object;");
}

jsize getListSize(JNIEnv *env, jobject list) {
    return env->CallIntMethod(list, env->GetMethodID(List, "size", "()I"));
}

jmethodID getPriceMethodID(JNIEnv *env) {
    return env->GetMethodID(env->FindClass("com/nokia/nativebookstore/Book"),
                            "getPrice", "()I");
}

jobject getBookList(JNIEnv *env, jobject obj, jclass bookStore) {
    jmethodID getAllBooksMethodID = env->GetMethodID(bookStore, "getAllBooks",
                                                     "()Ljava/util/List;");
    return env->CallObjectMethod(obj, getAllBooksMethodID);
}
