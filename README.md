# Console-Based Bank Management System

## About The Project
This is a fully functional console-based Bank Management System built with **C++**. It was developed as a practical application for **Course 7: Problem Solving Level 3**. The project demonstrates a solid understanding of fundamental programming concepts, data manipulation, file handling, and structured architecture in C++.

**Recent Major Update:** The system now features an Integrated Security System, User Management, and a fully simulated ATM interface!

## Features
The system provides a comprehensive set of banking operations, categorized into three main modules:

### 1. Security & User Management (New)
* **Secure Login System:** Restricts system access based on user credentials to ensure data privacy and system integrity.
* **Manage Users:** A comprehensive interface to Add, Update, Delete, and List system users, providing full control over the bank's administrative database.

### 2. ATM Simulation (New)
A dedicated, fast-processing ATM module handling daily transactions:
* **Cash Withdrawal**
* **Cash Deposit**
* **Balance Inquiry**

### 3. Core Client Management
* **Show Client List:** Display all clients and their account details.
* **Add New Client:** Register a new user with a unique account number, PIN, name, phone, and initial balance.
* **Delete Client:** Securely remove a client's record from the system.
* **Update Client Info:** Modify existing client details.
* **Find Client:** Search for a specific client using their Account Number.
* **Transactions System:** Includes broader functionalities for operations and checking total bank balances.

## Technologies & Concepts Applied
* **Language:** C++
* **File Handling:** Advanced reading from and writing to text files (`clients.txt` and `users.txt`) to ensure robust data persistence across sessions.
* **Modular Programming:** The code is cleanly structured into multiple header files (e.g., `Client process.h`, `User process.h`, `File process.h`, `String funcs.h`) for better readability, maintainability, and future scalability.
* **String Manipulation:** Processing and formatting user input efficiently.
* **Data Structures:** Utilizing C++ Vectors for dynamic data storage and manipulation in memory.

## How to Run
1. Clone the repository to your local machine:
   `git clone https://github.com/MoSamir59-coder/Bank-Project.git`
2. Open the solution file (`Bank Project.sln`) in **Visual Studio**.
3. Build and run the project (`Ctrl + F5`).
3. Build and run the project using the Local Windows Debugger.

---
*Developed with focus on clean code and robust problem-solving logic.*
