#pragma once
#include "Book.h"
#include <vector>
#include <memory>
#include "User.h"


enum class BookTransactionType { BORROW, RETURN };
class Library {
private:
	std::vector<std::unique_ptr<Book>> books;

public:
	Library();

	void addBook(const std::string& title, const std::string& author, int numberOfCopies);
	void removeBook(const std::string& id);
	Book* searchBook(const std::string& title);
	std::string listBooks();
	void sortBooksByTitle();
	void sortBooksByCopies();

	void borrowBook(const std::string& id, User* user);
	void returnBook(const std::string& id, User* user);

	~Library();
};
