#include <iostream>
#include <fstream> 
using namespace std;
class Student;
class Reservation;

class Food {
public:
    int foodId;
    string day;
    string date;
    string mealType;
    string foodName;
    int capacity;
    int price;
    Food* next;

    static Food* foodHead;

    static void funcWaitlist(int foodId, int newCapacity);

    static void addFood(int foodId, string day, string date, string mealType, string foodName, int capacity, int price) {
        Food* temp = foodHead;
        while(temp != NULL) {
            if(temp->foodId == foodId) {
                cout << "Food ID already exists!" << endl;
                return;
            }
            temp = temp->next;
        }

        Food* newFood = new Food;
        newFood->foodId = foodId;
        newFood->day = day;
        newFood->date = date;
        newFood->mealType = mealType;
        newFood->foodName = foodName;
        newFood->capacity = capacity;
        newFood->price = price;
        newFood->next = NULL;
        
        if(foodHead == NULL) {
            foodHead = newFood;
        }
        else {
            temp = foodHead;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newFood;
        }
        cout << "Food added successfully" << endl;
    }

    static void editFood(int foodId) {
        Food* temp = foodHead;
        while(temp != NULL && temp->foodId != foodId) {
            temp = temp->next;
        }
        
        if(temp == NULL) {
            cout << "Food not found!" << endl;
            return;
        }

        int oldCapacity = temp->capacity;
        cout << "Which parameter do you want to edit?" << endl;
        cout << "1. Capacity" << endl;
        cout << "2. Price" << endl;
        cout << "3. Both" << endl;
        int choice;
        cin >> choice;
        
        if(choice == 1) {
            cout << "Enter the new capacity: ";
            int capacity;
            cin >> capacity;
            temp->capacity = capacity;
            cout << "Capacity updated successfully :)" << endl;

            if(capacity > oldCapacity) {
                funcWaitlist(foodId, capacity - oldCapacity);
            }
        }
        else if(choice == 2) {
            cout << "Enter the new price: ";
            int price;
            cin >> price;
            temp->price = price;
            cout << "Price updated successfully :)" << endl;
        }
        else if(choice == 3) {
            cout << "Enter the new capacity: ";
            int capacity;
            cin >> capacity;
            cout << "Enter the new price: ";
            int price;
            cin >> price;
            temp->capacity = capacity;
            temp->price = price;
            cout << "Capacity and price updated successfully :)" << endl;

            if(capacity > oldCapacity) {
                funcWaitlist(foodId, capacity - oldCapacity);
            }
        }
        else {
            cout << "Invalid choice!" << endl;
        }
    }

    static void saveFoods() {
        ofstream file("foods.txt");
        Food* temp = foodHead;
        while(temp != NULL) {
            file << temp->foodId << " " << temp->day << " " << temp->date << " " 
                 << temp->mealType << " " << temp->foodName << " " 
                 << temp->capacity << " " << temp->price << endl;
            temp = temp->next;
        }
        file.close();
    }

    static void loadFoods() {
        ifstream file("foods.txt");
        if(!file.is_open()) return;

        string day, date, mealType, foodName;
        int foodId, capacity, price;
        while(file >> foodId >> day >> date >> mealType >> foodName >> capacity >> price) {
            addFood(foodId, day, date, mealType, foodName, capacity, price);
        }
        file.close();
    }

    static void deleteFoods() {
        Food* current = foodHead;
        while(current != NULL) {
            Food* next = current->next;
            delete current;
            current = next;
        }
        foodHead = NULL;
    }
};

class Student {
public:
    string studentId;
    string studentName;
    int charge;
    Student* next;

    static Student* studentHead;

    static void addStudent(string studentId, string studentName, int charge) {
        Student* temp = studentHead;
        while(temp != NULL) {
            if(temp->studentId == studentId) {
                cout << "Student ID already exists!" << endl;
                return;
            }
            temp = temp->next;
        }

        Student* newStudent = new Student;
        newStudent->studentId = studentId;
        newStudent->studentName = studentName;
        newStudent->charge = charge;
        newStudent->next = NULL;

        if(studentHead == NULL) {
            studentHead = newStudent;
        }
        else {
            temp = studentHead;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newStudent;
        }
        cout << "Student added successfully" << endl;
    }

