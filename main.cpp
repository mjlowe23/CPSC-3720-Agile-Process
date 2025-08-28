#include <iostream>
#include <vector>
#include <string>

using namespace std;

class StudentProfile {
private:
    string studentName;
    vector<string> courses;

public:
    void createProfile() {
        cout << "Enter your name: ";
        getline(cin, studentName);

        cout << "How many courses are you enrolled in? ";
        int courseCount;
        cin >> courseCount;
        cin.ignore(); // to consume newline character after number input

        for (int i = 0; i < courseCount; ++i) {
            cout << "Enter course #" << (i + 1) << ": ";
            string course;
            getline(cin, course);
            courses.push_back(course);
        }
    }

    void displayProfile() {
        cout << "\n--- Student Profile ---\n";
        cout << "Name: " << studentName << "\n";
        cout << "Courses enrolled in:\n";
        for (size_t i = 0; i < courses.size(); ++i) {
            cout << "  " << (i + 1) << ". " << courses[i] << "\n";
        }
    }
};

int main() {
    
 StudentProfile student;

    cout << "Welcome to Study Buddy Profile Setup\n";
    student.createProfile();

    student.displayProfile();

return 0;

}

