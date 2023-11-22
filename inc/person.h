#ifndef PERSON_H
#define PERSON_H

class Person
{
private:
    /* Fields */
    std::string dateCreated;
    std::string dateModified;
    std::string firstName;
    std::string middleName;
    std::string lastName;
    std::string fatherName;
    std::string motherName;
    std::string identityID;
    std::string birthDate;

public:
    /* Getters */
    const std::string &getDateCreated() const;
    const std::string &getDateModified() const;
    const std::string &getFirstName() const;
    const std::string &getMiddleName() const;
    const std::string &getLastName() const;
    const std::string &getFatherName() const;
    const std::string &getMotherName() const;
    const std::string &getIdentityID() const;
    const std::string &getBirthDate() const;

    /* Setters */
    void setDateCreated(const std::string &newDateCreated);
    void setDateModified(const std::string &newDateModified);
    void setFirstName(const std::string &newFirstName);
    void setMiddleName(const std::string &newMiddleName);
    void setLastName(const std::string &newLastName);
    void setFatherName(const std::string &newFatherName);
    void setMotherName(const std::string &newMotherName);
    void setIdentityID(const std::string &newIdentityID);
    void setBirthDate(const std::string &newBirthDate);

    /* Functions */
    virtual void printInfo() const;
};

#endif // PERSON_H