    static void addCharge(string studentId, int charge) {
        Student* temp = studentHead;
        while(temp != NULL && temp->studentId != studentId) {
            temp = temp->next;
        }
        
        if(temp == NULL) {
            cout << "Student not found!" << endl;
            return;
        }
        
        temp->charge += charge;
        cout << "Charge added successfully" << endl;
        cout << "New charge: " << temp->charge << endl;
    }

    static void saveStudents() {
        ofstream file("students.txt");
        Student* temp = studentHead;
        while(temp != NULL) {
            file << temp->studentId << " " << temp->studentName << " " 
                 << temp->charge << endl;
            temp = temp->next;
        }
        file.close();
    }

    static void loadStudents() {
        ifstream file("students.txt");
        if (!file.is_open()) return;

        string studentId, studentName;
        int charge;
        while(file >> studentId >> studentName >> charge) {
            addStudent(studentId, studentName, charge);
        }
        file.close();
    }

    static void deleteStudents() {
        Student* current = studentHead;
        while(current != NULL) {
            Student* next = current->next;
            delete current;
            current = next;
        }
        studentHead = NULL;
    }
};

class Reservation {
public:
    string studentId;
    int foodId;
    string day;
    string date;
    string mealType;
    Reservation* next;

    static Reservation* reservationHead;

    static void addToWaitlist(string studentId, int foodId) {
        ofstream file("waitlist.txt", ios::app);
        if(file.is_open()) {
            file << studentId << " " << foodId << endl;
            file.close();
            cout << "Added to waitlist. Will be reserved when capacity increases." << endl;
        }
    }

