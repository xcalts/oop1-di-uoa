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
    vector<string> hasPassed; // The courses (IDs) that the student has passed.

public:
    /* Constructors */
    Student() : Person() {}

    /* Deconstructor */
    virtual ~Student() {}

    /* Getters */
    Semester getCurrentSemester() const {
        return currentSemester;
    }
    vector<string> getHasPassed() const {
        return hasPassed;
    }

    /* Setters */ 
    void setCurrentSemester(Semester semester) {
        currentSemester = semester;
    }
    void setHasPassed(const vector<string> ids)
    {
        hasPassed = ids;
    }
    void addPassedCourse(const std::string& courseId) {
        hasPassed.push_back(courseId);
    }
    bool removePassedCourse(const std::string& courseId) {
        auto it = std::find(hasPassed.begin(), hasPassed.end(), courseId);
        if (it != hasPassed.end()) {
            hasPassed.erase(it);
            return true;
        }
        return false;
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
        student.setHasPassed(splitString(tokens[5], ';'));

        return student;
    }
    string toCSVString() const {
        stringstream ss;
        ss << getIdentityID() << "," << getFirstName() << "," << getLastName() << "," << getBirthDate() << "," << getCurrentSemester() << ",";

        // Serialize hasPassed
        for (size_t i = 0; i < getHasPassed().size(); ++i) {
            ss << hasPassed[i];
            if (i < hasPassed.size() - 1) ss << ";";
        }

        return ss.str();
    }
};

#endif // STUDENT_H
