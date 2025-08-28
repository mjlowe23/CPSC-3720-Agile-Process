#ifndef STUDENT_PROFILE_H
#define STUDENT_PROFILE_H

#include <vector>
#include <string>
#include <iostream>
using namespace std;

class StudentProfile {
private:
    string studentName;
    vector<string> courses;

public:
    void createProfile();
    void displayProfile();

};

#endif