#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> 
using namespace std;

// Utility function to clear screen
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else   
    system("clear");
#endif
}

// Utility function to convert string to lowercase 
string toLower(const string& str) {
    string lowerStr = "";
    for (size_t i = 0; i < str.length(); ++i) {
        char ch = str[i];
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        lowerStr += ch;
    }
    return lowerStr;
}

// Book class
class Book {
private:
    int id;
    string name;
    string author;
    string category;

public:
    Book() : id(0), name(""), author(""), category("") {}
    Book(int i, const string& n, const string& a, const string& c)
        : id(i), name(n), author(a), category(c) {
    }

    int getId() const { return id; }
    string getName() const { return name; }
    string getAuthor() const { return author; }
    string getCategory() const { return category; }

    void setName(const string& n) { name = n; }
    void setAuthor(const string& a) { author = a; }
    void setCategory(const string& c) { category = c; }


    void display() const {
        cout << left
            << setw(5) << id
            << setw(60) << name
            << setw(25) << author
            << setw(15) << category
            << endl;
    }

    // Serialize book to string for file storage
    string serialize() const {
        return to_string(id) + "|" + name + "|" + author + "|" + category;
    }

    // Deserialize book from string line
    static bool deserialize(const string& line, Book& book) {
        size_t len = line.length();
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        size_t pos3 = line.find('|', pos2 + 1);

        // Manual boundary checks instead of using npos
        if (pos1 >= len || pos2 >= len || pos3 >= len || pos1 == 0 || pos2 <= pos1 + 1 || pos3 <= pos2 + 1)
            return false;

        // Check ID is numeric
        string idStr = line.substr(0, pos1);
        for (char ch : idStr) {
            if (ch < '0' || ch > '9') return false;
        }

        book.id = stoi(idStr);
        book.name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        book.author = line.substr(pos2 + 1, pos3 - pos2 - 1);
        book.category = line.substr(pos3 + 1);

        return true;
    }

};

// IssuedBook class
class IssuedBook {
private:
    int bookId;
    string bookName;
    string studentName;
    int studentId;

public:
    IssuedBook() : bookId(0), bookName(""), studentName(""), studentId(0) {}
    IssuedBook(int bId, const string& bName, const string& sName, int sId)
        : bookId(bId), bookName(bName), studentName(sName), studentId(sId) {
    }

    int getBookId() const { return bookId; }
    string getBookName() const { return bookName; }
    string getStudentName() const { return studentName; }
    int getStudentId() const { return studentId; }

    void display() const {
        cout << left<< setw(15) << ("Book ID: " + to_string(bookId))<< setw(40) << (" Book Name: " + bookName) << setw(25) << ("Issued To: " + studentName) << setw(15) << ("Student ID: " + to_string(studentId))<< endl;
    }
};

// Base User class
class User {
public:
    virtual void menu() = 0; //  virtual function 
    virtual ~User() {}
};

// Forward declaration of Library for friend access
class Library;

// Student class
class Student : public User {
private:
    Library* library;

public:
    Student(Library* lib) : library(lib) {}
    void menu() override;
};

// Librarian class
class Librarian : public User {
private:
    Library* library;
    string passwordFile;

    string librarianPassword;

    void loadPassword();
    bool login();

public:
    Librarian(Library* lib, const string& passFile = "password.txt")
        : library(lib), passwordFile(passFile) {
        loadPassword();
    }
    void menu() override;
};

// Library class managing books and issued books
class Library {
private:
    Book* books;
    int bookCount;
    int bookCapacity;

    IssuedBook* issuedBooks;
    int issuedCount;
    int issuedCapacity;

    const string booksFile = "books.txt";
    const string issuedBooksFile = "issue.txt";

    friend class Student;
    friend class Librarian;

    // Helper methods
    void initializeBooks();

    Book* findBookById(int id);
    Book* findBookByName(const string& name);
    bool isBookIssued(int bookId);

    int generateNextBookId(const string& category);

    void saveIssuedBooks();
    void loadIssuedBooks();

    void saveBooks();
    void loadBooks();

    void displayBooksByCategory(const string& category);
    void displayAllBooks();

    void addBookDynamic(const Book& book);
    void addIssuedBookDynamic(const IssuedBook& ib);
    void removeIssuedBookAt(int index);

public:
    Library();
    ~Library();

