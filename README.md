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
  * View all books organized by category (Novels, Physics, Calculus)
  * Search for a book by name or ID
  * Modify book details (name, author, category)
  * Add new books with automatic ID generation
  * Delete books (only if not issued)
* **📖 Issue Management**
  * Issue books to students with student ID tracking
  * View currently issued books with student details
  * Return books to mark them available again

---

## 💾 Data Persistence
All data is stored in plain text files for durability between sessions:

| File Name      | Purpose                                  |
| -------------- | ---------------------------------------- |
| `books.txt`    | Stores all books in the library         |
| `issue.txt`    | Tracks which books are issued            |
| `password.txt` | Stores librarian password (default: ali) |

### 📋 Book Categories & ID System
- **Novels**: IDs start from 1
- **Physics**: IDs start from 101  
- **Calculus**: IDs start from 201
- **Other categories**: IDs start from 301

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
├── main.cpp          # Complete source code
├── books.txt          # Generated: Book database
├── issue.txt          # Generated: Issued books tracking
└── password.txt       # Generated: Librarian password
```

### 💡 Classes and Components

| Class / Component | Description                                                                                  |
| ----------------- | -------------------------------------------------------------------------------------------- |
| `Book`            | Represents a book (id, name, author, category) with serialization methods                   |
| `IssuedBook`      | Represents an issued book linked to a student                                               |
| `User` (abstract) | Base class with `menu()` as a pure virtual function                                         |
| `Student`         | Inherits from `User`; provides student functionalities                                      |
| `Librarian`       | Inherits from `User`; handles librarian features and authentication                         |
| `Library`         | Core class managing books and issued books with dynamic memory allocation                   |
| Utility Functions | `clearScreen()` for cross-platform console clearing, `toLower()` for case-insensitive search |

### 🏗️ Key Technical Features
- **Dynamic Memory Management**: Automatic array resizing for scalability
- **File Serialization**: Custom serialization for data persistence  
- **Friend Classes**: Controlled access between Library and User classes
- **Cross-platform Compatibility**: Works on Windows and Unix-based systems

---

## 🧑‍💻 Usage

When you launch the program, you'll see the **Main Menu**:
```text
=== Library Management System ===
1. Student
2. Librarian  
3. Exit program
```

* **Students** can browse and search books without authentication
* **Librarians** must log in (default password: `ali`) to access full management features
* Simply follow on-screen prompts to navigate and perform actions

### 📖 Sample Workflow
1. **First Run**: System creates default files and password
2. **Add Books**: Use librarian interface to populate the library
3. **Issue Books**: Track which students have borrowed books
4. **Student Access**: Students can view and search available books

---

## 🖥️ System Compatibility
* Uses `system("cls")` for **Windows**
* Uses `system("clear")` for **Linux/macOS**
* Compatible across platforms with minimal changes
* Requires standard C++ libraries only

---

## 🤝 Contributing

Contributions are welcome! Potential enhancements:
- Add more book categories
- Implement due date tracking
- Add fine calculation system
- Create GUI version
- Database integration

---

## 👨‍💻 Authors
**Mian AbdurRahman Qayyum** and **Haider Ali**

> This project is built for learning and demonstration purposes.
> Feel free to use, modify, and distribute for educational use.

---

## 📝 License
This project is open source and available for educational purposes.