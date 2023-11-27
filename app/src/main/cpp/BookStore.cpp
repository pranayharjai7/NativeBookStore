//
// Created by harjai on 13-Nov-23.
//

#include "BookStore.h"

BookStore::BookStore(JNIEnv *env, jobject bookStoreObj) : env(env), bookStoreObj(bookStoreObj) {
    bookStore = env->GetObjectClass(bookStoreObj);
    exception = env->FindClass("java/lang/Exception");
    list = env->FindClass("java/util/List");
}

BookStore::~BookStore() {
    //TBD
}

jint BookStore::calculateTotalRevenue() {
    jobject books = BookStore::getBookList();
    jmethodID getPrice = env->GetMethodID(env->FindClass("com/nokia/nativebookstore/Book"),
                                          "getPrice", "()I");
    jsize listSize = getListSize(books);
    jmethodID get = env->GetMethodID(list, "get", "(I)Ljava/lang/Object;");

    jint totalRevenue = 0;
    for (jsize i = 0; i < listSize; i++) {
        jobject book = env->CallObjectMethod(books, get, i);
        jint price = env->CallIntMethod(book, getPrice);

        //price exception
        if (price < 0) {
            throwException("Invalid Price Detected");
            return -1;
        }

        totalRevenue += price;
    }

    return totalRevenue;
}

void BookStore::updateBook(jobject bookObj) {
    jfieldID lastUpdatedBook_ID = env->GetFieldID(bookStore, "lastUpdatedBook", "Lcom/nokia/nativebookstore/Book;");

    jclass book = env->GetObjectClass(bookObj);

    //Getting new fields from sent parameter "book"
    jfieldID name_ID = env->GetFieldID(book, "name", "Ljava/lang/String;");
    auto newName = static_cast<jstring>(env->GetObjectField(bookObj, name_ID));

    jfieldID author_ID = env->GetFieldID(book, "author", "Ljava/lang/String;");
    auto newAuthor = static_cast<jstring>(env->GetObjectField(bookObj, author_ID));

    jfieldID price_ID = env->GetFieldID(book, "price", "I");
    jint newPrice = env->GetIntField(bookObj, price_ID);

    //getting ISBN
    jfieldID ISBN_ID = env->GetFieldID(book, "ISBN", "D");
    jdouble ISBN = env->GetDoubleField(bookObj, ISBN_ID);

    //calling findBookByISBN(ISBN) from java
    jmethodID findBookByISBN_ID = env->GetMethodID(bookStore, "findBookByISBN",
                                                   "(D)Lcom/nokia/nativebookstore/Book;");
    jobject foundBook = env->CallObjectMethod(bookStoreObj, findBookByISBN_ID, ISBN);

    if (foundBook != nullptr) {
        env->SetObjectField(foundBook, name_ID, newName);
        env->SetObjectField(foundBook, author_ID, newAuthor);
        env->SetIntField(foundBook, price_ID, newPrice);

        env->SetObjectField(bookStoreObj, lastUpdatedBook_ID, foundBook);
    } else {
        throwException("Book Not Found");
    }
}

jobject BookStore::getBookList() {
    jmethodID getAllBooksMethodID = env->GetMethodID(bookStore, "getAllBooks",
                                                     "()Ljava/util/List;");
    return env->CallObjectMethod(bookStoreObj, getAllBooksMethodID);
}

jsize BookStore::getListSize(jobject list) {
    jmethodID sizeID = env->GetMethodID(this->list, "size", "()I");
    return env->CallIntMethod(list, sizeID);
}

void BookStore::throwException(const char *message) {
    if (!env->ExceptionCheck()) {
        env->ThrowNew(exception, message);
    }
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

