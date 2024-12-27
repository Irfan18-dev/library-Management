#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_TITLE_LEN 50
#define MAX_AUTHOR_LEN 50

typedef struct {
    int id;
    char title[MAX_TITLE_LEN];
    char author[MAX_AUTHOR_LEN];
    int available; // 1 if available, 0 if borrowed
} Book;

Book library[MAX_BOOKS];
int bookCount = 0;

// Function to add a new book
void addBook() {
    if (bookCount >= MAX_BOOKS) {
        printf("Library is full. Cannot add more books.\n");
        return;
    }

    Book newBook;
    newBook.id = bookCount + 1;

    printf("Enter book title: ");
    getchar(); // Clear newline from input buffer
    fgets(newBook.title, MAX_TITLE_LEN, stdin);
    newBook.title[strcspn(newBook.title, "\n")] = 0; // Remove newline

    printf("Enter book author: ");
    fgets(newBook.author, MAX_AUTHOR_LEN, stdin);
    newBook.author[strcspn(newBook.author, "\n")] = 0; // Remove newline

    newBook.available = 1; // Mark the book as available
    library[bookCount++] = newBook;

    printf("Book added successfully! ID: %d\n", newBook.id);
}

// Function to display all books
void viewBooks() {
    if (bookCount == 0) {
        printf("No books available in the library.\n");
        return;
    }

    printf("\nLibrary Books:\n");
    printf("---------------------------------------------------------------\n");
    printf("ID   Title                          Author               Status\n");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < bookCount; i++) {
        printf("%-4d %-30s %-20s %s\n", 
               library[i].id, library[i].title, library[i].author,
               library[i].available ? "Available" : "Borrowed");
    }
}

// Function to borrow a book
void borrowBook() {
    if (bookCount == 0) {
        printf("No books available to borrow.\n");
        return;
    }

    int bookId;
    printf("Enter the ID of the book you want to borrow: ");
    scanf("%d", &bookId);

    if (bookId < 1 || bookId > bookCount) {
        printf("Invalid book ID.\n");
        return;
    }

    if (library[bookId - 1].available) {
        library[bookId - 1].available = 0;
        printf("You have successfully borrowed: %s\n", library[bookId - 1].title);
    } else {
        printf("Sorry, the book is currently borrowed.\n");
    }
}

// Function to return a book
void returnBook() {
    if (bookCount == 0) {
        printf("No books to return.\n");
        return;
    }

    int bookId;
    printf("Enter the ID of the book you want to return: ");
    scanf("%d", &bookId);

    if (bookId < 1 || bookId > bookCount) {
        printf("Invalid book ID.\n");
        return;
    }

    if (!library[bookId - 1].available) {
        library[bookId - 1].available = 1;
        printf("You have successfully returned: %s\n", library[bookId - 1].title);
    } else {
        printf("The book is already available in the library.\n");
    }
}

// Main function
int main() {
    int choice;

    do {
        printf("\nLibrary Management System\n");
        printf("1. Add Book\n");
        printf("2. View Books\n");
        printf("3. Borrow Book\n");
        printf("4. Return Book\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                viewBooks();
                break;
            case 3:
                borrowBook();
                break;
            case 4:
                returnBook();
                break;
            case 5:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}