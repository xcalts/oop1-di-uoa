#include "secretary.h"
#include "person.h"
#include <iostream>

int main()
{
    // Example usage:
    Secretary secretary;

    // Adding persons
    Person person1("John", "William", "Doe", "George", "Jane", "123456789", "01/01/1990");
    secretary.addPerson(person1);

    Person person2("Jane", "Marie", "Smith", "Michael", "Emily", "987654321", "15/05/1985");
    secretary.addPerson(person2);

    // Searching for a person
    const std::string searchIdentityID = "123456789";
    const Person *foundPerson = secretary.searchPersonByIdentityID(searchIdentityID);

    if (foundPerson != nullptr)
    {
        std::cout << "Person found:" << std::endl;
        foundPerson->printInfo();
    }
    else
    {
        std::cout << "Person not found." << std::endl;
    }

    return 0;
}