#include "Library.h"
#include "FileHandler.h"
#include <algorithm>
#include <iostream>

Library::Library() {
    FileHandler fileHandler;
    books = fileHandler.loadBooks();
}

void Library::addBook(const std::string& title, const std::string& author, int numberOfCopies) {
    int bookLength = static_cast<int>(books.size());
    std::unique_ptr<Book> newBook = std::make_unique<Book>(std::to_string(bookLength+1), title, author, numberOfCopies);
    books.push_back(std::move(newBook));
    FileHandler fileHandler;
    fileHandler.saveBooks(books);
}

void Library::removeBook(const std::string& id) {
    books.erase(std::remove_if(books.begin(), books.end(), [&id](const std::unique_ptr<Book>& book) {
        return book->getId() == id;
        }), books.end());
    FileHandler fileHandler;
    fileHandler.saveBooks(books);
}

Book* Library::searchBook(const std::string& title) {
    for (const auto& book : books) {
        if (book->getTitle() == title) {
            return book.get();
        }
    }
    return nullptr;
}

std::string Library::listBooks() {
    std::string output;
    for (const auto& book : books) {
        output += book->toString() + "\n";
    }
    return output;
}

void Library::sortBooksByTitle() {
    std::sort(books.begin(), books.end(), [](const std::unique_ptr<Book>& book1, const std::unique_ptr<Book>& book2) {
        return book1->getTitle() < book2->getTitle();
        });
    FileHandler fileHandler;
    fileHandler.saveBooks(books);
}

void Library::sortBooksByCopies() {
    std::sort(books.begin(), books.end(), [](const std::unique_ptr<Book>& book1, const std::unique_ptr<Book>& book2) {
        return book1->getNumberOfCopies() < book2->getNumberOfCopies();
        });
    FileHandler fileHandler;
    fileHandler.saveBooks(books);
}
void Library::borrowBook(const std::string& title, User* user) {
    Book* book = searchBook(title);
    //could have created a global object but I'm lazy
    FileHandler fileHandler;
    if (book && book->isAvailable()) {
        book->borrowBook();
        user->borrowBook(title);
        fileHandler.writeToBorrowedList(user->getUsername(),user->getBorrowedBooks());
        fileHandler.saveBooks(books);
        FileHandler::recordTransaction(title, "Borrow", user->getUsername());
        std::cout << "Book borrowed successfully.\n";
    }
    else {
        std::cout << "Book is not available for borrowing.\n";
    }
}

void Library::returnBook(const std::string& title, User* user) {
    Book* book = searchBook(title);
    FileHandler fileHandler;
    if (book && user->hasBorrowedBook(title)) {
        book->returnBook();
        user->returnBook(title);
        fileHandler.writeToBorrowedList(user->getUsername(), user->getBorrowedBooks());
        fileHandler.saveBooks(books);
        FileHandler::recordTransaction(title,"Return",user->getUsername());
        std::cout << "Book returned successfully.\n";
    }
    else {
        std::cout << "Book is not borrowed by the user.\n";
    }
}






Library::~Library() {
    // Since we are using unique_ptr, the memory will be automatically deallocated when the Library instance is destroyed.
    // We do not need to manually delete the pointers.
}