    // Student functionalities
    void studentViewBooks();
    void studentSearchBook();

    // Librarian functionalities
    void librarianViewBooks();
    void librarianSearchBook();
    void librarianModifyBook();
    void librarianAddBook();
    void librarianDeleteBook();
    void librarianIssueBook();
    void librarianViewIssuedBooks();
    void librarianReturnBook();
};

// Implementation of Library methods

Library::Library() {
    bookCapacity = 10;
    bookCount = 0;
    books = new Book[bookCapacity];

    issuedCapacity = 10;
    issuedCount = 0;
    issuedBooks = new IssuedBook[issuedCapacity];

    loadBooks();
    loadIssuedBooks();

    // If no books loaded, initialize defaults and save
    if (bookCount == 0) {
        //initializeBooks();
        saveBooks();
    }
}

Library::~Library() {
    delete[] books;
    delete[] issuedBooks;
}

void Library::addBookDynamic(const Book& book) {
    if (bookCount == bookCapacity) {
        // Resize array (double capacity)
        int newCapacity = bookCapacity * 2;
        Book* newBooks = new Book[newCapacity];
        for (int i = 0; i < bookCount; ++i) {
            newBooks[i] = books[i];
        }
        delete[] books;
        books = newBooks;
        bookCapacity = newCapacity;
    }
    books[bookCount++] = book;
}

void Library::addIssuedBookDynamic(const IssuedBook& ib) {
    if (issuedCount == issuedCapacity) {
        int newCapacity = issuedCapacity * 2;
        IssuedBook* newIssued = new IssuedBook[newCapacity];
        for (int i = 0; i < issuedCount; ++i) {
            newIssued[i] = issuedBooks[i];
        }
        delete[] issuedBooks;
        issuedBooks = newIssued;
        issuedCapacity = newCapacity;
    }
    issuedBooks[issuedCount++] = ib;
}

void Library::removeIssuedBookAt(int index) {
    if (index < 0 || index >= issuedCount) return;
    for (int i = index; i < issuedCount - 1; ++i) {
        issuedBooks[i] = issuedBooks[i + 1];
    }
    --issuedCount;
}

void Library::initializeBooks() {
    if (bookCount > 0) return;

    addBookDynamic(Book(1, "To Kill a Mockingbird", "Harper Lee", "Novels"));
    addBookDynamic(Book(2, "1984", "George Orwell", "Novels"));
    addBookDynamic(Book(3, "Pride and Prejudice", "Jane Austen", "Novels"));

    addBookDynamic(Book(101, "Fundamentals of Physics", "Halliday & Resnick", "Physics"));
    addBookDynamic(Book(102, "Concepts of Physics", "H.C. Verma", "Physics"));
    addBookDynamic(Book(103, "Introduction to Electrodynamics", "David J. Griffiths", "Physics"));

    addBookDynamic(Book(201, "Calculus", "James Stewart", "Calculus"));
    addBookDynamic(Book(202, "Calculus Made Easy", "Silvanus P. Thompson", "Calculus"));
    addBookDynamic(Book(203, "Advanced Calculus", "Patrick M. Fitzpatrick", "Calculus"));
}

Book* Library::findBookById(int id) {
    for (int i = 0; i < bookCount; ++i) {
        if (books[i].getId() == id) return &books[i];
    }
    return nullptr;
}

Book* Library::findBookByName(const string& name) {
    string searchName = toLower(name);
    for (int i = 0; i < bookCount; ++i) {
        if (toLower(books[i].getName()) == searchName) return &books[i];
    }
    return nullptr;
}

bool Library::isBookIssued(int bookId) {
    for (int i = 0; i < issuedCount; ++i) {
        if (issuedBooks[i].getBookId() == bookId) return true;
    }
    return false;
}

int Library::generateNextBookId(const string& category) {
    int base = 0;
    if (category == "Novels") base = 0;
    else if (category == "Physics") base = 100;
    else if (category == "Calculus") base = 200;
    else base = 300;

    int maxId = base;
    for (int i = 0; i < bookCount; ++i) {
        if (books[i].getCategory() == category && books[i].getId() > maxId)
            maxId = books[i].getId();
    }
    return maxId + 1;
}

