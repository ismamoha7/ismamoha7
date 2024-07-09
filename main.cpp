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

