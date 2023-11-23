#ifndef PERSON_H
#define PERSON_H

#include "misc.h"
#include <string>
#include <iostream>

class Person
{
private:
    /* Fields */
    std::string dateCreated;
    std::string firstName;
    std::string middleName;
    std::string lastName;
    std::string fatherName;
    std::string motherName;
    std::string identityID;
    std::string birthDate;

public:
    /* Constructors */
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
    }

    /* Getters */
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

    /* Setters */
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

    /* Functions */
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
};

#endif // PERSON_H
