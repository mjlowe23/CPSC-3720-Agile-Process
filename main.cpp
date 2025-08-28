#include "student_profile.h"

int main() {
    
    vector<StudentProfile> studentProfiles;
    char choice;

    cout << "Welcome to Study Buddy Profile Setup\n";

    do{
        StudentProfile student;
        student.createProfile();
        studentProfiles.push_back(student);

        cout << "\nAdd another student? Type y for yes n for no: ";
        cin >> choice;
        cin.ignore();
    }
    while(choice == 'y'|| choice == 'Y');

    cout << "\nAll profiles created.\n";

    for(size_t i = 0; i < studentProfiles.size(); ++i){
        cout << "\nStudent #" << (i + 1) << ": \n";
        studentProfiles[i].displayProfile();
    }

    cout << "\nChecking study session proposals...\n";
    if (studentProfiles.size() >= 2) {
        studentProfiles[0].findAndProposeStudySessions(studentProfiles[1]);
        studentProfiles[0].displayProposedSessions();

        // Ask student 0 to confirm/decline
        studentProfiles[0].reviewProposals();
        studentProfiles[0].displayConfirmedSessions();
    }

return 0;

}

