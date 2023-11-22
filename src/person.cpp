#include "person.h"
#include "misc.h"

#include <iostream>

const std::string &Person::getDateCreated() const
{
    return dateCreated;
}

const std::string &Person::getDateModified() const
{
    return dateModified;
}

const std::string &Person::getFirstName() const
{
    return firstName;
}

const std::string &Person::getMiddleName() const
{
    return middleName;
}

const std::string &Person::getLastName() const
{
    return lastName;
}

const std::string &Person::getFatherName() const
{
    return fatherName;
}

const std::string &Person::getMotherName() const
{
    return motherName;
}

const std::string &Person::getIdentityID() const
{
    return identityID;
}

const std::string &Person::getBirthDate() const
{
    return birthDate;
}

void Person::setDateModified(const std::string &newDateModified)
{
    if (!isValidDateFormat(newDateModified))
    {
        throw std::invalid_argument("Invalid date format. Please use dd/mm/yyyy.");
    }

    dateModified = newDateModified;
}

void Person::setFirstName(const std::string &newFirstName)
{
    firstName = newFirstName;
}

void Person::setMiddleName(const std::string &newMiddleName)
{
    middleName = newMiddleName;
}

void Person::setLastName(const std::string &newLastName)
{
    lastName = newLastName;
}

void Person::setFatherName(const std::string &newFatherName)
{
    fatherName = newFatherName;
}

void Person::setMotherName(const std::string &newMotherName)
{
    motherName = newMotherName;
}

void Person::setIdentityID(const std::string &newIdentityID)
{
    identityID = newIdentityID;
}

void Person::setBirthDate(const std::string &newBirthDate)
{
    if (!isValidDateFormat(newBirthDate))
    {
        throw std::invalid_argument("Invalid date format. Please use dd/mm/yyyy.");
    }

    birthDate = newBirthDate;
}

void Person::printInfo() const
{
    std::cout << "== Person ==" << std::endl;
}