void Library::saveIssuedBooks() {
    ofstream fout(issuedBooksFile.c_str());
    for (int i = 0; i < issuedCount; ++i) {
        fout << issuedBooks[i].getBookId() << "|" << issuedBooks[i].getBookName() << "|"
            << issuedBooks[i].getStudentName() << "|" << issuedBooks[i].getStudentId() << "\n";
    }
    fout.close();
}

void Library::loadIssuedBooks() {
    issuedCount = 0;
    ifstream fin(issuedBooksFile.c_str());
    if (!fin) return;
    string line;
    while (getline(fin, line)) {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        size_t pos3 = line.find('|', pos2 + 1);
        if (pos1 == string::npos || pos2 == string::npos || pos3 == string::npos) continue;
        int bId = 0, sId = 0;
        try {
            bId = stoi(line.substr(0, pos1));
            sId = stoi(line.substr(pos3 + 1));
        }
        catch (...) {
            continue; // skip malformed lines
        }
        string bName = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string sName = line.substr(pos2 + 1, pos3 - pos2 - 1);
        addIssuedBookDynamic(IssuedBook(bId, bName, sName, sId));
    }
    fin.close();
}

void Library::saveBooks() {
    ofstream fout(booksFile.c_str());
    for (int i = 0; i < bookCount; ++i) {
        fout << books[i].serialize() << "\n";
    }
    fout.close();
}

void Library::loadBooks() {
    bookCount = 0;
    ifstream fin(booksFile.c_str());
    if (!fin) return;
    string line;
    Book temp;
    while (getline(fin, line)) {
        if (Book::deserialize(line, temp)) {
            addBookDynamic(temp);
        }
    }
    fin.close();
}

void Library::displayBooksByCategory(const string& category) {
    cout << "\nBooks in category: " << category << "\n";
    cout << "----------------------------------------\n";
    bool found = false;
    for (int i = 0; i < bookCount; ++i) {
        if (books[i].getCategory() == category) {
            books[i].display();
            found = true;
        }
    }
    if (!found) cout << "No books found in this category.\n";
}

void Library::displayAllBooks() {
    string categories[3] = { "Novels", "Physics", "Calculus" };
    for (int i = 0; i < 3; ++i) {



        displayBooksByCategory(categories[i]);
        cout << "\n";
    }
}

// Student functionalities
void Library::studentViewBooks() {
    clearScreen();
    cout << "=== View All Books ===\n";
    displayAllBooks();
}

void Library::studentSearchBook() {
    clearScreen();
    cout << "=== Search Book ===\n";
    cout << "Search by:\n1. Name\n2. ID\nEnter choice: ";
    int choice;
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        cout << "Enter book name: ";
        string name;
        getline(cin, name);
        Book* book = findBookByName(name);
        if (book) {
            cout << "Book found:\n";
            book->display();
        }
        else {
            cout << "Book not found.\n";
        }
    }
    else if (choice == 2) {
        cout << "Enter book ID: ";
        int id;
        cin >> id;
        cin.ignore();
        Book* book = findBookById(id);
        if (book) {
            cout << "Book found:\n";
            book->display();
        }
        else {
            cout << "Book not found.\n";
        }
    }
    else {
        cout << "Invalid choice.\n";
    }
}

// Librarian functionalities
void Library::librarianViewBooks() {
    clearScreen();
    cout << "=== View All Books ===\n";
    displayAllBooks();
}

void Library::librarianSearchBook() {
    clearScreen();
    cout << "=== Search Book ===\n";
    cout << "Search by:\n1. Name\n2. ID\nEnter choice: ";
    int choice;
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        cout << "Enter book name: ";
        string name;
        getline(cin, name);
        Book* book = findBookByName(name);
        if (book) {
            cout << "Book found:\n";
            book->display();
        }
        else {
            cout << "Book not found.\n";
        }
    }
    else if (choice == 2) {
        cout << "Enter book ID: ";
        int id;
        cin >> id;
        cin.ignore();
        Book* book = findBookById(id);
        if (book) {
            cout << "Book found:\n";
            book->display();
        }
        else {
            cout << "Book not found.\n";
        }
    }
    else {
        cout << "Invalid choice.\n";
    }
}

