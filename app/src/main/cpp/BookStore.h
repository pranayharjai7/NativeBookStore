//
// Created by harjai on 22-Nov-23.
//

#ifndef NATIVEBOOKSTORE_BOOKSTORE_H
#define NATIVEBOOKSTORE_BOOKSTORE_H

#include <jni.h>

class BookStore {
private:
    JNIEnv *env;
    jobject bookStoreObj;
    jclass bookStore;
    jclass exception;
    jclass list;

    jobject getBookList();

    jsize getListSize(jobject list);

    void throwException(const char *string);


public:
    BookStore(JNIEnv *env, jobject bookStoreObj);

    ~BookStore();

    jint calculateTotalRevenue();

    void updateBook(jobject bookObj);

};

#endif //NATIVEBOOKSTORE_BOOKSTORE_H
