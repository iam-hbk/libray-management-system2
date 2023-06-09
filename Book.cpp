#include "Book.h"
#include <stdexcept>

Book::Book(const std::string& id, const std::string& title, const std::string& author, int numberOfCopies)
	: id(id), title(title), author(author), numberOfCopies(numberOfCopies) {}

const std::string& Book::getId() const {
	return id;
}

const std::string& Book::getTitle() const {
	return title;
}

const std::string& Book::getAuthor() const {
	return author;
}

int Book::getNumberOfCopies() const {
	return numberOfCopies;
}

void Book::setId(const std::string& id) {
	this->id = id;
}

void Book::setTitle(const std::string& title) {
	this->title = title;
}

void Book::setAuthor(const std::string& author) {
	this->author = author;
}

void Book::setNumberOfCopies(int numberOfCopies) {
	this->numberOfCopies = numberOfCopies;
}

bool Book::isAvailable() const {
	return numberOfCopies > 0;
}

void Book::increaseCopies(int numberOfNewCopies) {
	if (numberOfNewCopies < 0) {
		throw std::invalid_argument("Number of new copies cannot be negative");
	}
	numberOfCopies += numberOfNewCopies;
}

void Book::borrowBook() {
	if (!isAvailable()) {
		throw std::runtime_error("Book is not available for borrowing");
	}
	--numberOfCopies;

}

void Book::returnBook() {
	++numberOfCopies;
}
std::string Book::toString() const {
	std::string id_ = getId();
	std::string title_ = getTitle();
	std::string author_ = getAuthor();
	std::string nC = std::to_string(numberOfCopies);
	id_.resize(5, ' ');
	title_.resize(15, ' ');
	author_.resize(15, ' ');
	nC.resize(5, ' ');
	std::string newline = "";
	newline.resize(80,'-');
	return  newline+"\n "+id_ + "\t\t" + title_ + "\t\t" + author_ + "\t\t" + "\t"+nC;

}
