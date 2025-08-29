#include "student_profile.h"
#include <sstream>
#include <iomanip>
#include <cctype>

// Parse "HH:MM" (24-hour) to minutes since midnight.
// Returns true on success; minutes = [0, 1440).
bool parseHHMMtoMinutes(const std::string& s, int& minutes) {
    // Enforce format HH:MM with leading zeros allowed (e.g., 08:05, 14:30)
    if (s.size() != 5 || s[2] != ':' || !isdigit(s[0]) || !isdigit(s[1]) || !isdigit(s[3]) || !isdigit(s[4])) {
        return false;
    }
    int hh = (s[0] - '0') * 10 + (s[1] - '0');
    int mm = (s[3] - '0') * 10 + (s[4] - '0');
    if (hh < 0 || hh > 23 || mm < 0 || mm > 59) return false;
    minutes = hh * 60 + mm;
    return true;
}

// Convert minutes since midnight to "h:MM AM/PM"
std::string minutesTo12h(int minutes) {
    minutes %= 24 * 60;
    int hh24 = minutes / 60;
    int mm = minutes % 60;
    bool isPM = (hh24 >= 12);
    int hh12 = hh24 % 12;
    if (hh12 == 0) hh12 = 12;
    std::ostringstream os;
    os << hh12 << ":" << std::setw(2) << std::setfill('0') << mm << (isPM ? " PM" : " AM");
    return os.str();
}

// Clamp/validate against availability window [08:00, 22:00]
constexpr int kOpenMin = 8 * 60;   // 480
constexpr int kCloseMin = 22 * 60; // 1320

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

            // Input & validate "HH:MM" 24h within 08:00–22:00 and start < end
            int startMin, endMin;
            while (true) {
                std::cout << "  Start time (24h HH:MM, between 08:00 and 22:00): ";
                std::getline(std::cin, slot.start);
                if (!parseHHMMtoMinutes(slot.start, startMin)) {
                    std::cout << "    ✗ Invalid time format. Use HH:MM (e.g., 08:30, 14:00).\n";
                    continue;
                }
                if (startMin < kOpenMin || startMin > kCloseMin) {
                    std::cout << "    ✗ Start time must be between 08:00 and 22:00.\n";
                    continue;
                }
                break;
            }

            while (true) {
                std::cout << "  End time   (24h HH:MM, no later than 22:00): ";
                std::getline(std::cin, slot.end);
                if (!parseHHMMtoMinutes(slot.end, endMin)) {
                    std::cout << "    ✗ Invalid time format. Use HH:MM (e.g., 09:45, 21:15).\n";
                    continue;
                }
                if (endMin < kOpenMin || endMin > kCloseMin) {
                    std::cout << "    ✗ End time must be between 08:00 and 22:00.\n";
                    continue;
                }
                if (endMin <= startMin) {
                    std::cout << "    ✗ End time must be after start time.\n";
                    continue;
                }
                break;
        }


            //cout << "  Start time (24h e.g., 14:00): ";
            //getline(cin, slot.start);
            //cout << "  End time   (24h e.g., 16:00): ";
            //getline(cin, slot.end);
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
                int startMin, endMin;
                // If parsing ever fails (shouldn’t), just print raw.
                if (parseHHMMtoMinutes(s.start, startMin) && parseHHMMtoMinutes(s.end, endMin)) {
                    std::cout << "  " << (i + 1) << ". " << s.day
                            << " " << minutesTo12h(startMin) << " - " << minutesTo12h(endMin) << "\n";
                } else {
                    std::cout << "  " << (i + 1) << ". " << s.day
                            << " " << s.start << " - " << s.end << "\n";
                }
            }
        }
 }

void StudentProfile::addAvailability(const TimeSlot& slot) {
    availability.push_back(slot);
}

const vector<TimeSlot>& StudentProfile::getAvailability() const {
    return availability;
}

void StudentProfile::addCourse(const std::string& course) {
    courses.push_back(course);
}

bool StudentProfile::removeCourse(const std::string& course) {
    for (auto it = courses.begin(); it != courses.end(); ++it) {
        if (*it == course) {
            courses.erase(it);
            return true;
        }
    }
    return false;
}

void StudentProfile::clearAvailability() {
    availability.clear();
}

void StudentProfile::findAndProposeStudySessions(const StudentProfile& classmate) {
    bool found = false;

    for (const auto& mySlot : availability) {
        int myStart, myEnd;
        if (!parseHHMMtoMinutes(mySlot.start, myStart) ||
            !parseHHMMtoMinutes(mySlot.end, myEnd)) {
            continue; // skip invalid
        }

        for (const auto& theirSlot : classmate.getAvailability()) {
            if (mySlot.day != theirSlot.day) continue; // must be same day

            int theirStart, theirEnd;
            if (!parseHHMMtoMinutes(theirSlot.start, theirStart) ||
                !parseHHMMtoMinutes(theirSlot.end, theirEnd)) {
                continue; // skip invalid
            }

            // Calculate overlap
            int overlapStart = max(myStart, theirStart);
            int overlapEnd   = min(myEnd, theirEnd);

            if (overlapStart < overlapEnd) {
                string proposal = "Session with " + classmate.getName() +
                                  " on " + mySlot.day +
                                  " " + minutesTo12h(overlapStart) +
                                  " - " + minutesTo12h(overlapEnd);
                proposedSessions.push_back(proposal);
                found = true;
            }
        }
    }

    if (!found) {
        cout << "No overlapping availability with " << classmate.getName() << ".\n";
    }
}

void StudentProfile::displayProposedSessions() const {
    cout << "\n---Proposed Study Sessions for " << studentName << " ---\n";
    if (proposedSessions.empty()) {
        cout << "  (none)\n";
    } else {
        for (size_t i = 0; i < proposedSessions.size(); ++i) {
            cout << "  " << (i + 1) << ". " << proposedSessions[i] << "\n";
        }
    }
}

void StudentProfile::reviewProposals() {
    if (proposedSessions.empty()) {
        cout << studentName << " has no proposals to review.\n";
        return;
    }

    cout << "\n--- Review Proposed Study Sessions for " << studentName << " ---\n";
    for (size_t i = 0; i < proposedSessions.size(); ++i) {
        cout << (i + 1) << ". " << proposedSessions[i] << "\n";
        cout << "   Confirm this session? (y/n): ";
        char choice;
        cin >> choice;
        cin.ignore();
        if (choice == 'y' || choice == 'Y') {
            confirmedSessions.push_back(proposedSessions[i]);
            cout << "   ✓ Confirmed!\n";
        } else {
            cout << "   ✗ Declined.\n";
        }
    }
    // After reviewing, clear proposals (optional, since they’ve been handled)
    proposedSessions.clear();
}

void StudentProfile::displayConfirmedSessions() const {
    cout << "\n--- Confirmed Study Sessions for " << studentName << " ---\n";
    if (confirmedSessions.empty()) {
        cout << "  (none)\n";
    } else {
        for (size_t i = 0; i < confirmedSessions.size(); ++i) {
            cout << "  " << (i + 1) << ". " << confirmedSessions[i] << "\n";
        }
    }
}

bool StudentProfile::sharesCourseWith(const StudentProfile& other) const {
    for (const auto& course : courses) {
        for (const auto& otherCourse : other.courses) {
            if (course == otherCourse) {
                return true;
            }
        }
    }
    return false;
}
