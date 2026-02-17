#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <ctime>
#include <limits>

using namespace std;

// ==============================
// 1. STUDENT CLASS
// ==============================
class Student {
private:
    string indexNumber;
    string name;
    
public:
    Student() : indexNumber(""), name("") {}
    
    Student(string idx, string n) : indexNumber(idx), name(n) {}
    
    // Getters
    string getIndex() const { return indexNumber; }
    string getName() const { return name; }
    
    // Setters
    void setIndex(string idx) { indexNumber = idx; }
    void setName(string n) { name = n; }
    
    // Display student info
    void display() const {
        cout << left << setw(15) << indexNumber 
             << setw(25) << name << endl;
    }
    
    // Convert to string for file storage
    string toString() const {
        return indexNumber + "," + name;
    }
    
    // Load from string (for file reading)
    static Student fromString(const string& data) {
        size_t commaPos = data.find(',');
        if (commaPos != string::npos) {
            string idx = data.substr(0, commaPos);
            string name = data.substr(commaPos + 1);
            return Student(idx, name);
        }
        return Student("", "");
    }
};

// ==============================
// 2. ATTENDANCE RECORD CLASS
// ==============================
class AttendanceRecord {
private:
    string studentIndex;
    char status; // 'P' = Present, 'A' = Absent, 'L' = Late
    
public:
    AttendanceRecord() : studentIndex(""), status('A') {}
    
    AttendanceRecord(string idx, char s) : studentIndex(idx), status(s) {}
    
    // Getters
    string getStudentIndex() const { return studentIndex; }
    char getStatus() const { return status; }
    
    // Setters
    void setStatus(char s) { status = s; }
    
    // Display record
    void display(const vector<Student>& students) const {
        // Find student name
        string studentName = "Unknown";
        for (const auto& student : students) {
            if (student.getIndex() == studentIndex) {
                studentName = student.getName();
                break;
            }
        }
        
        string statusText;
        switch (status) {
            case 'P': statusText = "Present"; break;
            case 'A': statusText = "Absent"; break;
            case 'L': statusText = "Late"; break;
            default: statusText = "Unknown";
        }
        
        cout << left << setw(15) << studentIndex 
             << setw(25) << studentName 
             << setw(10) << statusText << endl;
    }
    
    // Convert to string for file storage
    string toString() const {
        return studentIndex + "," + status;
    }
    
    // Load from string
    static AttendanceRecord fromString(const string& data) {
        size_t commaPos = data.find(',');
        if (commaPos != string::npos) {
            string idx = data.substr(0, commaPos);
            char status = data.substr(commaPos + 1)[0];
            return AttendanceRecord(idx, status);
        }
        return AttendanceRecord("", 'A');
    }
};
