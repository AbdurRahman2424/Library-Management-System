# 📚 C++ Library Management System

A simple **command-line Library Management System** built in **C++**, offering distinct functionalities for **students** and **librarians**. It uses **object-oriented programming** and **text file storage** for persistent data management.

---

## ✨ Features

### 👨‍🎓 For Students

* **View All Books**
  Browse the full library collection, categorized for easy viewing.
* **Search for a Book**
  Search by book name or ID.

### 🧑‍🏫 For Librarians

* **🔐 Secure Login**
  Password-protected access to librarian functionalities.

  > Default Password: `ali`
* **📚 Manage Books**

  * View all books
  * Search for a book by name or ID
  * Modify book details (name, author, category)
  * Add new books with automatic ID generation
  * Delete books (only if not issued)
* **📖 Issue Management**

  * Issue books to students
  * View currently issued books with student details
  * Return books to mark them available again

---

## 💾 Data Persistence

All data is stored in plain text files for durability between sessions:

| File Name      | Purpose                                  |
| -------------- | ---------------------------------------- |
| `books.txt`    | Stores all books in the library          |
| `issue.txt`    | Tracks which books are issued            |
| `password.txt` | Stores librarian password (default: ali) |

---

## 🛠️ How to Compile & Run

### ✅ Prerequisites

* A working **C++ compiler** (e.g., `g++`)

### 🔧 Compile

Open your terminal, navigate to the source directory, and compile:

```bash
g++ main.cpp -o library_system
```

### ▶️ Run

On **Linux/macOS**:

```bash
./library_system
```

On **Windows**:

```cmd
.\library_system.exe
```

---

## 📂 Project Structure

```bash
project/
└── main.cpp          # Complete source code
```

### 💡 Classes and Components

| Class / Component | Description                                                                                  |
| ----------------- | -------------------------------------------------------------------------------------------- |
| `Book`            | Represents a book (id, name, author, category) with file I/O methods                         |
| `IssuedBook`      | Represents an issued book linked to a student                                                |
| `User` (abstract) | Base class with `menu()` as a virtual function                                               |
| `Student`         | Inherits from `User`; provides student functionalities                                       |
| `Librarian`       | Inherits from `User`; handles librarian features and login                                   |
| `Library`         | Manages books and issued books, handles file operations                                      |
| Utility Functions | `clearScreen()` for cross-platform console clearing, `toLower()` for case-insensitive search |

---

## 🧑‍💻 Usage

When you launch the program, you'll see the **Main Menu**:

```text
Library Management System

1. Enter as Student
2. Enter as Librarian
3. Exit
```

* **Students** can browse and search books.
* **Librarians** must log in to access full book and issue management features.
* Simply follow on-screen prompts to navigate and perform actions.

---

## 🖥️ System Compatibility

* Uses `system("cls")` for **Windows**
* Uses `system("clear")` for **Linux/macOS**
* Compatible across platforms with minimal changes

---

## 👨‍💻 Developer

**Mian AbdurRahman Qayyum**

> This project is built for learning and demonstration purposes.
> Not intended for production or commercial use.

---
