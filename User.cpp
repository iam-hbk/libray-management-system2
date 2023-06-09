#include "User.h"

User::User(const std::string& id, const std::string& username, const std::string& password, std::vector<std::string> brB, UserType type)
    : id(id), username(username), password(password),borrowedBooks(brB), type(type) {
}

const std::string& User::getId() const {
    return id;
}

const std::string& User::getUsername() const {
    return username;
}

const std::string& User::getPassword() const {
    return password;
}
const std::vector<std::string> User::getBorrowedBooks() const {
    return borrowedBooks;
}

UserType User::getType() const {
    return type;
}

std::string User::getTypeString() const {
    if (type == UserType::ADMIN) {
        return "admin";
    }
    else {
        return "normal";
    }
}

void User::setId(const std::string& id) {
    this->id = id;
}

void User::setUsername(const std::string& username) {
    this->username = username;
}

void User::setPassword(const std::string& password) {
    this->password = password;
}

void User::setType(UserType type) {
    this->type = type;
}

std::string User::toString() const {
    return "ID: " + id + ", Username: " + username + ", Type: " + (type == UserType::ADMIN ? "Admin" : "Normal");
}


void User::borrowBook(std::string title){
    borrowedBooks.push_back(title);
}
void User::returnBook(std::string title){
    borrowedBooks.erase(std::remove(borrowedBooks.begin(), borrowedBooks.end(), title), borrowedBooks.end());

}
bool User::hasBorrowedBook(std::string title) {
    return std::find(borrowedBooks.begin(), borrowedBooks.end(), title) != borrowedBooks.end();
}
std::string User::listBorrowedBooks() {
    std::string output;
    for (const auto& book : borrowedBooks) {
        output += book + "\n";
    }
    return output;
}