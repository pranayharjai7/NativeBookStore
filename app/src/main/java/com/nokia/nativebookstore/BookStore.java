package com.nokia.nativebookstore;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

public class BookStore {

    static {
        System.loadLibrary("nativebookstore");
    }

    private List<Book> books;

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
        return books.stream()
                .filter(book -> book.getISBN() == ISBN)
                .collect(Collectors.toList())
                .get(0);
    }

    public List<Book> getAllBooks() {
        return books;
    }

    public native int calculateTotalRevenue();
}
