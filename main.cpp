#include <iostream>
#include "Library.h"
#include "UserManager.h"

void printMenu(User* user) {
	std::cout << "\n\t\t\t************************************************\n";
	std::cout << "\t\t\t*                     MENU                     *\n";
	std::cout << "\t\t\t************************************************\n";
	if (user->getType() == UserType::ADMIN) {
		std::cout << "\t\t\t\t 1. Add book\n";
		std::cout << "\t\t\t\t 2. Remove book\n";
		std::cout << "\t\t\t\t 3. List books\n";
		std::cout << "\t\t\t\t 4. Search book\n";
		std::cout << "\t\t\t\t 5. Sort books by title\n";
		std::cout << "\t\t\t\t 6. Sort books by copies\n";
		std::cout << "\t\t\t\t 7. Add user\n";
		std::cout << "\t\t\t\t 8. Remove user\n";
		std::cout << "\t\t\t\t 9. Display users\n";
		std::cout << "\t\t\t\t10. Generate Reports\n";
		std::cout << "\t\t\t\t11. Log out\n";
		std::cout << "\t\t\t\t12. Exit\n";
	}
	else {
		std::cout << "\t\t\t\t1. List all books\n";
		std::cout << "\t\t\t\t2. List my borrowed books\n";
		std::cout << "\t\t\t\t3. Search book\n";
		std::cout << "\t\t\t\t4. Borrow book\n";
		std::cout << "\t\t\t\t5. Return book\n";
		std::cout << "\t\t\t\t6. Log out\n";
		std::cout << "\t\t\t\t7. Exit\n";
	}
	std::cout << "--------------------------------------------------\n";
	std::cout << "Please enter your choice and press enter: ";
}

