#pragma once
#include <unordered_map>
#include <memory>
#include "User.h"
#include "UserAdmin.h"

class UserManager {
private:
    std::unordered_map<std::string, std::unique_ptr<User>> users;
    int maxID;

    UserManager();

    std::string getNewUserID();
    std::vector<std::unique_ptr<User>> getUserVector() const;
    User* getUserById(const std::string& id) const;

public:
    UserManager(const UserManager& other) = delete;
    UserManager& operator=(const UserManager& other) = delete;

    static UserManager& getInstance();

    User* login(const std::string& username, const std::string& password);
    void createUser(const std::string& username, const std::string& password, const std::string& type);
    void deleteUser(const std::string& username);
    void updateUser(const std::string& id, const std::string& username, const std::string& password, const std::string& type);

    std::string displayUsers() const;
};
