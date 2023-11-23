package com.nokia.nativebookstore;

public class Book {
    private String name;
    private String author;
    private double ISBN;
    private int price;

    public Book() {
    }

    public Book(String name, String author, double ISBN, int price) {
        this.name = name;
        this.author = author;
        this.ISBN = ISBN;
        this.price = price;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getAuthor() {
        return author;
    }

    public void setAuthor(String author) {
        this.author = author;
    }

    public double getISBN() {
        return ISBN;
    }

    public void setISBN(double ISBN) {
        this.ISBN = ISBN;
    }

    public int getPrice() {
        return price;
    }

    public void setPrice(int price) {
        this.price = price;
    }

    @Override
    public String toString() {
        return name + ", " +
                author + ", " +
                ISBN + ", " +
                price + "\n";
    }
}
