#pragma once
#include <string>

class Book {
private:
    std::string id;
    std::string title;
    std::string author;
    int numberOfCopies;

public:
    Book(const std::string& id, const std::string& title, const std::string& author, int numberOfCopies);

    // Getter methods
    const std::string& getId() const;
    const std::string& getTitle() const;
    const std::string& getAuthor() const;
    int getNumberOfCopies() const;

    // Setter methods
    void setId(const std::string& id);
    void setTitle(const std::string& title);
    void setAuthor(const std::string& author);
    void setNumberOfCopies(int numberOfCopies);

    // Additional methods
    bool isAvailable() const;
    void increaseCopies(int numberOfNewCopies);
    void borrowBook();
    void returnBook();
    std::string toString() const;
};
