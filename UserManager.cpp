#include "UserManager.h"
#include <iostream>
#include "FileHandler.h"

UserManager::UserManager() : maxID(0) {
	FileHandler fileHandler;
	std::vector<std::unique_ptr<User>> loadedUsers = fileHandler.loadUsers();
	for (auto& user : loadedUsers) {
		int id = std::stoi(user->getId());
		if (id > maxID) {
			maxID = id;
		}
		users[user->getUsername()] = std::move(user);
	}
}

UserManager& UserManager::getInstance() {
	static UserManager instance;
	return instance;
}

std::string UserManager::getNewUserID() {
	maxID += 1;
	return std::to_string(maxID);
}

User* UserManager::login(const std::string& username, const std::string& password) {
	auto iter = users.find(username);
	if (iter != users.end()) {
		User* user = iter->second.get();
		if (user->getPassword() == FileHandler::hash(password)) {
			FileHandler::recordUserLogin(username);
			return user;

		}
	}
	return nullptr;
}

void UserManager::createUser(const std::string& username, const std::string& password, const std::string& type) {
	std::string id = getNewUserID();
	std::vector<std::string> brB;
	if (type == "admin") {
		users[username] = std::make_unique<UserAdmin>(id, username, FileHandler::hash(password), brB);
	}
	else {
		users[username] = std::make_unique<User>(id, username, FileHandler::hash(password), brB, UserType::NORMAL);
	}

	FileHandler fileHandler;
	fileHandler.saveUsers(getUserVector());
}

void UserManager::deleteUser(const std::string& username) {
	auto iter = users.find(username);
	if (iter != users.end()) {
		users.erase(iter);

		FileHandler fileHandler;
		fileHandler.saveUsers(getUserVector());
	}
}

void UserManager::updateUser(const std::string& id, const std::string& username, const std::string& password, const std::string& type) {
	User* user = getUserById(id);
	if (user) {
		user->setUsername(username);
		user->setPassword(FileHandler::hash(password));

		if (type == "admin") {
			user->setType(UserType::ADMIN);
		}
		else {
			user->setType(UserType::NORMAL);
		}

		FileHandler fileHandler;
		fileHandler.saveUsers(getUserVector());
	}
}

std::string UserManager::displayUsers() const {
	std::string output;
	for (const auto& pair : users) {
		output += pair.second->toString() + "\n";
	}
	return output;
}

std::vector<std::unique_ptr<User>> UserManager::getUserVector() const {
	std::vector<std::unique_ptr<User>> userVector;
	for (const auto& pair : users) {
		userVector.push_back(std::make_unique<User>(*pair.second));
	}
	return userVector;
}

User* UserManager::getUserById(const std::string& id) const {
	for (const auto& pair : users) {
		if (pair.second->getId() == id) {
			return pair.second.get();
		}
	}
	return nullptr;
}
