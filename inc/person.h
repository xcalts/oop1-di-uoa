#ifndef PERSON_H
#define PERSON_H

#include "misc.h"
#include <string>
#include <iostream>

class Person
{
private:
    // Static
    static int personCount;

    // Fields
    std::string dateCreated;
    std::string firstName;
    std::string middleName;
    std::string lastName;
    std::string fatherName;
    std::string motherName;
    std::string identityID;
    std::string birthDate;

public:
    // Constructors
    Person(const std::string &firstName,
           const std::string &middleName,
           const std::string &lastName,
           const std::string &fatherName,
           const std::string &motherName,
           const std::string &identityID,
           const std::string &birthDate)
        : firstName(firstName),
          middleName(middleName),
          lastName(lastName),
          fatherName(fatherName),
          motherName(motherName),
          identityID(identityID),
          birthDate(birthDate)
    {
        if (!isValidDateFormat(birthDate))
        {
            throw std::invalid_argument("Invalid date format. Please use dd/mm/yyyy.");
        }

        dateCreated = getCurrentDateAsString();
        personCount++;
    }
    Person()
    {
        dateCreated = getCurrentDateAsString();
        personCount++;
    }

    // Deconstructors
    virtual ~Person()
    {
        personCount--;
    }

    // Getters
    static int getPersonCount()
    {
        return personCount;
    }
    const std::string &getDateCreated() const
    {
        return dateCreated;
    }
    const std::string &getFirstName() const
    {
        return firstName;
    }
    const std::string &getMiddleName() const
    {
        return middleName;
    }
    const std::string &getLastName() const
    {
        return lastName;
    }
    const std::string &getFatherName() const
    {
        return fatherName;
    }
    const std::string &getMotherName() const
    {
        return motherName;
    }
    const std::string &getIdentityID() const
    {
        return identityID;
    }
    const std::string &getBirthDate() const
    {
        return birthDate;
    }

    // Setters
    void setDateCreated(const std::string &newDateCreated)
    {
        if (!isValidDateFormat(newDateCreated))
        {
            throw std::invalid_argument("Invalid date format. Please use dd/mm/yyyy.");
        }

        dateCreated = newDateCreated;
    }
    void setFirstName(const std::string &newFirstName)
    {
        firstName = newFirstName;
    }
    void setMiddleName(const std::string &newMiddleName)
    {
        middleName = newMiddleName;
    }
    void setLastName(const std::string &newLastName)
    {
        lastName = newLastName;
    }
    void setFatherName(const std::string &newFatherName)
    {
        fatherName = newFatherName;
    }
    void setMotherName(const std::string &newMotherName)
    {
        motherName = newMotherName;
    }
    void setIdentityID(const std::string &newIdentityID)
    {
        identityID = newIdentityID;
    }
    void setBirthDate(const std::string &newBirthDate)
    {
        if (!isValidDateFormat(newBirthDate))
        {
            throw std::invalid_argument("Invalid date format. Please use dd/mm/yyyy.");
        }

        birthDate = newBirthDate;
    }

    // Functions
    void printInfo() const
    {
        std::cout << "First Name: " << getFirstName() << std::endl;
        std::cout << "Middle Name: " << getMiddleName() << std::endl;
        std::cout << "Last Name: " << getLastName() << std::endl;
        std::cout << "Father's Name: " << getFatherName() << std::endl;
        std::cout << "Mother's Name: " << getMotherName() << std::endl;
        std::cout << "Identity ID: " << getIdentityID() << std::endl;
        std::cout << "Birth Date: " << getBirthDate() << std::endl;
        std::cout << "Date Created: " << getDateCreated() << std::endl;
    }

    // Overloading output operator
    friend std::ostream &operator<<(std::ostream &out, const Person &person)
    {
        out << "First Name: " << person.getFirstName() << std::endl;
        out << "Middle Name: " << person.getMiddleName() << std::endl;
        out << "Last Name: " << person.getLastName() << std::endl;
        out << "Father's Name: " << person.getFatherName() << std::endl;
        out << "Mother's Name: " << person.getMotherName() << std::endl;
        out << "Identity ID: " << person.getIdentityID() << std::endl;
        out << "Birth Date: " << person.getBirthDate() << std::endl;
        out << "Date Created: " << person.getDateCreated() << std::endl;

        return out;
    }

    // Overloading input operator
    friend std::istream &operator>>(std::istream &in, Person &person)
    {
        // Assuming the input format is the same as the printInfo format
        std::string firstName, middleName, lastName, fatherName, motherName, identityID, birthDate;

        std::cout << "Enter First Name: ";
        in >> firstName;
        person.setFirstName(firstName);

        std::cout << "Enter Middle Name: ";
        in >> middleName;
        person.setMiddleName(middleName);

        std::cout << "Enter Last Name: ";
        in >> lastName;
        person.setLastName(lastName);

        std::cout << "Enter Father's Name: ";
        in >> fatherName;
        person.setFatherName(fatherName);

        std::cout << "Enter Mother's Name: ";
        in >> motherName;
        person.setMotherName(motherName);

        std::cout << "Enter Identity ID: ";
        in >> identityID;
        person.setIdentityID(identityID);

        std::cout << "Enter Birth Date (dd/mm/yyyy): ";
        in >> birthDate;
        person.setBirthDate(birthDate);

        return in;
    }
};

// Initialize it out of the class definition
int Person::personCount = 0;

#endif // PERSON_H
