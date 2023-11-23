#ifndef SECRETARY_H
#define SECRETARY_H

#include "person.h"
#include <vector>

class Secretary
{
private:
    std::vector<Person> personList;

public:
    /* Functions */
    void addPerson(const Person &person)
    {
        personList.push_back(person);
    }
    const Person *searchPersonByIdentityID(const std::string &identityID) const
    {
        auto it = std::find_if(personList.begin(), personList.end(),
                               [&identityID](const Person &person)
                               {
                                   return person.getIdentityID() == identityID;
                               });

        if (it != personList.end())
        {
            return &(*it);
        }
        else
        {
            return nullptr; // Person not found
        }
    }
};

#endif // SECRETARY_H
