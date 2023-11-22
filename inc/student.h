#ifndef STUDENT_H
#define STUDENT_H

#include "person.h" // Include the base class header

class Student : public Person
{
private:
    int studentID;
    std::string studyProgram;
    std::string dateStarted;
    std::string dateFinished;

public:
    // Constructors
    Student(int id, const std::string &major);

    // Getters
    int getStudentID() const;
    const std::string &getMajor() const;
    const std::string &getDateStarted() const;
    const std::string &getDateFinished() const;

    // Setters
    void setStudentID(int newStudentID);
    void setStudyProgram(const std::string &newMajor);
    void setDateStarted(const std::string &newDateStarted);
    void setDateFinished(const std::string &newDateFinished);
    void printInfo() const override;
};

#endif // STUDENT_H