void Library::librarianModifyBook() {
    clearScreen();
    cout << "=== Modify Book ===\n";
    cout << "Search book to modify\n";
    cout << "1. By name\n2. By ID\nEnter choice: ";
    int choice;
    cin >> choice;
    cin.ignore();
    Book* book = nullptr;

    if (choice == 1) {
        cout << "Enter book name: ";
        string name;
        getline(cin, name);
        book = findBookByName(name);
    }
    else if (choice == 2) {
        cout << "Enter book ID: ";
        int id;
        cin >> id;
        cin.ignore();
        book = findBookById(id);
    }
    else {
        cout << "Invalid choice.\n";
        return;
    }

    if (!book) {
        cout << "Book not found.\n";
        return;
    }

    cout << "Current details:\n";
    book->display();

    cout << "Enter new name (leave empty to keep current): ";
    string newName;
    getline(cin, newName);
    if (!newName.empty()) book->setName(newName);

    cout << "Enter new author (leave empty to keep current): ";
    string newAuthor;
    getline(cin, newAuthor);
    if (!newAuthor.empty()) book->setAuthor(newAuthor);

    cout << "Enter new category (Novels, Physics, Calculus) (leave empty to keep current): ";
    string newCategory;
    getline(cin, newCategory);
    if (!newCategory.empty()) {
        if (newCategory == "Novels" || newCategory == "Physics" || newCategory == "Calculus") {
            book->setCategory(newCategory);
        }
        else {
            cout << "Invalid category. Keeping current category.\n";
        }
    }

    saveBooks(); // Save changes to file
    cout << "Book details updated.\n";
}

void Library::librarianAddBook() {
    clearScreen();
    cout << "=== Add New Book ===\n";
    cout << "Enter category (Novels, Physics, Calculus): ";
    string category;
    getline(cin, category);
    if (category != "Novels" && category != "Physics" && category != "Calculus") {
        cout << "Invalid category.\n";
        return;
    }

    cout << "Enter book name: ";
    string name;
    getline(cin, name);

    cout << "Enter author name: ";
    string author;
    getline(cin, author);

    int newId = generateNextBookId(category);
    addBookDynamic(Book(newId, name, author, category));
    saveBooks();

    cout << "Book added with ID: " << newId << "\n";
}

void Library::librarianDeleteBook() {
    clearScreen();
    cout << "=== Delete Book ===\n";
    cout << "Enter book ID to delete: ";
    int id;
    cin >> id;
    cin.ignore();

    int index = -1;
    for (int i = 0; i < bookCount; ++i) {
        if (books[i].getId() == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Book not found.\n";
        return;
    }

    if (isBookIssued(id)) {
        cout << "Cannot delete book. It is currently issued.\n";
        return;
    }

    // Shift books left
    for (int i = index; i < bookCount - 1; ++i) {
        books[i] = books[i + 1];
    }
    --bookCount;

    saveBooks();

    cout << "Book deleted successfully.\n";
}

void Library::librarianIssueBook() {
    clearScreen();
    cout << "=== Issue Book ===\n";
    cout << "Enter book ID to issue: ";
    int bookId;
    cin >> bookId;
    cin.ignore();

    Book* book = findBookById(bookId);
    if (!book) {
        cout << "Book not found.\n";
        return;
    }

    if (isBookIssued(bookId)) {
        cout << "Book is already issued.\n";
        return;
    }

    cout << "Enter student name: ";
    string studentName;
    getline(cin, studentName);

    cout << "Enter student ID: ";
    int studentId;
    cin >> studentId;
    cin.ignore();

    addIssuedBookDynamic(IssuedBook(bookId, book->getName(), studentName, studentId));
    saveIssuedBooks();

    cout << "Book issued successfully.\n";
}

void Library::librarianViewIssuedBooks() {
    clearScreen();
    cout << "=== Issued Books ===\n";
    if (issuedCount == 0) {
        cout << "No books are currently issued.\n";
    }
    else {
        for (int i = 0; i < issuedCount; ++i) {
            issuedBooks[i].display();
        }
    }
}

void Library::librarianReturnBook() {
    clearScreen();
    cout << "=== Return Book ===\n";
    cout << "Enter book ID to return: ";
    int bookId;
    cin >> bookId;
    cin.ignore();

    int index = -1;
    for (int i = 0; i < issuedCount; ++i) {
        if (issuedBooks[i].getBookId() == bookId) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "No record of this book being issued.\n";
        return;
    }

    removeIssuedBookAt(index);
    saveIssuedBooks();

    cout << "Book returned successfully.\n";
}

// Implementation of Student methods
void Student::menu() {
    while (true) {
        clearScreen();
        cout << "=== Student Menu ===\n";
        cout << "1. View all books\n";
        cout << "2. Search a book\n";
        cout << "3. Return to main menu\n";
        cout << "Enter choice: ";
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            library->studentViewBooks();
            cout << "\nPress Enter to continue...";
            cin.get();
        }
        else if (choice == 2) {
            library->studentSearchBook();
            cout << "\nPress Enter to continue...";
            cin.get();
        }
        else if (choice == 3) {
            break;
        }
        else {
            cout << "Invalid choice. Press Enter to try again...";
            cin.get();
        }
    }
}

