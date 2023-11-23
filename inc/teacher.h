#ifndef TEACHER_H
#define TEACHER_H

#include "person.h"
#include <string>

class Teacher : public Person
{
private:
    std::string subject;

public:
    /* Constructors */
    Teacher(const std::string &firstName, const std::string &lastName, const std::string &subject){};

    /* Getters */
    const std::string &Teacher::getSubject() const
    {
        return subject;
    }

    /* Setters */
    void Teacher::setSubject(const std::string &newSubject)
    {
        subject = newSubject;
    }

    /* Functions */
    void printInfo() const override
    {
        Person::printInfo();
        std::cout << "Subject: " << getSubject() << std::endl;
    }
};

#endif // TEACHER_H
