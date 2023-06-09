#pragma once
#include <string>
#include <vector>


enum class UserType { ADMIN, NORMAL };
class User {
private:
	std::string id;
	std::string username;
	std::string password;
	UserType type;
	std::vector<std::string> borrowedBooks;

public:
	User(const std::string& id, const std::string& username, const std::string& password, std::vector<std::string> brB, UserType type);

	const std::string& getId() const;
	const std::string& getUsername() const;
	const std::string& getPassword() const;
	const std::vector<std::string> getBorrowedBooks() const;
	UserType getType() const;
	virtual std::string getTypeString() const;

	void setId(const std::string& id);
	void setUsername(const std::string& username);
	void setPassword(const std::string& password);
	void setType(UserType type);

	void borrowBook(std::string title);
	void returnBook(std::string title);
	bool hasBorrowedBook(std::string title);

	std::string listBorrowedBooks();

	virtual std::string toString() const;
};
