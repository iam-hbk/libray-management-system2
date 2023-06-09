#include "UserAdmin.h"
#include "FileHandler.h"
UserAdmin::UserAdmin(const std::string& id, const std::string& username, const std::string& password, std::vector<std::string> brB)
	: User(id, username, password, brB, UserType::ADMIN) {}

std::string UserAdmin::getTypeString() const {
	return "admin";
}

std::string UserAdmin::getAllLogs(std::string file) {
	FileHandler fh;
	std::string content;
	for (std::string line : fh.readLogFile(file))
	{
		content += line + "\n";
	}
	return content;
}