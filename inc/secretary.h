#ifndef SECRETARY_H
#define SECRETARY_H

#include "person.h"
#include <vector>
#include <iostream>
#include <algorithm>

class Secretary
{
private:
    std::vector<Person *> department;

public:
    // Constructors
    Secretary() {}

    // Destructor
    ~Secretary()
    {
        // Clean up dynamically allocated memory
        for (Person *person : department)
        {
            delete person;
        }
    }

    // Copy Constructor
    Secretary(const Secretary &other)
    {
        for (const Person *person : other.department)
        {
            department.push_back(new Person(*person));
        }
    }

    // Overloading + operator to add a Person using dynamic memory allocation
    Secretary &operator+(Person *newPerson)
    {
        department.push_back(new Person(*newPerson));
        return *this;
    }

    // Overloading input operator for Secretary
    friend std::istream &operator>>(std::istream &in, Secretary &secretary)
    {
        // Assuming the input format is the same as the printInfo format for Person
        Person *newPerson = new Person();
        in >> *newPerson;
        secretary = secretary + newPerson; // Using the + operator to add the Person
        return in;
    }

    // Overloading output operator for Secretary
    friend std::ostream &operator<<(std::ostream &out, const Secretary &secretary)
    {
        out << "== DEPARTMENT ==" << std::endl;
        for (const Person *person : secretary.department)
        {
            out << *person;
        }
        return out;
    }

    // Function to search for a specific person
    void searchPerson() const
    {
        std::string searchID;
        std::cout << "Enter the Identity ID to search for: ";
        std::cin >> searchID;

        auto it = std::find_if(department.begin(), department.end(), [searchID](const Person *person)
                               { return person->getIdentityID() == searchID; });

        if (it != department.end())
        {
            std::cout << "Person Found:" << std::endl;
            std::cout << *(*it);
        }
        else
        {
            std::cout << "Person not found in the department." << std::endl;
        }
    }

    // Overloading = operator
    Secretary &operator=(const Secretary &other)
    {
        if (this != &other)
        {
            // Clean up existing memory
            for (Person *person : department)
            {
                delete person;
            }
            department.clear();

            // Deep copy the department
            for (const Person *person : other.department)
            {
                department.push_back(new Person(*person));
            }
        }
        return *this;
    }
};

#endif // SECRETARY_H
