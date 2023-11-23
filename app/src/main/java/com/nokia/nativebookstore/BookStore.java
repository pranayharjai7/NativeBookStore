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
        List<Book> bookList = books.stream()
                .filter(book -> book.getISBN() == ISBN)
                .collect(Collectors.toList());
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

    private native void updateBookInternal(Book book);

    private native int calculateTotalRevenueInternal();

    @Override
    public String toString() {
        return "books=\n" + books +
                '}';
    }
}
