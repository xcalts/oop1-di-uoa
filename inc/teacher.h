#ifndef TEACHER_H
#define TEACHER_H

#include "person.h"
#include <string>

class Teacher : public Person
{
private:
    // Fields
    std::string subject;

public:
    // Constructors
    Teacher(const std::string &firstName, const std::string &lastName, const std::string &subject){};
    Teacher() : Person() {}

    // Getters
    const std::string getSubject() const
    {
        return subject;
    }

    // Setters
    void setSubject(const std::string &newSubject)
    {
        subject = newSubject;
    }

    // Functions
    void printInfo() const
    {
        std::cout << "== TEACHER ==" << std::endl;
        Person::printInfo();
        std::cout << "Subject: " << getSubject() << std::endl;
    }

    // Overloading output operator for Teacher
    friend std::ostream &operator<<(std::ostream &out, const Teacher &teacher)
    {
        out << "== TEACHER ==" << std::endl;
        out << static_cast<const Person &>(teacher); // Output the Person part
        out << "Subject: " << teacher.getSubject() << std::endl;
        return out;
    }

    // Overloading input operator for Teacher
    friend std::istream &operator>>(std::istream &in, Teacher &teacher)
    {
        // Assuming the input format is the same as the printInfo format
        Person &person = teacher; // Upcast to Person to handle the common attributes

        in >> person; // Input the Person part

        std::string subject;
        std::cout << "Enter Subject: ";
        in >> subject;
        teacher.setSubject(subject);

        return in;
    }
};

#endif // TEACHER_H
