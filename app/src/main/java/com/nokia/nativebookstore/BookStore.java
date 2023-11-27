package com.nokia.nativebookstore;

import com.nokia.nativebookstore.utils.CallbackJava;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

public class BookStore {

    static {
        System.loadLibrary("nativebookstore");
    }

    private List<Book> books;
    private Book lastUpdatedBook;

    public BookStore() {
        books = new ArrayList<>();
    }

    public void addBook(Book book) {
        books.add(book);
    }

    public void removeBook(Book book) {
        books.remove(book);
    }

    public Book findBookByISBN(double ISBN) {
        List<Book> bookList = books.stream().filter(book -> book.getISBN() == ISBN).collect(Collectors.toList());
        if (bookList.isEmpty()) {
            return null;
        }
        return bookList.get(0);
    }

    public List<Book> getAllBooks() {
        return books;
    }

    public int calculateTotalRevenue() {
        try {
            return calculateTotalRevenueInternal();
        } catch (Exception e) {
            e.printStackTrace();
            return -1;
        }
    }

    public void updateBook(Book book) {
        try {
            updateBookInternal(book);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void onBookUpdate(CallbackJava callback) {
        if (lastUpdatedBook != null) {
            callback.onCallbackSuccess("Book updated: " + lastUpdatedBook);
        } else {
            callback.onCallbackFailure("No Book updates found!");
        }
    }

    private native void updateBookInternal(Book book);

    private native int calculateTotalRevenueInternal();

    public Book getLastUpdatedBook() {
        return lastUpdatedBook;
    }

    public void setLastUpdatedBook(Book lastUpdatedBook) {
        this.lastUpdatedBook = lastUpdatedBook;
    }

    @Override
    public String toString() {
        return "books=\n" + books + '}';
    }
}
