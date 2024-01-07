#ifndef PERSON_H
#define PERSON_H

#include "misc.h"
#include <string>
#include <iostream>

using namespace std;

class Person
{
private:
    /* Fields */
    string identityId; // The UUID of the person.
    string firstName;  // The first name of the person.
    string lastName;   // The last name of the person.
    string birthDate;  // The birth date of the person.

public:
    /* Constructors */
    Person() { }
    Person(const string &identityId,
           const string &firstName,
           const string &lastName,
           const string &birthDate)
        : identityId(identityId),
          firstName(firstName),
          lastName(lastName),
          birthDate(birthDate)
    {}

    /* Deconstructors */
    virtual ~Person()
    {
    }

    /* Getters */
    const string &getIdentityID() const
    {
        return identityId;
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

    /* Setters */
    void setIdentityID(const string &newIdentityID)
    {
        identityId = newIdentityID;
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
        birthDate = newBirthDate;
    }

};

#endif // PERSON_H