    static void reserveFood(string studentId, int foodId) {
        if(Food::foodHead == NULL) {
            cout << "No meals available" << endl;
            return;
        }

        Reservation* temp = reservationHead;
        while(temp != NULL) {
            if(temp->studentId == studentId && temp->foodId == foodId) {
                cout << "Reservation already exists :)" << endl;
                return;
            }
            temp = temp->next;
        }

        Student* student = Student::studentHead;
        while(student != NULL && student->studentId != studentId) {
            student = student->next;
            if(student == NULL) {
                cout << "Student not found" << endl;
                cout << "Do you want to add a new student? (y/n)" << endl;
                char choice;
                cin >> choice;
                if(choice == 'y') {
                    cout << "Enter the student name: ";
                    string studentName;
                    cin >> studentName;
                    Student::addStudent(studentId, studentName, 0);
                }
                return;
            }
        }

        Food* food = Food::foodHead;
        while(food != NULL && food->foodId != foodId) {
            food = food->next;
            if(food == NULL) {
                cout << "Food not found" << endl;
                return;
            }
        }

        if(food->capacity == 0) {
            addToWaitlist(studentId, foodId);
        }
        else {
            if(student->charge < food->price) {
                cout << "You do not have enough money to reserve food" << endl;
                r:
                cout << "Do you want to charge your account? (y/n)" << endl;
                char choice;
                cin >> choice;
                if(choice == 'y') {
                    Student::addCharge(studentId, food->price);
                }
                else if(choice == 'n'){
                    return;
                }
                else{
                    cout << "Invalid choice" << endl;
                    goto r;
                }
            }

            Reservation* newReservation = new Reservation;
            newReservation->studentId = studentId;
            newReservation->foodId = foodId;
            newReservation->day = food->day;
            newReservation->date = food->date;
            newReservation->mealType = food->mealType;
            newReservation->next = NULL;

            if(reservationHead == NULL) {
                reservationHead = newReservation;
            }
            else {
                temp = reservationHead;
                while(temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = newReservation;
            }
            food->capacity--;
            student->charge -= food->price;
            cout << "Reservation successful" << endl;
        }
    }

    static void cancelReservation(string studentId, int foodId) {
        if(reservationHead == NULL) {
            cout << "No reservations exist" << endl;
            return;
        }
        
        Reservation* current = reservationHead;
        while(current != NULL && (current->studentId != studentId || current->foodId != foodId)) {
            current = current->next;
        }

        if(current == NULL) {
            cout << "Reservation not found!" << endl;
            return;
        }

        Student* student = Student::studentHead;
        while(student != NULL && student->studentId != studentId) {
            student = student->next;
        }

        Food* food = Food::foodHead;
        while(food != NULL && food->foodId != foodId) {
            food = food->next;
        }

        if(current == reservationHead) {
            reservationHead = current->next;
        }
        else {
            Reservation* temp = reservationHead;
            while(temp->next != current) {
                temp = temp->next;
            }
            temp->next = current->next;
        }
        delete current;

        if(student != NULL && food != NULL) {
            student->charge += food->price;
            food->capacity++;
            cout << "Reservation cancelled successfully!" << endl;

            string filename = "student " + studentId + " reservations.txt";
            ofstream file(filename);
            Reservation* temp = reservationHead;
            bool found = false;
            
            while(temp != NULL) {
                if(temp->studentId == studentId) {
                    found = true;
                    file << "Food ID: " << temp->foodId << endl;
                    file << "Day: " << temp->day << endl;
                    file << "Date: " << temp->date << endl;
                    file << "Meal Type: " << temp->mealType << endl;
                    file << "--------------------------------" << endl;
                }
                temp = temp->next;
            }

            if(!found) {
                file << "No reservations found :(" << endl;
            }
            file.close();
            cout << "Reservation file updated successfully :)" << endl;
        }
    }

    static void saveReservations() {
        ofstream file("reservations.txt");
        Reservation* temp = reservationHead;
        while (temp != NULL) {
            file << temp->studentId << " " << temp->foodId << " " 
                 << temp->day << " " << temp->date << " " << temp->mealType << endl;
            temp = temp->next;
        }
        file.close();
    }

    static void loadReservations() {
        ifstream file("reservations.txt");
        if(!file.is_open()) return;

        string studentId, day, date, mealType;
        int foodId;
        while(file >> studentId >> foodId >> day >> date >> mealType) {
            Reservation* newReservation = new Reservation;
            newReservation->studentId = studentId;
            newReservation->foodId = foodId;
            newReservation->day = day;
            newReservation->date = date;
            newReservation->mealType = mealType;
            newReservation->next = NULL;

            if(reservationHead == NULL) {
                reservationHead = newReservation;
            }
            else {
                Reservation* temp = reservationHead;
                while(temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = newReservation;
            }
        }
        file.close();
    }

    static void deleteReservations() {
        Reservation* current = reservationHead;
        while(current != NULL) {
            Reservation* next = current->next;
            delete current;
            current = next;
        }
        reservationHead = NULL;
    }
};

void Food::funcWaitlist(int foodId, int newCapacity) {
    ifstream inFile("waitlist.txt");
    ofstream outFile("temp_waitlist.txt");
    int count = 0;
    string studentId;
    int waitFoodId;
    
    while(inFile >> studentId >> waitFoodId && count < newCapacity) {
        if(waitFoodId == foodId) {
            Student* student = Student::studentHead;
            while(student != NULL && student->studentId != studentId) {
                student = student->next;
            }
            
            Food* food = Food::foodHead;
            while(food != NULL && food->foodId != foodId) {
                food = food->next;
            }
            
            if(student != NULL && food != NULL && student->charge >= food->price) {
                Reservation::reserveFood(studentId, foodId);
                count++;
            }
            else {
                outFile << studentId << " " << waitFoodId << endl;
            }
        }
        else {
            outFile << studentId << " " << waitFoodId << endl;
        }
    }

    while(inFile >> studentId >> waitFoodId) {
        outFile << studentId << " " << waitFoodId << endl;
    }
    
    inFile.close();
    outFile.close();
    remove("waitlist.txt");
    rename("temp_waitlist.txt", "waitlist.txt");
}

Food* Food::foodHead = NULL;
Student* Student::studentHead = NULL;
Reservation* Reservation::reservationHead = NULL;

void foodMenu() {
    cout << "Food Menu: " << endl;
    cout << "1. Lunch" << endl;
    cout << "2. Dinner" << endl;
    cout << "3. All" << endl;
    int choice;
    cin >> choice;
    Food* temp = Food::foodHead;
    while(temp != NULL) {
        if((choice == 1 && temp->mealType == "Lunch") || 
           (choice == 2 && temp->mealType == "Dinner") || 
           (choice == 3)) {
            cout << "Food ID: " << temp->foodId << endl;
            cout << "Day: " << temp->day << endl;
            cout << "Date: " << temp->date << endl;
            if(choice == 3) cout << "Meal Type: " << temp->mealType << endl;
            cout << "Food Name: " << temp->foodName << endl;
            cout << "Capacity: " << temp->capacity << endl;
            cout << "Price: " << temp->price << endl;
            cout << "--------------------------------" << endl;
        }
        temp = temp->next;
    }
}

void studentInfo(string studentId) {
    Student* temp = Student::studentHead;
    while(temp != NULL && temp->studentId != studentId) {
        temp = temp->next;
    } 
    if(temp == NULL) {
        cout << "Student not found" << endl;
        return;
    }
    cout << "Student ID: " << temp->studentId << endl;
    cout << "Student Name: " << temp->studentName << endl;
    cout << "Charge: " << temp->charge << endl;
}

void studentReservations(string studentId) {
    string filename = "student " + studentId + " reservations.txt";
    ofstream file(filename);
    bool found = false;
    Reservation* temp = Reservation::reservationHead;
    
    while(temp != NULL) {
        if(temp->studentId == studentId) {
            found = true;
            file << "Food ID: " << temp->foodId << endl;
            file << "Day: " << temp->day << endl;
            file << "Date: " << temp->date << endl;
            file << "Meal Type: " << temp->mealType << endl;
            file << "--------------------------------" << endl;
        }
        temp = temp->next;
    }

    if(!found) {
        file << "No reservations found :(" << endl;
    }
    file.close();
    cout << "Reservations saved to " << filename << endl;
}

int main() {
    Student::loadStudents();
    Food::loadFoods();
    Reservation::loadReservations();

    int choice;
    string studentId, studentName, day, date, mealType, foodName;
    int foodId, capacity, price, charge;

    do {
        cout << "Welcome to the food reservation system" << endl;
        cout << "1. Add food" << endl;
        cout << "2. Edit food" << endl;
        cout << "3. Add student" << endl;
        cout << "4. Charge student" << endl;
        cout << "5. Reserve food" << endl;
        cout << "6. Cancel reservation" << endl;
        cout << "7. Show food menu" << endl;
        cout << "8. Show student info" << endl;
        cout << "9. Show student reservations" << endl;
        cout << "10. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: {
                cout << "Enter food ID: ";
                cin >> foodId;
                cout << "Enter day: ";
                cin >> day;
                cout << "Enter date: ";
                cin >> date;
                w:
                cout << "Enter meal type (Lunch/Dinner): ";
                cin >> mealType;
                if(mealType != "Lunch" && mealType != "Dinner") {
                    cout << "Invalid meal type. Please enter either Lunch or Dinner" << endl;
                    goto w;
                }
                cout << "Enter food name: ";
                cin >> foodName;
                cout << "Enter capacity: ";
                cin >> capacity;
                cout << "Enter price: ";
                cin >> price;
                Food::addFood(foodId, day, date, mealType, foodName, capacity, price);
                break;
            }

            case 2: {
                cout << "Enter food ID to edit: ";
                cin >> foodId;
                Food::editFood(foodId);
                break;
            }

            case 3: {
                cout << "Enter student ID: ";
                cin >> studentId;
                cout << "Enter student name: ";
                cin >> studentName;
                cout << "Enter charge: ";
                cin >> charge;
                Student::addStudent(studentId, studentName, charge);
                break;
            }

            case 4: {
                cout << "Enter student ID: ";
                cin >> studentId;
                cout << "Enter amount to charge: ";
                cin >> charge;
                Student::addCharge(studentId, charge);
                break;
            }

            case 5: {
                cout << "Enter student ID: ";
                cin >> studentId;
                cout << "Enter food ID: ";
                cin >> foodId;
                Reservation::reserveFood(studentId, foodId);
                break;
            }

            case 6: {
                cout << "Enter student ID: ";
                cin >> studentId;
                cout << "Enter food ID: ";
                cin >> foodId;
                Reservation::cancelReservation(studentId, foodId);
                break;
            }

            case 7: {
                foodMenu();
                break;
            }

            case 8: {
                cout << "Enter student ID: ";
                cin >> studentId;
                studentInfo(studentId);
                break;
            }

            case 9: {
                cout << "Enter student ID: ";
                cin >> studentId;
                studentReservations(studentId);
                break;
            }

            case 10: {
                Student::saveStudents();
                Food::saveFoods();
                Reservation::saveReservations();
                Student::deleteStudents();
                Food::deleteFoods();
                Reservation::deleteReservations();
                cout << "Data saved successfully" << endl;
                break;
            }

            default:
                cout << "Invalid choice. Please choose a number between 1-10" << endl;
        }
    } while(choice != 10);
}