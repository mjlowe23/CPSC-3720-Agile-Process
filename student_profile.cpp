#include "student_profile.h"

void StudentProfile::createProfile()  {
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
        // ---- New: collect availability ----
        cout << "\nHow many availability time slots would you like to add? ";
        int slotCount;
        cin >> slotCount;
        cin.ignore(); // consume newline

        for (int i = 0; i < slotCount; ++i) {
            cout << "\nTime slot #" << (i + 1) << "\n";
            TimeSlot slot;
            cout << "  Day (e.g., Mon, Tuesday): ";
            getline(cin, slot.day);
            cout << "  Start time (24h e.g., 14:00): ";
            getline(cin, slot.start);
            cout << "  End time   (24h e.g., 16:00): ";
            getline(cin, slot.end);
            availability.push_back(slot);
        }
}

void StudentProfile::displayProfile() {
        cout << "\n--- Student Profile ---\n";
        cout << "Name: " << studentName << "\n";
        cout << "Courses enrolled in:\n";
        for (size_t i = 0; i < courses.size(); ++i) {
            cout << "  " << (i + 1) << ". " << courses[i] << "\n";
        }

        // ---- New: show availability ----
        cout << "Availability time slots:\n";
        if (availability.empty()) {
            cout << "  (none)\n";
        } else {
            for (size_t i = 0; i < availability.size(); ++i) {
                const auto& s = availability[i];
                cout << "  " << (i + 1) << ". " << s.day
                    << " " << s.start << " - " << s.end << "\n";
            }
        }
 }

void StudentProfile::addAvailability(const TimeSlot& slot) {
    availability.push_back(slot);
}

const vector<TimeSlot>& StudentProfile::getAvailability() const {
    return availability;
}
