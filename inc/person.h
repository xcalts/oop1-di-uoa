#ifndef PERSON_H
#define PERSON_H

#include "misc.h"
#include <string>
#include <iostream>

using namespace std;

class Person
{
private:
    // Fields
    string identityID;
    string firstName;
    string lastName;
    string birthDate;

public:
    // Constructors
    Person() { }
    Person(const string &identityID,
           const string &firstName,
           const string &lastName,
           const string &birthDate)
        : identityID(identityID),
          firstName(firstName),
          lastName(lastName),
          birthDate(birthDate)
    {}

    // Deconstructors
    virtual ~Person()
    {
    }

    // Getters
    const string &getIdentityID() const
    {
        return identityID;
    }
    const string &getFirstName() const
    {
        return firstName;
    }
    const string &getLastName() const
    {
        return lastName;
    }
    const string &getBirthDate() const
    {
        return birthDate;
    }

    // Setters
    void setIdentityID(const string &newIdentityID)
    {
        identityID = newIdentityID;
    }
    void setFirstName(const string &newFirstName)
    {
        firstName = newFirstName;
    }
    void setLastName(const string &newLastName)
    {
        lastName = newLastName;
    }
    void setBirthDate(const string &newBirthDate)
    {
        if (!isValidDateFormat(newBirthDate))
        {
            throw std::invalid_argument("Invalid date format. Please use dd/mm/yyyy.");
        }

        birthDate = newBirthDate;
    }

};

#endif // PERSON_H
