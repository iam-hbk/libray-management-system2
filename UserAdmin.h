#pragma once

#include "User.h"

class UserAdmin : public User {
public:
    UserAdmin(const std::string& id, const std::string& username, const std::string& password, std::vector<std::string> brB);
    static std::string getAllLogs(std::string file);
    std::string getTypeString() const override;
};
