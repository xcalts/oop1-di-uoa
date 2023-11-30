#include "secretary.h"
#include "person.h"
#include "student.h"
#include "teacher.h"

#include <iostream>

int main()
{
    try
    {
        Secretary d;

        // People
        Person *john = new Person("John", "Doe", "L.", "AA", "BB", "ID123", "01/01/1990");
        Person *alice = new Person("Alice", "Smith", "L.", "AA", "BB", "ID456", "02/02/1995");
        Student *petros = new Student("Petros", "G.", "L.", "AA", "BB", "ID001", "03/03/1993", 1001, "Computer Science", "01/09/2020", "01/07/2024");
        Student *nikos = new Student("Nikos", "K.", "L.", "AA", "BB", "ID002", "04/04/1994", 1002, "Mathematics", "01/09/2021", "01/07/2025");
        Teacher *christos = new Teacher("Dr.", "Smith", "Computer Science");
        Teacher *dimitris = new Teacher("Prof.", "Johnson", "Mathematics");

        // =
        Secretary _d;
        _d = d;

        // Adding
        d = d + john + alice + petros + nikos + christos + dimitris;

        // Searching
        d.searchPerson();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}