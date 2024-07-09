#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>

// Define a struct to represent a student
struct Student {
    std::string firstname;
    std::string surname;
    std::string gender;
    int age;
    int group;
    std::vector<std::string> activities;
};

struct Activity {
    std::string name;
    int maxCapacity;
    int currentCapacity;
    int maxGenderRatio; // Percentage limit for a single gender
    int maleCount;
    int femaleCount;
};

std::vector<Student> students;
std::vector<Activity> sports = {
        {"Rugby", 20, 0, 75, 0, 0},
        {"Athletics", 20, 0, 75, 0, 0},
        {"Swimming", 20, 0, 75, 0, 0},
        {"Soccer", 20, 0, 75, 0, 0}
};
std::vector<Activity> clubs = {
        {"Journalism Club", 60, 0, 50, 0, 0},
        {"Red Cross Society", 60, 0, 50, 0, 0},
        {"AISEC", 60, 0, 50, 0, 0},
        {"Business Club", 60, 0, 50, 0, 0},
        {"Computer Science Club", 60, 0, 50, 0, 0}
};

// Function to add a student
void addStudent() {
    Student student;
    std::cout << "Enter first name: ";
    std::cin >> student.firstname;
    std::cout << "Enter surname: ";
    std::cin >> student.surname;
    std::cout << "Enter gender (Male/Female): ";
    std::cin >> student.gender;
    std::cout << "Enter age: ";
    std::cin >> student.age;
    std::cout << "Enter BBIT group (1-3): ";
    std::cin >> student.group;

    int choice;
    do {
        std::cout << "\nSelect activity type:\n1. Sport\n2. Club/Society\n0. Finish selection\nYour choice: ";
        std::cin >> choice;
        if (choice == 1) {
            std::cout << "Available sports:\n";
            for (size_t i = 0; i < sports.size(); ++i) {
                std::cout << i + 1 << ". " << sports[i].name << " (Available: " << sports[i].maxCapacity - sports[i].currentCapacity << ")\n";
            }
            int sportChoice;
            std::cin >> sportChoice;
            if (sportChoice > 0 && sportChoice <= sports.size() && sports[sportChoice - 1].currentCapacity < sports[sportChoice - 1].maxCapacity) {
                if ((sports[sportChoice - 1].maleCount + sports[sportChoice - 1].femaleCount) < (sports[sportChoice - 1].maxCapacity) &&
                    ((student.gender == "Male" && sports[sportChoice - 1].maleCount < sports[sportChoice - 1].maxCapacity * sports[sportChoice - 1].maxGenderRatio / 100) ||
                     (student.gender == "Female" && sports[sportChoice - 1].femaleCount < sports[sportChoice - 1].maxCapacity * sports[sportChoice - 1].maxGenderRatio / 100))) {
                    student.activities.push_back(sports[sportChoice - 1].name);
                    sports[sportChoice - 1].currentCapacity++;
                    if (student.gender == "Male") sports[sportChoice - 1].maleCount++;
                    else sports[sportChoice - 1].femaleCount++;
                } else {
                    std::cout << "Gender ratio limit reached for this sport.\n";
                }
            } else {
                std::cout << "Invalid choice or sport is full.\n";
            }
        } else if (choice == 2) {
            std::cout << "Available clubs/societies:\n";
            for (size_t i = 0; i < clubs.size(); ++i) {
                std::cout << i + 1 << ". " << clubs[i].name << " (Available: " << clubs[i].maxCapacity - clubs[i].currentCapacity << ")\n";
            }
            int clubChoice;
            std::cin >> clubChoice;
            if (clubChoice > 0 && clubChoice <= clubs.size() && clubs[clubChoice - 1].currentCapacity < clubs[clubChoice - 1].maxCapacity) {
                if ((clubs[clubChoice - 1].maleCount + clubs[clubChoice - 1].femaleCount) < (clubs[clubChoice - 1].maxCapacity) &&
                    ((student.gender == "Male" && clubs[clubChoice - 1].maleCount < clubs[clubChoice - 1].maxCapacity * clubs[clubChoice - 1].maxGenderRatio / 100) ||
                     (student.gender == "Female" && clubs[clubChoice - 1].femaleCount < clubs[clubChoice - 1].maxCapacity * clubs[clubChoice - 1].maxGenderRatio / 100))) {
                    student.activities.push_back(clubs[clubChoice - 1].name);
                    clubs[clubChoice - 1].currentCapacity++;
                    if (student.gender == "Male") clubs[clubChoice - 1].maleCount++;
                    else clubs[clubChoice - 1].femaleCount++;
                } else {
                    std::cout << "Gender ratio limit reached for this club/society.\n";
                }
            } else {
                std::cout << "Invalid choice or club/society is full.\n";
            }
        }
    } while (choice != 0);

    students.push_back(student);
}

void viewStudents() {
    std::cout << "\nView students by:\n1. All\n2. Group\nYour choice: ";
    int choice;
    std::cin >> choice;
    if (choice == 1) {
        for (const auto& student : students) {
            std::cout << student.firstname << " " << student.surname << " (Group " << student.group << "): ";
            for (const auto& activity : student.activities) {
                std::cout << activity << " ";
            }
            std::cout << "\n";
        }
    } else if (choice == 2) {
        std::cout << "Enter group number (1-3): ";
        int group;
        std::cin >> group;
        for (const auto& student : students) {
            if (student.group == group) {
                std::cout << student.firstname << " " << student.surname << " (Group " << student.group << "): ";
                for (const auto& activity : student.activities) {
                    std::cout << activity << " ";
                }
                std::cout << "\n";
            }
        }
    } else {
        std::cout << "Invalid choice.\n";
    }
}

void viewActivities(const std::vector<Activity>& activities) {
    for (const auto& activity : activities) {
        std::cout << activity.name << " (Available: " << activity.maxCapacity - activity.currentCapacity << ", Male: " << activity.maleCount << ", Female: " << activity.femaleCount << ")\n";
    }
}

void saveToFile() {
    std::ofstream outFile("students.csv");
    outFile << "Firstname,Surname,Gender,Age,Group,Activities\n";
    for (const auto& student : students) {
        outFile << student.firstname << "," << student.surname << "," << student.gender << "," << student.age << "," << student.group << ",";
        for (const auto& activity : student.activities) {
            outFile << activity << ";";
        }
        outFile << "\n";
    }
    outFile.close();
    std::cout << "Data saved to students.csv\n";
}

int main() {
    int choice;
    do {
        std::cout << "\nMenu:\n1. Add Student\n2. View Students\n3. View Clubs/Societies\n4. View Sports\n5. View Grouped Students\n6. Save all Files\n7. Exit\nYour choice: ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                viewStudents();
                break;
            case 3:
                viewActivities(clubs);
                break;
            case 4:
                viewActivities(sports);
                break;
            case 5:
                viewStudents();
                break;
            case 6:
                saveToFile();
                break;
            case 7:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 7);
    return 0;
}

