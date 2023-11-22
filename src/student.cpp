#include "student.h"
#include "misc.h"

#include <iostream>
#include <chrono>
#include <iomanip>

// Constructors
Student::Student(int id, const std::string &major)
    : studentID(id), studyProgram(major)
{
    // You can initialize dateStarted and dateFinished if needed
}

// Getter for student ID
int Student::getStudentID() const
{
    return studentID;
}

// Getter for major
const std::string &Student::getMajor() const
{
    return studyProgram;
}

// Getter for dateStarted
const std::string &Student::getDateStarted() const
{
    return dateStarted;
}

// Getter for dateFinished
const std::string &Student::getDateFinished() const
{
    return dateFinished;
}

// Setter for student ID
void Student::setStudentID(int newStudentID)
{
    studentID = newStudentID;
}

// Setter for major
void Student::setStudyProgram(const std::string &newMajor)
{
    studyProgram = newMajor;
}

// Setter for dateStarted
void Student::setDateStarted(const std::string &newDateStarted)
{
    if (!isValidDateFormat(newDateStarted))
    {
        throw std::invalid_argument("Invalid date format. Please use dd/mm/yyyy.");
    }

    dateStarted = newDateStarted;
}

// Setter for dateFinished
void Student::setDateFinished(const std::string &newDateFinished)
{
    if (!isValidDateFormat(newDateFinished))
    {
        throw std::invalid_argument("Invalid date format. Please use dd/mm/yyyy.");
    }

    dateFinished = newDateFinished;
}

void Student::printInfo() const
{
    std::cout << "== Student ==" << std::endl;
    std::cout << "Student ID: " << getStudentID() << std::endl;
    std::cout << "Study Program: " << getMajor() << std::endl;
    std::cout << "Date Started: " << getDateStarted() << std::endl;
    std::cout << "Date Finished: " << getDateFinished() << std::endl;
}