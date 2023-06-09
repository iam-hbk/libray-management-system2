#define _CRT_SECURE_NO_WARNINGS
#include "FileHandler.h"
#include <fstream>
#include <thread>
#include <sstream>
#include <string>
#include <chrono>
#include <ctime>
#include <map>

std::vector<std::unique_ptr<Book>> FileHandler::loadBooks() {
	std::vector<std::unique_ptr<Book>> books;

	// Start a new thread to load the books.
	std::thread loadThread([&]() {
		std::ifstream file("books.txt");

		std::string line;
		while (std::getline(file, line)) {
			std::istringstream iss(line);

			std::string id;
			std::string title;
			std::string author;
			std::string numberOfCopies;

			if (!(iss >> id >> title >> author >> numberOfCopies)) {
				break;
			}

			std::unique_ptr<Book> book = std::make_unique<Book>(id, title, author, std::stoi(numberOfCopies));
			books.push_back(std::move(book));
		}
		});

	// Wait for the loading to finish before returning the books.
	loadThread.join();

	return books;
}

void FileHandler::saveBooks(const std::vector<std::unique_ptr<Book>>& books) {
	// Start a new thread to save the books.
	std::thread saveThread([&]() {
		std::ofstream file("books.txt");

		for (const auto& book : books) {
			file << book->getId() << " " << book->getTitle() << " " << book->getAuthor() << " " << book->getNumberOfCopies() << "\n";
		}
		});

	// Wait for the saving to finish before returning.
	saveThread.join();
}

void FileHandler::saveUsers(const std::vector<std::unique_ptr<User>>& users) {
	// Start a new thread to save the users.
	std::thread saveThread([&]() {
		std::ofstream file("users.txt");

		for (const auto& user : users) {
			file << user->getId() << " " << user->getUsername() << " " << user->getPassword() << " " << user->getTypeString() << "\n";
		}
		});

	// Wait for the saving to finish before returning.
	saveThread.join();
}

//Spliting helper function
std::vector<std::string> split(const std::string& str) {
	std::istringstream stream(str);
	std::vector<std::string> words;
	std::string word;

	while (std::getline(stream, word, ',')) {
		words.push_back(word);
	}
	return words;
}
std::vector<std::unique_ptr<User>> FileHandler::loadUsers() {
	//map (dict) to hold the borrowed books
	std::map<std::string, std::vector<std::string>> borrowedBooksMap;
	std::ifstream borrowedBooksFile("borrowedBooks.txt");
	std::string borrowedLine;
	while (std::getline(borrowedBooksFile, borrowedLine)) {
		std::istringstream iss(borrowedLine);
		std::string username;
		std::string books;
		if (!(iss >> username >> books)) {
			break;
		}
		borrowedBooksMap[username] = split(books);
	}

	std::vector<std::unique_ptr<User>> users;
	std::ifstream Userfile("users.txt");
	std::string line;

	while (std::getline(Userfile, line)) {
		std::istringstream iss(line);
		std::string id, username, password, userType;



		if (!(iss >> id >> username >> password >> userType)) {
			break;
		}

		if (userType == "Admin") {
			users.push_back(std::make_unique<UserAdmin>(id, username, password, borrowedBooksMap[username]));
		}
		else {
			users.push_back(std::make_unique<User>(id, username, password, borrowedBooksMap[username], UserType::NORMAL));
		}
	}

	return users;
}

std::string FileHandler::hash(const std::string& input) {
	// Simple hash function for demonstration purposes.
	// In a real-world application, I would use a more secure hashing algorithm.

	unsigned long hash = 5381;
	for (char c : input) {
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}
	return std::to_string(hash);
}
int FileHandler::getNumberOfBooks() {
	std::ifstream file("books.txt");
	int count = 0;

	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			count++;
		}
		file.close();
	}

	return count;
}

int FileHandler::getNumberOfUsers() {
	std::ifstream file("users.txt");
	int count = 0;

	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			count++;
		}
		file.close();
	}

	return count;
}

//book_sting    type_of_transaction     user_who_did_it     date_and_time
void FileHandler::recordTransaction(std::string book_string, std::string typeOfTransaction, std::string actioner) {
	// Get current time as time_point object
	auto now = std::chrono::system_clock::now();

	// Convert to time_t to get number of seconds elapsed since 01-01-1970
	std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

	// Convert to tm struct to get a familiar time format
	std::tm* timePtr = std::localtime(&currentTime);
	// Open the text file in append mode
	std::ofstream outfile("logfile.txt", std::ios_base::app | std::ios_base::out);

	book_string.resize(15, ' ');
	actioner.resize(15, ' ');
	outfile << book_string + "\t" << typeOfTransaction + "\t" << actioner + "\t" << std::asctime(timePtr);

}
std::vector<std::string> FileHandler::readLogFile(std::string filename) {
	std::vector<std::string> lines;
	std::ifstream infile(filename);

	std::string line;
	while (std::getline(infile, line)) {
		lines.push_back(line);
	}

	return lines;
}
void FileHandler::recordUserLogin(std::string user) {
	// Get current time as time_point object
	auto now = std::chrono::system_clock::now();
	user.resize(15, ' ');
	// Convert to time_t to get number of seconds elapsed since 01-01-1970
	std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

	// Convert to tm struct to get a familiar time format
	std::tm* timePtr = std::localtime(&currentTime);
	// Open the text file in append mode
	std::ofstream outfile("Userlogfile.txt", std::ios_base::app | std::ios_base::out);

	// Append the local date and time
	outfile << user + "\t" << std::asctime(timePtr);
};
void FileHandler::writeToBorrowedList(std::string user, std::vector<std::string> books) {
	auto now = std::chrono::system_clock::now();

	// Convert to time_t to get number of seconds elapsed since 01-01-1970
	std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

	// Convert to tm struct to get a familiar time format
	std::tm* timePtr = std::localtime(&currentTime);
	// Open the text file in append mode
	std::ofstream outfile("borrowedBooks.txt", std::ios_base::app | std::ios_base::out);


	std::string result;
	for (const auto& str : books) {
		if (!result.empty()) {
			result += ",";
		}
		result += str;
	}
	outfile << user + "\t" << result+"\n";
};