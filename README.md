👋 **A Quick Note:** This is one of my very first projects in C++, and I've put a lot of effort into making both the project and this detailed README as complete as possible as part of my learning journey! It was a practice for learning C++ and git & github together :)##


![C++](https://img.shields.io/badge/C++-17-blue.svg) 
![License](https://img.shields.io/badge/License-MIT-green.svg)  
*A console-based food reservation system for university dining halls, built with C++.*

## 📖 Table of Contents
1.  [📝 Project Description](#-project-description)
2.  [✨ Features](#-features)
3.  [🛠️ Prerequisites](#️-prerequisites)
4.  [⚙️ How to Compile and Run](#️-how-to-compile-and-run)
5.  [📁 File Structure](#-file-structure)
6.  [🧩 Core Classes and Functionalities](#-core-classes-and-functionalities)
    * [🍔 Food Class](#-food-class)
    * [🧑‍🎓 Student Class](#-student-class)
    * [📅 Reservation Class](#-reservation-class)
7.  [🚀 Usage Guide](#-usage-guide)
    * [Main Menu Options](#main-menu-options)
8.  [⏳ Waitlist Functionality](#-waitlist-functionality)
9.  [💾 Data Persistence](#-data-persistence)
10. [💡 Potential Future Improvements](#-potential-future-improvements)
11. [🤝 Contributing](#-contributing)
12. [📜 License](#-license)
13. [📬 Contact](#-contact)

---

## 📝 Project Description

The **Food Reservation System** is a command-line application written in C++ that allows users (presumably administrators and students) to manage a canteen or cafeteria system. It supports operations such as adding and managing food items, registering students, managing student account charges, making and canceling food reservations, and viewing various reports. The system uses text files for data persistence, loading data at startup and saving it on exit.

---

## ✨ Features

* **Food Management**:
    * Add new food items with details: ID, day, date, meal type (Lunch/Dinner), name, capacity, and price.
    * Edit existing food items: Update capacity and/or price.
    * View food menu: Filter by Lunch, Dinner, or see all available items.
* **Student Management**:
    * Add new students: Record student ID, name, and initial account charge.
    * Add charge to student accounts.
    * View student information: Display student ID, name, and current charge.
* **Reservation Management**:
    * Reserve food: Students can reserve available food items.
    * Automatic Waitlisting: If a food item is out of stock, students are added to a waitlist.
    * Process Waitlist: When food capacity increases, waitlisted students are automatically reserved if they have sufficient funds.
    * Cancel reservations: Students can cancel their existing reservations, and funds are refunded.
    * View student reservations: Display all reservations for a specific student and save them to a dedicated file.
* **Data Persistence**:
    * Loads data from `foods.txt`, `students.txt`, and `reservations.txt` on startup.
    * Saves all data back to these files upon exiting the application.
    * Manages a `waitlist.txt` for pending reservations.
    * Generates individual `student [studentId] reservations.txt` files.

---

## 🛠️ Prerequisites

* A C++ compiler that supports C++11 or later (e.g., GCC/g++, Clang, MSVC).
* Basic understanding of command-line interface usage.

---

## ⚙️ How to Compile and Run

1.  **Save the Code**: Ensure all the provided C++ code is saved in a single file named `main.cpp` (or your preferred name).
2.  **Open a Terminal or Command Prompt**: Navigate to the directory where you saved the file.
3.  **Compile the Code**:
    * Using g++ (common on Linux/macOS):
        ```bash
        g++ main.cpp -o food_reservation_system
        ```
    * Using Clang:
        ```bash
        clang++ main.cpp -o food_reservation_system
        ```
    * Using MSVC (Visual Studio Developer Command Prompt):
        ```bash
        cl main.cpp /EHsc /Fe:food_reservation_system.exe
        ```
    (If you use a different filename than `main.cpp`, replace it in the command above.)

4.  **Run the Executable**:
    * On Linux/macOS:
        ```bash
        ./food_reservation_system
        ```
    * On Windows:
        ```bash
        food_reservation_system.exe
        ```

Upon running, the application will attempt to load data from `foods.txt`, `students.txt`, and `reservations.txt`. If these files don't exist, it will start with empty data.

---

## 📁 File Structure

The application uses several text files to store and manage data:

* `main.cpp`: (Or your chosen filename) Contains the C++ source code for the project.
* `foods.txt`: Stores data for all available food items. Each line represents a food item:
    `foodId day date mealType foodName capacity price`
* `students.txt`: Stores data for all registered students. Each line represents a student:
    `studentId studentName charge`
* `reservations.txt`: Stores data for all active reservations. Each line represents a reservation:
    `studentId foodId day date mealType`
* `waitlist.txt`: Stores pending reservation requests for food items that are currently out of capacity. Each line represents a waitlist entry:
    `studentId foodId`
* `student [studentId] reservations.txt`: Dynamically created/updated file that lists all reservations for a specific student. This file is generated or updated when a student's reservations are viewed (Option 9) or when a reservation is canceled. For example, `student 123 reservations.txt`.

---

## 🧩 Core Classes and Functionalities

The system is built around three main classes that manage data using linked lists:

### 🍔 Food Class

Manages all aspects related to food items.

* **Attributes**:
    * `foodId` (int): Unique identifier for the food.
    * `day` (string): Day of the week the food is available.
    * `date` (string): Date the food is available.
    * `mealType` (string): "Lunch" or "Dinner".
    * `foodName` (string): Name of the food.
    * `capacity` (int): Number of available servings.
    * `price` (int): Cost of the food item.
    * `next` (Food\*): Pointer to the next food item in the linked list.
* **Static Members**:
    * `foodHead` (Food\*): Head of the linked list of food items.
* **Key Static Methods**:
    * `addFood(...)`: Adds a new food item if the `foodId` doesn't already exist.
    * `editFood(int foodId)`: Allows editing the `capacity` and/or `price` of an existing food item. If capacity is increased, it triggers `funcWaitlist`.
    * `saveFoods()`: Saves all food items to `foods.txt`.
    * `loadFoods()`: Loads food items from `foods.txt` at startup.
    * `deleteFoods()`: Deallocates memory used by the food linked list.
    * `funcWaitlist(int foodId, int newCapacity)`: Processes students from `waitlist.txt` for a given `foodId` if its capacity increases.

### 🧑‍🎓 Student Class

Manages student information and account balances.

* **Attributes**:
    * `studentId` (string): Unique identifier for the student.
    * `studentName` (string): Name of the student.
    * `charge` (int): Current account balance of the student.
    * `next` (Student\*): Pointer to the next student in the linked list.
* **Static Members**:
    * `studentHead` (Student\*): Head of the linked list of students.
* **Key Static Methods**:
    * `addStudent(...)`: Adds a new student if the `studentId` doesn't already exist.
    * `addCharge(string studentId, int charge)`: Adds a specified amount to a student's account balance.
    * `saveStudents()`: Saves all student data to `students.txt`.
    * `loadStudents()`: Loads student data from `students.txt` at startup.
    * `deleteStudents()`: Deallocates memory used by the student linked list.

### 📅 Reservation Class

Manages food reservations made by students.

* **Attributes**:
    * `studentId` (string): ID of the student making the reservation.
    * `foodId` (int): ID of the food item being reserved.
    * `day` (string): Day of the reservation (copied from Food).
    * `date` (string): Date of the reservation (copied from Food).
    * `mealType` (string): Meal type of the reservation (copied from Food).
    * `next` (Reservation\*): Pointer to the next reservation in the linked list.
* **Static Members**:
    * `reservationHead` (Reservation\*): Head of the linked list of reservations.
* **Key Static Methods**:
    * `reserveFood(string studentId, int foodId)`: Allows a student to reserve a food item.
        * Checks if the student and food exist.
        * Checks if the student has enough charge.
        * If food capacity is zero, adds the student to the waitlist using `addToWaitlist`.
        * Decreases food capacity and student charge upon successful reservation.
    * `cancelReservation(string studentId, int foodId)`: Cancels an existing reservation.
        * Increases food capacity and refunds the student's charge.
        * Updates the student-specific reservation file.
    * `addToWaitlist(string studentId, int foodId)`: Adds a student's request to `waitlist.txt`.
    * `saveReservations()`: Saves all active reservations to `reservations.txt`.
    * `loadReservations()`: Loads reservation data from `reservations.txt` at startup.
    * `deleteReservations()`: Deallocates memory used by the reservation linked list.

---

## 🚀 Usage Guide

Upon running the application, you will be presented with a main menu. Enter the number corresponding to your desired action.

### Main Menu Options

1.  **Add food**:
    * Prompts for food ID, day, date, meal type ("Lunch" or "Dinner"), food name, capacity, and price.
    * Adds the food to the system if the ID is unique.
2.  **Edit food**:
    * Prompts for the food ID to edit.
    * Allows updating capacity, price, or both.
    * If capacity is increased, it may trigger reservations for waitlisted students.
3.  **Add student**:
    * Prompts for student ID, student name, and initial charge.
    * Adds the student to the system if the ID is unique.
4.  **Charge student**:
    * Prompts for student ID and the amount to add to their charge.
5.  **Reserve food**:
    * Prompts for student ID and food ID.
    * Attempts to reserve the food. If successful, updates student charge and food capacity.
    * If the student doesn't exist, offers to add them.
    * If the student has insufficient funds, offers an option to add charge.
    * If food capacity is zero, adds the student to the waitlist for that food.
6.  **Cancel reservation**:
    * Prompts for student ID and food ID of the reservation to cancel.
    * Refunds the student and increases food capacity.
    * Updates the `student [studentId] reservations.txt` file.
7.  **Show food menu**:
    * Asks whether to display "Lunch", "Dinner", or "All" meals.
    * Lists details of matching food items.
8.  **Show student info**:
    * Prompts for student ID.
    * Displays the student's name and current charge.
9.  **Show student reservations**:
    * Prompts for student ID.
    * Lists all current reservations for that student.
    * Saves/updates this list to `student [studentId] reservations.txt`.
10. **Exit**:
    * Saves all current data (foods, students, reservations) to their respective `.txt` files.
    * Clears all data from memory (deallocates linked lists).
    * Terminates the application.

---

## ⏳ Waitlist Functionality

The system includes a waitlist feature for popular food items:

1.  **Adding to Waitlist**: If a student attempts to reserve a food item (`Reservation::reserveFood`) whose `capacity` is 0, the student's ID and the food ID are appended to `waitlist.txt` via `Reservation::addToWaitlist`.
2.  **Processing Waitlist**: When an administrator edits a food item (`Food::editFood`) and increases its `capacity`, the `Food::funcWaitlist` method is called.
    * This function reads `waitlist.txt`.
    * For each entry matching the `foodId` whose capacity was increased, it attempts to make a reservation (`Reservation::reserveFood`).
    * It processes students from the waitlist up to the number of newly available slots.
    * A reservation is made only if the student exists and has sufficient charge for the food item.
    * Successfully processed students are removed from the waitlist. Unprocessed students (due to insufficient funds or if `newCapacity` slots are filled) remain in the waitlist file for future attempts.
    * The `waitlist.txt` file is updated by writing to a temporary file and then renaming it.

---

## 💾 Data Persistence

* **Loading**: When the application starts, `Student::loadStudents()`, `Food::loadFoods()`, and `Reservation::loadReservations()` are called to populate the in-memory linked lists from `students.txt`, `foods.txt`, and `reservations.txt` respectively.
* **Saving**: When the user chooses option 10 (Exit), `Student::saveStudents()`, `Food::saveFoods()`, and `Reservation::saveReservations()` are called to write the current state of the linked lists back to their respective text files.
* **Dynamic Files**:
    * `waitlist.txt` is read and rewritten by `Food::funcWaitlist`.
    * `student [studentId] reservations.txt` files are created/overwritten by `studentReservations()` (menu option 9) and `Reservation::cancelReservation()`.

---

## 💡 Potential Future Improvements

* **Enhanced Input Validation**: Implement more robust checks for user inputs (e.g., ensuring numeric inputs are indeed numbers, date formats are valid).
* **User Roles**: Differentiate between an "Admin" and "Student" interface with different permissions.
* **Password Protection**: Secure student accounts or admin functionalities.
* **Advanced Search/Filter**: Allow searching for food by name, or students by name, and more complex filtering options for menus.
* **Reporting**: Generate reports like daily/weekly popular food items, total sales, etc.
* **Date and Time Handling**: Use a proper date/time library for managing food availability and reservation dates, potentially automating removal of past food items.
* **Error Handling**: Improve error messages and recovery mechanisms.
* **Refactor `goto` statements**: Replace `goto` statements with structured control flow (loops, conditionals) for better readability and maintainability.
* **User Interface**: Develop a Graphical User Interface (GUI) for a more user-friendly experience.
* **Database Integration**: Replace text files with a relational database (e.g., SQLite, PostgreSQL) for more robust data management, scalability, and querying capabilities.
* **Transaction Management**: For financial operations like charging and reserving, implement more robust transaction logic to ensure data consistency.

---

## 🤝 Contributing

Contributions are what make the open-source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1.  **Fork the Project**
2.  **Create your Feature Branch** (`git checkout -b feature/AmazingFeature`)
3.  **Commit your Changes** (`git commit -m 'Add some AmazingFeature'`)
4.  **Push to the Branch** (`git push origin feature/AmazingFeature`)
5.  **Open a Pull Request**

Please make sure to update tests as appropriate and adhere to the existing coding style.

---

## 📜 License

This project is licensed under the **MIT License**.

MIT License

Copyright (c) [2025] [Mehdi Ahmadiyan]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

---

## 📬 Contact

[Mehdi Ahmadiyan] - [mahdiahmadiyan13@gmail.com]

Project Link: [https://github.com/MehdiAhmadiyan/University-Food-Reservation](https://github.com/MehdiAhmadiyan/University-Food-Reservation)

