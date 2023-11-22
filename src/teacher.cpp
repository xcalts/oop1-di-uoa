#include "person.h"
#include "teacher.h"

#include <iostream>

// Constructor
Teacher::Teacher(const std::string &firstName, const std::string &lastName, const std::string &subject) {}

// Getters
const std::string &Teacher::getSubject() const
{
    return subject;
}

void Teacher::setSubject(const std::string &newSubject)
{
    subject = newSubject;
}

void Teacher::printInfo() const
{
    // Add additional information specific to Teacher
    std::cout << "== Teacher == " << std::endl;
    std::cout << "Subject: " << getSubject() << std::endl;
}
