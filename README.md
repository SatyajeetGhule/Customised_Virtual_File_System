# Customised_Virtual_File_System
Developed a Customised Virtual File System using C programming concepts that simulates Unix/Linux file system internals. Implemented inode management, file descriptor handling, and core file operations such as create, read, write, delete, and list files through a custom shell.

---

# 🗂️ Customised Virtual File System (CVFS)

A **Customised Virtual File System** implemented using **C programming concepts**, designed to simulate the internal working of a Unix/Linux-like file system.
This project provides a command-line shell to perform basic file operations and helps in understanding core operating system internals.

---

## 📌 Overview

The Customised Virtual File System (CVFS) is an **in-memory file system simulation**.
It mimics how an operating system manages files internally using data structures such as **Boot Block, Super Block, Inode List (DILB), File Table, and UFDT**.

The project does **not use actual disk storage**. All file data and metadata are managed dynamically in memory, making it ideal for learning and educational purposes.

---

## 🎯 Purpose

This project is designed to:

* Understand the internal working of a Virtual File System
* Learn how Unix/Linux system calls work internally
* Practice low-level system programming using C
* Understand inode-based file management
* Strengthen fundamentals for:

  * Operating Systems
  * System Programming
  * Technical Interviews

---

## ⚙️ Features

* Interactive CVFS command-line shell
* File creation with permissions (Read / Write)
* Read and write operations on files
* File deletion using unlink operation
* List all files with inode information
* Manual pages for supported commands
* Proper error handling using error codes
* Complete in-memory file system (no disk I/O)

---

## 🏗️ Architecture

The internal design closely follows a real Unix/Linux file system:

```
User Commands
     ↓
CVFS Shell
     ↓
UFDT (User File Descriptor Table)
     ↓
File Table
     ↓
Inode (DILB - Linked List)
     ↓
Super Block
     ↓
Boot Block
```

### Core Components

* **Boot Block** – Stores boot-related information
* **Super Block** – Maintains total and free inode count
* **Inode (DILB)** – Stores file metadata and buffer
* **File Table** – Maintains read/write offsets and mode
* **UFDT** – Manages open files for a process

---

## 🛠️ Technologies Used

* **Programming Language:** C (procedural programming)
* **File Extension:** `.cpp`
* **Compiler:** g++
* **Core Concepts:**

  * Structures and Pointers
  * Linked Lists
  * Dynamic Memory Allocation
  * File System Internals
  * System Call Simulation

---

## 📝 Language & File Extension Note

Although this project is written using **C language syntax and concepts**, the source file uses a **`.cpp` file extension**.

This is intentional to:

* Compile the program using a C++ compiler
* Maintain consistency with other system-level projects
* Allow future enhancement using C++ features if required

⚠️ **Note:**
The project does **not** use C++ features such as classes, templates, or STL.
It strictly follows **C-style procedural programming**.

---

## 📡 Supported Commands

| Command                         | Description            |
| ------------------------------- | ---------------------- |
| `creat <filename> <permission>` | Create a new file      |
| `write <fd>`                    | Write data into a file |
| `read <fd> <size>`              | Read data from a file  |
| `ls`                            | List all files         |
| `unlink <filename>`             | Delete a file          |
| `man <command>`                 | Display manual page    |
| `help`                          | Display help menu      |
| `clear`                         | Clear terminal         |
| `exit`                          | Exit CVFS              |

---

## ▶️ How to Run

1. Compile the source file:

```bash
g++ CVFS.cpp -o cvfs
```

2. Run the executable:

```bash
./cvfs
```

3. Start executing CVFS commands from the shell.

---

## 📂 Sample Usage

```
Marvellous CVFS :> creat Demo.txt 3
File gets successfully created with fd 3

Marvellous CVFS :> write 3
Enter the data that you want to write:
Hello CVFS!

Marvellous CVFS :> read 3 10
Data from file is : Hello CVFS
```

---

## 🚫 Limitations

* Fixed maximum file size
* Limited number of inodes
* Single process simulation
* No persistent storage (RAM only)

---

## 📚 Learning Outcomes

* Clear understanding of file system internals
* Practical knowledge of inode-based file management
* Strong grip on OS-level data structures
* Improved confidence for system programming interviews

---

## 👨‍💻 Author

**Satyajeet Manohar Ghule**

**Date:** January 2026

---
