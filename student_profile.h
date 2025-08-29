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
    vector<string> proposedSessions;
    vector<string> confirmedSessions;

public:
    void createProfile();
    void displayProfile();
    void addAvailability(const TimeSlot& slot);
    const vector<TimeSlot>& getAvailability() const;


    // Story 5
    void findAndProposeStudySessions(const StudentProfile& classmate);
    void displayProposedSessions() const;

    // NEW: confirmation system
    void reviewProposals();               // confirm/decline
    void displayConfirmedSessions() const; // show confirmed sessions

    string getName() const { return studentName; }

    void addCourse(const std::string& course);
    bool removeCourse(const std::string& course);
    void clearAvailability();


};

#endif