---
# Library Management System

This is a simple command-line Library Management System built in C++. It allows users to interact with the system as either a **Student** or a **Librarian**, providing different functionalities for each role. The system manages books and their issuance, with data persisted to text files.

## Features

### For Students
* **View all books**: Browse a categorized list of all available books in the library.
* **Search for a book**: Find a specific book by its name or ID.

### For Librarians
* **Secure Login**: Access the librarian functionalities via a password-protected login.
* **View all books**: See a comprehensive list of all books, categorized for easy viewing.
* **Search for a book**: Quickly locate books by name or ID.
* **Modify book details**: Update the name, author, or category of existing books.
* **Add new books**: Introduce new books to the library's collection, with automatic ID generation based on category.
* **Delete books**: Remove books from the library (only if they are not currently issued).
* **Issue books**: Record the issuance of a book to a student.
* **View issued books**: See a list of all currently issued books, including student details.
* **Return books**: Mark a book as returned, making it available again.

## Data Persistence
The system uses plain text files to store data, ensuring that information is saved between sessions:
* `books.txt`: Stores details of all books in the library.
* `issue.txt`: Records information about issued books.
* `password.txt`: Contains the librarian's password (default: `ali`).

## How to Compile and Run

### Prerequisites
* A C++ compiler (e.g., g++).

### Compilation
Navigate to the directory containing the source code (`.cpp` file) and compile using your C++ compiler:

```bash
g++ main.cpp -o library_system
```

### Running the Application
After successful compilation, run the executable:

```bash
./library_system
```

On Windows, you might run it like this:

```bash
.\library_system.exe
```

## System Requirements
The `clearScreen()` utility function uses `system("cls")` for Windows and `system("clear")` for Unix-like systems (Linux/macOS) to clear the console. This means the program is compatible with both environments.

## Project Structure
* **`main.cpp`**: Contains the complete source code for the Library Management System.
* `Book` class: Represents a book with `id`, `name`, `author`, and `category`. Includes serialization/deserialization methods for file I/O.
* `IssuedBook` class: Stores information about an issued book, linking it to a student.
* `User` abstract class: Defines the interface for different user types (`menu()` virtual function).
* `Student` class: Inherits from `User` and provides student-specific functionalities.
* `Librarian` class: Inherits from `User` and handles librarian-specific operations, including login.
* `Library` class: Manages the collection of `Book` and `IssuedBook` objects, handling file loading, saving, and all core library logic.
* **Utility Functions**: `clearScreen()` and `toLower()` for enhancing user experience and data handling.

## Usage
Upon launching, the system presents a main menu where you can choose to enter as a Student or a Librarian, or exit the program. Follow the on-screen prompts to navigate through the menus and perform desired actions.

## Developer
* Mian AbdurRahman Qayyum