int main() {

	/// Left to do 
	/// Load books borrowed by the User from the borrowedBooks file [Done]
	/// Display Books on sort [Done]
	/// fix UI [In Progress]
	/// Make README.MD file [In Progress]
	/// Make UML class diagrams [Done]
	/// 


	//For UI
	std::string Id = "ID";
	std::string Title = "Title";
	std::string auth = "Author";
	std::string nC = "Number of Copies";
	Id.resize(5, ' ');
	Title.resize(15, ' ');
	auth.resize(15, ' ');
	nC.resize(20, ' ');

	std::cout << "\t\t\t*------------------------------------------*" << std::endl;
	std::cout << "\t\t\t|      Library Management System           |" << std::endl;
	std::cout << "\t\t\t*------------------------------------------*" << std::endl;


	Library library;
	UserManager& userManager = UserManager::getInstance();

	// Pre-creating an admin user
	userManager.createUser("admin", "admin", "admin");
	User* loggedInUser = nullptr;

	while (true) {
		if (!loggedInUser) {
			std::cout << "\t\t\t*-----------------*" << std::endl;
			std::cout << "\t\t\t|      LOGIN      |" << std::endl;
			std::cout << "\t\t\t*-----------------*" << std::endl;
			std::string username;
			std::string password;
			std::cout << "Please enter your username: ";
			std::cin >> username;
			std::cout << "Please enter your password: ";
			std::cin >> password;
			loggedInUser = userManager.login(username, password);
			if (!loggedInUser) {
				std::cout << "Invalid login. Please try again.\n";
			}
		}
		else {
			printMenu(loggedInUser);
			int choice;
			std::cin >> choice;

			if (loggedInUser->getType() == UserType::ADMIN) {
				switch (choice) {
				case 1: {
					// Add book
					std::cout << "\n ~ Adding a Book ~\n" << std::endl;
					std::string title, author;
					int numberOfCopies;
					std::cout << "Enter title: ";
					std::cin >> title;
					std::cout << "Enter author: ";
					std::cin >> author;
					std::cout << "Enter number of copies: ";
					std::cin >> numberOfCopies;
					library.addBook(title, author, numberOfCopies);
					std::cout << title + " Added Successfully" << std::endl;
					break;
				}
				case 2: {
					std::cout << "\n ~ Removing a book ~\n" << std::endl;
					std::string id;
					std::cout << "Enter book id: ";
					std::cin >> id;
					library.removeBook(id);
					break;
				}
				case 3: {
					// List books
					std::cout << "\n ~ List of All Books ~\n" << std::endl;
					std::cout << "\n  " + Id + "|\t" << Title + "|\t" << auth + "|\t" << nC << std::endl;
					std::cout << library.listBooks();
					break;
				}
				case 4: {
					// Search book
					std::cout << "\n ~ Searching a Book ~\n" << std::endl;
					std::string title;
					std::cout << "Enter title: ";
					std::cin >> title;
					Book* book = library.searchBook(title);
					if (book) {
						std::cout << "\n  " + Id + "|\t" << Title + "|\t" << auth + "|\t" << nC << std::endl;
						std::cout << book->toString();
					}
					else {
						std::cout << "Book not found.\n";
					}
					break;
				}
				case 5: {
					// Sort books by title
					std::cout << "\n ~ Sorted Books by Title ~\n" << std::endl;
					std::cout << "\n  " + Id + "|\t" << Title + "|\t" << auth + "|\t" << nC << std::endl;
					library.sortBooksByTitle();
					std::cout << library.listBooks();
					break;
				}
				case 6: {
					// Sort books by copies
					std::cout << "\n ~ Sorted Books by Number of Copies~\n" << std::endl;
					std::cout << "\n  " + Id + "|\t" << Title + "|\t" << auth + "|\t" << nC << std::endl;
					library.sortBooksByCopies();
					std::cout << library.listBooks();
					break;
				}
				case 7: {
					// Add user
					std::cout << "\n ~ Creating a new user ~\n" << std::endl;
					std::string username, password, type;
					std::cout << "Enter username: ";
					std::cin >> username;
					std::cout << "Enter password: ";
					std::cin >> password;
					std::cout << "Enter type (admin/normal): ";
					std::cin >> type;
					userManager.createUser(username, password, type);
					break;
				}
				case 8: {
					// Remove user
					std::cout << "\n ~ Deleting an existing user ~\n" << std::endl;
					std::string username;
					std::cout << "Enter username: ";
					std::cin >> username;
					userManager.deleteUser(username);
					break;
				}
				case 9: {
					// Display users
					std::cout << "\n ~ List of all users ~\n" << std::endl;
					std::cout << userManager.displayUsers();
					break;
				}
				case 10:
					std::cout << "\n ~ Library Reports ~\n" << std::endl;
					std::cout << "\n[Access Logs]\n" << std::endl;
					std::cout << UserAdmin::getAllLogs("Userlogfile.txt") << std::endl;
					std::cout << "\n[Books Transactions]\n" << std::endl;
					std::cout << UserAdmin::getAllLogs("logfile.txt") << std::endl;

					break;
				case 11: {
					// Log out
					loggedInUser = nullptr;
					std::cout << "\nYou have been logged out !" << std::endl;
					break;
				}
				case 12: {
					// Exit
					return 0;
				}
				}
			}
			else {
				switch (choice) {
				case 1: {
					// List books
					std::cout << "\n ~ List of All Books ~\n" << std::endl;
					std::cout << "\n  " + Id + "|\t" << Title + "|\t" << auth + "|\t" << nC << std::endl;
					std::cout << library.listBooks();
					break;
				}
				case 2:
					std::cout << "\n ~ List of All Books I have Borrowed~\n" << std::endl;
					std::cout << loggedInUser->listBorrowedBooks();
					break;
				case 3: {
					// Search book
					std::cout << "\n ~ Searching a Book ~\n" << std::endl;
					std::string title;
					std::cout << "Enter title: ";
					std::cin >> title;
					Book* book = library.searchBook(title);
					if (book) {
						std::cout << "\n  " + Id + "|\t" << Title + "|\t" << auth + "|\t" << nC << std::endl;
						std::cout << book->toString() << std::endl;

					}
					else {
						std::cout << "Book not found.\n";
					}
					break;
				}
				case 4: {
					// Borrow book
					std::cout << "\n ~ Borrowing a Book ~\n" << std::endl;
					std::string title;
					std::cout << "Enter book title: ";
					std::cin >> title;
					library.borrowBook(title, loggedInUser);
					break;
				}
				case 5: {
					// Return book
					std::cout << "\n ~ Returning a Book ~\n" << std::endl;
					std::string title;
					std::cout << "Enter book title: ";
					std::cin >> title;
					library.returnBook(title, loggedInUser);
					break;
				}
				case 6: {
					// Log out
					loggedInUser = nullptr;
					break;
				}
				case 7: {
					// Exit
					return 0;
				}
				}
			}
		}
	}
	return 0;
}
