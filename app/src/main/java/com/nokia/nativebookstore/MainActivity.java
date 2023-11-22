package com.nokia.nativebookstore;

import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;

import com.nokia.nativebookstore.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        BookStore bookStore = new BookStore();

        Book book1 = new Book("Book1", "Author1", 1111, 50);
        Book book2 = new Book("Book2", "Author2", 1112, 150);
        Book book3 = new Book("Book3", "Author3", 1113, 70);
        Book book4 = new Book("Book4", "Author4", 1114, 130);

        bookStore.addBook(book1);
        bookStore.addBook(book2);
        bookStore.addBook(book3);
        bookStore.addBook(book4);

        binding.sampleText.setText("Total Book revenue: " + bookStore.calculateTotalRevenue());
    }
}