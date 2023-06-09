#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Book.h"
#include "User.h"
#include "UserAdmin.h"

class FileHandler {
public:
	std::vector<std::unique_ptr<Book>> loadBooks();
	void saveBooks(const std::vector<std::unique_ptr<Book>>& books);
	std::vector<std::unique_ptr<User>> loadUsers();
	void saveUsers(const std::vector<std::unique_ptr<User>>& users);
	static std::string hash(const std::string& input);
	int getNumberOfBooks();
	int getNumberOfUsers();


	//Books logFile

	//book_sting    type_of_transaction     user_who_did_it     date_and_time
	static void recordTransaction(std::string book_string, std::string typeOfTransaction, std::string actioner);
	void writeToBorrowedList(std::string user, std::vector<std::string> books);
	//read from any given log file
	std::vector<std::string> readLogFile(std::string filename);

	//User logFile

	//who      when
	static void recordUserLogin(std::string user);
};