// Implementation of Librarian methods

void Librarian::loadPassword() {
    ifstream fin(passwordFile.c_str());
    if (!fin) {
        // Create default password file
        ofstream fout(passwordFile.c_str());
        librarianPassword = "ali";
        fout << librarianPassword;
        fout.close();
    }
    else {
        getline(fin, librarianPassword);
        fin.close();
    }
}

bool Librarian::login() {
    clearScreen();
    cout << "Enter librarian password: ";
    string inputPass;
    getline(cin, inputPass);

    if (inputPass == librarianPassword) {
        cout << "Login successful!\n";
        cout << "Press Enter to continue...";
        cin.get();
        return true;
    }
    else {
        cout << "Incorrect password.\n";
        cout << "Press Enter to continue...";
        cin.get();
        return false;
    }
}

void Librarian::menu() {
    if (!login()) return;

    while (true) {
        clearScreen();
        cout << "=== Librarian Menu ===\n";
        cout << "1. View all books\n";
        cout << "2. Search a book\n";
        cout << "3. Modify a book\n";
        cout << "4. Add a new book\n";
        cout << "5. Delete a book\n";
        cout << "6. Issue a book\n";
        cout << "7. View issued books\n";
        cout << "8. Return a book\n";
        cout << "9. Return to main menu\n";
        cout << "0. Exit program\n";
        cout << "Enter choice: ";
        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            library->librarianViewBooks();
            cout << "\nPress Enter to continue...";
            cin.get();
            break;
        case 2:
            library->librarianSearchBook();
            cout << "\nPress Enter to continue...";
            cin.get();
            break;
        case 3:
            library->librarianModifyBook();
            cout << "\nPress Enter to continue...";
            cin.get();
            break;
        case 4:
            library->librarianAddBook();
            cout << "\nPress Enter to continue...";
            cin.get();
            break;
        case 5:
            library->librarianDeleteBook();
            cout << "\nPress Enter to continue...";
            cin.get();
            break;
        case 6:
            library->librarianIssueBook();
            cout << "\nPress Enter to continue...";
            cin.get();
            break;
        case 7:
            library->librarianViewIssuedBooks();
            cout << "\nPress Enter to continue...";
            cin.get();
            break;
        case 8:
            library->librarianReturnBook();
            cout << "\nPress Enter to continue...";
            cin.get();
            break;
        case 9:
            return;
        case 0:
            cout << "Exiting program...\n";
            exit(0);
        default:
            cout << "Invalid choice. Press Enter to try again...";
            cin.get();
        }
    }
}

// Main function
int main() {
    Library library;

    while (true) {
        clearScreen();
        cout << "=== Library Management System ===\n";
        cout << "1. Student\n";
        cout << "2. Librarian\n";
        cout << "3. Exit program\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            Student student(&library);
            student.menu();
        }
        else if (choice == 2) {
            Librarian librarian(&library);
            librarian.menu();
        }
        else if (choice == 3) {
            cout << "Thank you for using the Library Management System. \n Made by: AbdurRahman\n";
            break;
        }
        else {
            cout << "Invalid choice. Press Enter to try again...";
            cin.get();
        }
    }

    return 0;
}
