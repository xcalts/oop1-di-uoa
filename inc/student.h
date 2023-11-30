#ifndef STUDENT_H
#define STUDENT_H

#include "person.h"
#include <string>

class Student : public Person
{
private:
    // Fields
    int studentID;
    std::string studyProgram;
    std::string dateStarted;
    std::string dateFinished;

public:
    // Constructors
    Student(const std::string &firstName,
            const std::string &middleName,
            const std::string &lastName,
            const std::string &fatherName,
            const std::string &motherName,
            const std::string &identityID,
            const std::string &birthDate,
            int id,
            const std::string &studyProgram,
            const std::string &startedDate,
            const std::string &finishedDate)
        : Person(firstName, middleName, lastName, fatherName, motherName, identityID, birthDate),
          studentID(id),
          studyProgram(studyProgram),
          dateStarted(startedDate),
          dateFinished(finishedDate)
    {
        if (!isValidDateFormat(startedDate) || !isValidDateFormat(finishedDate))
        {
            throw std::invalid_argument("Invalid date format. Please use dd/mm/yyyy.");
        }
    }

    Student() : Person() {}
    // Deconstructor
    virtual ~Student() {}

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

    // Setters
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
        std::cout << "== STUDENT ==" << std::endl;
        Person::printInfo();
        std::cout << "Student ID: " << getStudentID() << std::endl;
        std::cout << "Study Program: " << getMajor() << std::endl;
        std::cout << "Date Started: " << getDateStarted() << std::endl;
        std::cout << "Date Finished: " << getDateFinished() << std::endl;
    }

    // Overloading output operator for Student
    friend std::ostream &operator<<(std::ostream &out, const Student &student)
    {
        out << "== STUDENT ==" << std::endl;
        out << static_cast<const Person &>(student); // Output the Person part
        out << "Student ID: " << student.getStudentID() << std::endl;
        out << "Study Program: " << student.getMajor() << std::endl;
        out << "Date Started: " << student.getDateStarted() << std::endl;
        out << "Date Finished: " << student.getDateFinished() << std::endl;

        return out;
    }

    // Overloading input operator
    friend std::istream &operator>>(std::istream &in, Student &student)
    {
        Person &person = student;

        in >> person;

        int studentID;
        std::string major, dateStarted, dateFinished;

        std::cout << "Enter Student ID: ";
        in >> studentID;
        student.setStudentID(studentID);

        std::cout << "Enter Study Program: ";
        in >> major;
        student.setStudyProgram(major);

        std::cout << "Enter Date Started (dd/mm/yyyy): ";
        in >> dateStarted;
        student.setDateStarted(dateStarted);

        std::cout << "Enter Date Finished (dd/mm/yyyy): ";
        in >> dateFinished;
        student.setDateFinished(dateFinished);

        return in;
    }
};

#endif // STUDENT_H
