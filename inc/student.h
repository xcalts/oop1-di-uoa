#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>

#include "person.h"
#include "semester.h"

using namespace std;

class Student : public Person
{
private:
    /* Fields */
    Semester currentSemester; // The semester that the student is already in.

public:
    /* Constructors */
    Student() : Person() {}

    /* Deconstructor */
    virtual ~Student() {}

    /* Getters */
    Semester getCurrentSemester() const {
        return currentSemester;
    }
    
    /* Setters */ 
    void setCurrentSemester(Semester semester) {
        currentSemester = semester;
    }
    
    /* CSV */ 
    static Student fromCSVLine(const string& line) {
        stringstream ss(line);
        string token;
        vector<string> tokens;

        // Split line by commas
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        Student student;
        student.setIdentityID(tokens[0]);
        student.setFirstName(tokens[1]);
        student.setLastName(tokens[2]);
        student.setBirthDate(tokens[3]);
        student.setCurrentSemester(Semester(stringToInt(tokens[4].c_str())));

        return student;
    }
    string toCSVString() const {
        stringstream ss;
        ss << getIdentityID() << "," << getFirstName() << "," << getLastName() << "," << getBirthDate() << "," << getCurrentSemester();

        return ss.str();
    }
};

#endif // STUDENT_H
