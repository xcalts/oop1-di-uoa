#ifndef STUDENT_H
#define STUDENT_H

#include "person.h"
#include <string>

class Student : public Person
{
private:
    int studentID;
    std::string studyProgram;
    std::string dateStarted;
    std::string dateFinished;

public:
    // Constructors
    Student(int id, const std::string &major)
        : studentID(id), studyProgram(major){};

    // Getters
    int getStudentID() const
    {
        return studentID;
    }
    const std::string &getMajor() const
    {
        return studyProgram;
    }
    const std::string &getDateStarted() const
    {
        return dateStarted;
    }
    const std::string &getDateFinished() const
    {
        return dateFinished;
    }

    void setStudentID(int newStudentID)
    {
        studentID = newStudentID;
    }
    void setStudyProgram(const std::string &newMajor)
    {
        studyProgram = newMajor;
    }
    void setDateStarted(const std::string &newDateStarted)
    {
        if (!isValidDateFormat(newDateStarted))
        {
            throw std::invalid_argument("Invalid date format. Please use dd/mm/yyyy.");
        }

        dateStarted = newDateStarted;
    }
    void setDateFinished(const std::string &newDateFinished)
    {
        if (!isValidDateFormat(newDateFinished))
        {
            throw std::invalid_argument("Invalid date format. Please use dd/mm/yyyy.");
        }

        dateFinished = newDateFinished;
    }
    void printInfo() const
    {
        Person::printInfo();
        std::cout << "Student ID: " << getStudentID() << std::endl;
        std::cout << "Study Program: " << getMajor() << std::endl;
        std::cout << "Date Started: " << getDateStarted() << std::endl;
        std::cout << "Date Finished: " << getDateFinished() << std::endl;
    }
};

#endif // STUDENT_H
