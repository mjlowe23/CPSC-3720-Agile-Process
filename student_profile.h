#ifndef STUDENT_PROFILE_H
#define STUDENT_PROFILE_H

#include <vector>
#include <string>
#include <iostream>
using namespace std;

struct TimeSlot {
    string day;
    string start;
    string end;
};

class StudentProfile {
private:
    string studentName;
    vector<string> courses;
    vector<TimeSlot> availability;
    vector<string>availableTimeSlots;
    vector<string> proposedSessions;

public:
    void createProfile();
    void displayProfile();
    void addAvailability(const TimeSlot& slot);
    const vector<TimeSlot>& getAvailability() const;

    // time slot function (user story 4)
    void addAvailableTimeSlots();
    void displayAvailableTimeSlots();

    // time slot function (user story 5)
    void proposeStudySession(const string& classmateName, const string& timeSlot);
    void displayProposedSessions();

};

#endif