#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

class Book {
private:
    std::string title;
    std::string author;
    int publicationYear;

public:
    Book(const std::string& title, const std::string& author, int publicationYear)
        : title(title), author(author), publicationYear(publicationYear) {}

    std::string getTitle() const {
        return title;
    }

    std::string getAuthor() const {
        return author;
    }

    int getPublicationYear() const {
        return publicationYear;
    }

    bool contains(const std::string& keyword) const {
        return title.find(keyword) != std::string::npos || author.find(keyword) != std::string::npos;
    }

    bool operator<(const Book& other) const {
        return title < other.title;
    }
};

class Library {
private:
    std::vector<Book> books;

public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void removeBook(const std::string& title) {
        auto it = std::find_if(books.begin(), books.end(), [&title](const Book& book) {
            return book.getTitle() == title;
            });

        if (it != books.end()) {
            books.erase(it);
            std::cout << "Książka o tytule '" << title << "' została usunięta." << std::endl;
        }
        else {
            std::cout << "Książka o tytule '" << title << "' nie została znaleziona." << std::endl;
        }
    }

    void displayBooks() const {
        std::cout << "Lista książek w bibliotece:" << std::endl;
        for (const auto& book : books) {
            std::cout << "Tytuł: " << book.getTitle() << ", Autor: " << book.getAuthor() << ", Rok wydania: " << book.getPublicationYear() << std::endl;
        }
    }

    void searchBooks(const std::string& keyword) const {
        std::cout << "Wyszukiwanie książek zawierających '" << keyword << "':" << std::endl;

        bool foundBooks = false;
        for (const auto& book : books) {
            if (book.contains(keyword)) {
                std::cout << "Tytuł: " << book.getTitle() << ", Autor: " << book.getAuthor() << ", Rok wydania: " << book.getPublicationYear() << std::endl;
                foundBooks = true;
            }
        }

        if (!foundBooks) {
            std::cout << "Nie znaleziono książek pasujących do kryteriów wyszukiwania." << std::endl;
        }
    }

    void sortBooksByTitle() {
        std::sort(books.begin(), books.end());
    }

    void saveBooksToFile(const std::string& fileName) const {
        std::ofstream file(fileName);
        if (file.is_open()) {
            for (const auto& book : books) {
                file << book.getTitle() << "," << book.getAuthor() << "," << book.getPublicationYear() << "\n";
            }
            std::cout << "Zapisano dane do pliku '" << fileName << "'." << std::endl;
        }
        else {
            std::cout << "Nie można otworzyć pliku do zapisu." << std::endl;
        }
    }

    void loadBooksFromFile(const std::string& fileName) {
        std::ifstream file(fileName);
        if (file.is_open()) {
            books.clear();
            std::string line;
            while (std::getline(file, line)) {
                size_t pos1 = line.find(',');
                size_t pos2 = line.rfind(',');

                if (pos1 != std::string::npos && pos2 != std::string::npos) {
                    std::string title = line.substr(0, pos1);
                    std::string author = line.substr(pos1 + 1, pos2 - pos1 - 1);
                    int publicationYear = std::stoi(line.substr(pos2 + 1));
                    books.emplace_back(title, author, publicationYear);
                }
            }
            std::cout << "Wczytano dane z pliku '" << fileName << "'." << std::endl;
        }
        else {
            std::cout << "Nie można otworzyć pliku do odczytu." << std::endl;
        }
    }
};

int main() {
    setlocale(LC_CTYPE, "Polish");
    Library library;

    library.addBook(Book("Harry Potter and the Philosopher's Stone", "J.K. Rowling", 1997));
    library.addBook(Book("To Kill a Mockingbird", "Harper Lee", 1960));
    library.addBook(Book("1984", "George Orwell", 1949));


    library.displayBooks();

    library.removeBook("To Kill a Mockingbird");

    library.displayBooks();

    library.searchBooks("Potter");

    library.sortBooksByTitle();
    library.displayBooks();

    library.saveBooksToFile("books.txt");

    library.removeBook("Harry Potter and the Philosopher's Stone");
    library.removeBook("1984");

    library.displayBooks();

    library.loadBooksFromFile("books.txt");

    library.displayBooks();

    return 0;
}
