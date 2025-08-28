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

public:
    void createProfile();
    void displayProfile();
    void addAvailability(const TimeSlot& slot)
    const vector<TimeSlot>& getAvailability() const;
};

#endif