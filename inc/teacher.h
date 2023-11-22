#ifndef TEACHER_H
#define TEACHER_H

#include "person.h"
#include <string>

class Teacher : public Person
{
private:
    std::string subject;

public:
    // Constructors
    Teacher(const std::string &firstName, const std::string &lastName, const std::string &subject);

    // Getter for subject
    const std::string &getSubject() const;

    // Setter for subject
    void setSubject(const std::string &newSubject);

    // Function to override the printInfo function in Person
    void printInfo() const override;
};

#endif // TEACHER_H
