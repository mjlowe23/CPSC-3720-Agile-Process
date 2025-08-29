#include "student_profile.h"

void updateProfile(StudentProfile& student) {
    char choice;
    do {
        cout << "\n--- Updating profile for " << student.getName() << " ---\n";
        cout << "1. Add course\n";
        cout << "2. Remove course\n";
        cout << "3. Clear and add availability\n";
        cout << "4. Display profile\n";
        cout << "5. Return to main menu\n";
        cout << "Select an option: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case '1': {
                cout << "Enter course to add: ";
                string course;
                getline(cin, course);
                student.addCourse(course);
                cout << "Course added.\n";
                break;
            }
            case '2': {
                cout << "Enter course to remove: ";
                string course;
                getline(cin, course);
                if (student.removeCourse(course)) {
                    cout << "Course removed.\n";
                } else {
                    cout << "Course not found.\n";
                }
                break;
            }
            case '3': {
                student.clearAvailability();
                cout << "Availability cleared. Enter new availability slots.\n";
                cout << "How many availability time slots would you like to add? ";
                int slotCount;
                cin >> slotCount;
                cin.ignore();
                for (int i = 0; i < slotCount; ++i) {
                    cout << "\nTime slot #" << (i + 1) << "\n";
                    TimeSlot slot;
                    cout << "  Day (e.g., Mon, Tuesday): ";
                    getline(cin, slot.day);

                    int startMin, endMin;
                    while (true) {
                        cout << "  Start time (24h HH:MM, between 08:00 and 22:00): ";
                        getline(cin, slot.start);
                        if (!parseHHMMtoMinutes(slot.start, startMin)) {
                            cout << "    ✗ Invalid time format. Use HH:MM (e.g., 08:30, 14:00).\n";
                            continue;
                        }
                        if (startMin < kOpenMin || startMin > kCloseMin) {
                            cout << "    ✗ Start time must be between 08:00 and 22:00.\n";
                            continue;
                        }
                        break;
                    }
                    while (true) {
                        cout << "  End time   (24h HH:MM, no later than 22:00): ";
                        getline(cin, slot.end);
                        if (!parseHHMMtoMinutes(slot.end, endMin)) {
                            cout << "    ✗ Invalid time format. Use HH:MM (e.g., 09:45, 21:15).\n";
                            continue;
                        }
                        if (endMin < kOpenMin || endMin > kCloseMin) {
                            cout << "    ✗ End time must be between 08:00 and 22:00.\n";
                            continue;
                        }
                        if (endMin <= startMin) {
                            cout << "    ✗ End time must be after start time.\n";
                            continue;
                        }
                        break;
                    }
                    student.addAvailability(slot);
                }
                break;
            }
            case '4': {
                student.displayProfile();
                break;
            }
            case '5': {
                cout << "Returning to main menu.\n";
                break;
            }
            default:
                cout << "Invalid option, try again.\n";
        }
    } while (choice != '5');
}

void searchClassmates(StudentProfile& student, vector<StudentProfile>& allStudents) {
    bool foundAny = false;
    for (auto& other : allStudents) {
        if (student.getName() == other.getName()) continue; // skip self
        if (student.sharesCourseWith(other)) {
            cout << "\nFound classmate: " << other.getName() << " who shares courses.\n";
            //StudentProfile temp = student; // copy for proposing sessions
            student.findAndProposeStudySessions(other);
            student.displayProposedSessions();

            // Optional: prompt to confirm
            student.reviewProposals();
            student.displayConfirmedSessions();

            foundAny = true;
        }
    }
    if (!foundAny) {
        cout << "No classmates found who share courses and availability.\n";
    }
}

int main() {
    vector<StudentProfile> studentProfiles;
    char choice;

    cout << "Welcome to Study Buddy Profile Setup\n";

    do {
        StudentProfile student;
        student.createProfile();
        studentProfiles.push_back(student);

        cout << "\nAdd another student? Type y for yes n for no: ";
        cin >> choice;
        cin.ignore();
    } while (choice == 'y' || choice == 'Y');

    while (true) {
        cout << "\n--- Main Menu ---\n";
        cout << "Select a student by number:\n";
        for (size_t i = 0; i < studentProfiles.size(); ++i) {
            cout << (i + 1) << ". " << studentProfiles[i].getName() << "\n";
        }
        cout << studentProfiles.size() + 1 << ". Exit\n";

        int studentChoice;
        cout << "Enter choice: ";
        cin >> studentChoice;
        cin.ignore();

        if (studentChoice == (int)studentProfiles.size() + 1) {
            cout << "Exiting program.\n";
            break;
        }
        if (studentChoice < 1 || studentChoice >(int)studentProfiles.size()) {
            cout << "Invalid choice. Try again.\n";
            continue;
        }

        StudentProfile& selectedStudent = studentProfiles[studentChoice - 1];

        cout << "\nSelected student: " << selectedStudent.getName() << "\n";
        cout << "1. Update profile\n";
        cout << "2. Search for classmates in same courses\n";
        cout << "3. Display profile\n";
        cout << "4. Return to student selection\n";
        cout << "Choose action: ";
        char actionChoice;
        cin >> actionChoice;
        cin.ignore();

        switch (actionChoice) {
            case '1':
                updateProfile(selectedStudent);
                break;
            case '2':
                searchClassmates(selectedStudent, studentProfiles);
                break;
            case '3':
                selectedStudent.displayProfile();
                break;
            case '4':
                // Just return to student selection menu
                break;
            default:
                cout << "Invalid action. Returning to student selection.\n";
        }
    }

    return 0;
}

