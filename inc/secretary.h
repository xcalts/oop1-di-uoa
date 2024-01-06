#ifndef SECRETARY_H
#define SECRETARY_H

#include <algorithm>
#include <curses.h>
#include <vector>
#include <iostream>
#include <fstream>

#include "course.h"
#include "misc.h"
#include "professor.h"
#include "student.h"

#define COURSES_CSV_FILE "./data/courses.csv"
#define STUDENTS_CSV_FILE "./data/students.csv"
#define PROFESSORS_CSV_FILE "./data/professors.csv"


using namespace std;

class Secretary
{
private:
    vector<Course> courses;
    vector<Professor> professors;
    vector<Student> students;

public:
    // Constructors
    Secretary() {}

    // Destructor
    ~Secretary() {}

    // API
    // Courses
    void createCourse(WINDOW *win) {
        // Variables
        int currentLine = 1;
        char buffer[100];
        Course newCourse;

        // Ask for Input
        mvwprintw(win, currentLine++, 1, "Complete the following questions to create a new course.");
        mvwprintw(win, currentLine++, 1, "[?] What is the ID of the course? ");
        echo();
        wgetnstr(win, buffer, 100);
        newCourse.setCourseId(string(buffer));

        mvwprintw(win, currentLine++, 1, "[?] What is the name of the course? ");
        echo();
        wgetnstr(win, buffer, 100);
        newCourse.setName(string(buffer));

        mvwprintw(win, currentLine++, 1, "[?] How many ECTS does the course give? ");
        echo();
        wgetnstr(win, buffer, 100);
        newCourse.setNoEcts(stringToInt(buffer));

        mvwprintw(win, currentLine++, 1, "[?] In which semester is the course teached (1-8)? ");
        echo();
        wgetnstr(win, buffer, 100);
        newCourse.setSemester(Semester(stringToInt(buffer)));

        mvwprintw(win, currentLine++, 1, "[?] Is the course necessary to pass (1|true or 0|false)? ");
        echo();
        wgetnstr(win, buffer, 100);
        newCourse.setIsNecessary(stringToBool(buffer));

        // Check if the course already exists
        for (auto course : courses)
        {
            if (course.getCourseId() == newCourse.getCourseId())
            {
                mvwprintw(win, currentLine++, 1, "[!] Course with courseId: %s already exists.", newCourse.getCourseId().c_str());
                goto print_options;
            }
        }

        // Add to courses
        courses.push_back(newCourse);

        // Result
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "[+] Course with courseId: %s was created successfully.", newCourse.getCourseId().c_str());

    // Options
    print_options:
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "Press <enter> to create a new course.");
        mvwprintw(win, currentLine++, 1, "Move the arrows to select a new option.");
        mvwprintw(win, currentLine++, 1, "Press <q> to quit.");
        wrefresh(win);
    };
    void readCourse(WINDOW *win) {
        // Variables
        int currentLine = 1;
        char buffer[100];

        bool courseExists = false;
        string courseIdToRead;
        Course courseToRead;

        // Input
        mvwprintw(win, currentLine++, 1, "Complete the following questions to get the details of an existing course.");
        mvwprintw(win, currentLine++, 1, "[?] What is the ID of the course? ");
        echo();
        wgetnstr(win, buffer, 100);
        courseIdToRead = string(buffer);

        // Validation
        // 1. Check if course already exists
        for (auto course : courses)
        {
            if (course.getCourseId() == courseIdToRead)
            {
                courseExists = true;
                courseToRead = course;
            }
        }
        if (!courseExists)
        {
            mvwprintw(win, currentLine++, 1, "[!] Course with courseId: %s does not exist.", courseIdToRead.c_str());
            goto print_options;
        }

        // Result
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "[+] c.courseId: %s", courseToRead.getCourseId().c_str());
        mvwprintw(win, currentLine++, 1, "[+] c.name: %s", courseToRead.getName().c_str());
        mvwprintw(win, currentLine++, 1, "[+] c.noEcts: %i", courseToRead.getNoEcts());
        mvwprintw(win, currentLine++, 1, "[+] c.semester: %i", courseToRead.getSemester());
        mvwprintw(win, currentLine++, 1, "[+] c.isNecessary: %s", courseToRead.getIsNecessary() ? "true" : "false");

    // Options
    print_options:
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "Press <enter> to get the details of another course.");
        mvwprintw(win, currentLine++, 1, "Move the arrows to select a new option.");
        mvwprintw(win, currentLine++, 1, "Press <q> to quit.");
        wrefresh(win);
    };
    void updateCourse(WINDOW *win) {
        // Variables
        int currentLine = 1;
        char buffer[100];
        bool e = false;
        Course* courseToUpdate;

        // Input
        mvwprintw(win, currentLine++, 1, "Complete the following questions to update an existing course.");
        mvwprintw(win, currentLine++, 1, "[?] What is the ID of the course? ");
        echo();
        wgetnstr(win, buffer, 100);

        // Check if you exists
        for (auto &course : courses)
        {
            if (course.getCourseId() == string(buffer))
            {
                e = true;
                courseToUpdate = &course;
            }
        }
        if (!e)
        {
            mvwprintw(win, currentLine++, 1, "[!] Course with courseId: %s does not exist.", buffer);
            goto print_options;
        }

        mvwprintw(win, currentLine++, 1, "[?] What is the name of the course? ");
        echo();
        wgetnstr(win, buffer, 100);
        (*courseToUpdate).setName(string(buffer));

        mvwprintw(win, currentLine++, 1, "[?] How many ECTS does the course give? ");
        echo();
        wgetnstr(win, buffer, 100);
        (*courseToUpdate).setNoEcts(stringToInt(buffer));

        mvwprintw(win, currentLine++, 1, "[?] In which semester is the course teached (1-8)? ");
        echo();
        wgetnstr(win, buffer, 100);
        (*courseToUpdate).setSemester(Semester(stringToInt(buffer)));

        mvwprintw(win, currentLine++, 1, "[?] Is the course necessary to pass (1|true or 0|false)? ");
        echo();
        wgetnstr(win, buffer, 100);
        (*courseToUpdate).setIsNecessary(stringToBool(buffer));

        // Results
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "[+] Course with courseId: %s was updated successfully.", (*courseToUpdate).getCourseId().c_str());

    // Options
    print_options:
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "Press <enter> to update another course.");
        mvwprintw(win, currentLine++, 1, "Move the arrows to select a new option.");
        mvwprintw(win, currentLine++, 1, "Press <q> to quit.");
        wrefresh(win);
    };
    void deleteCourse(WINDOW *win) {
        // Variables
        int currentLine = 1;
        char buffer[100];
        bool courseExists = false;
        string courseIdToDelete;

        // Input
        mvwprintw(win, currentLine++, 1, "Complete the following questions to delete an existing course.");
        mvwprintw(win, currentLine++, 1, "[?] What is the ID of the course? ");
        echo();
        wgetnstr(win, buffer, 100);
        courseIdToDelete = string(buffer);

        // Validation
        // 1. Check if course already exists
        for (auto course : courses)
        {
            if (course.getCourseId() == courseIdToDelete)
            {
                courseExists = true;
            }
        }
        if (!courseExists)
        {
            mvwprintw(win, currentLine++, 1, "[!] Course with courseId: %s does not exist.", courseIdToDelete.c_str());
            goto print_options;
        }

        // Remove
        courses.erase(std::remove_if(courses.begin(), courses.end(),
                                     [courseIdToDelete](const Course &c)
                                     { return c.getCourseId() == courseIdToDelete; }),
                      courses.end());

        // Results
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "[+] Course with courseId: %s was removed successfully.", courseIdToDelete.c_str());

    // Options
    print_options:
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "Press <enter> to remove another course.");
        mvwprintw(win, currentLine++, 1, "Move the arrows to select a new option.");
        mvwprintw(win, currentLine++, 1, "Press <q> to quit.");
        wrefresh(win);
    };
    void listCourses(WINDOW *win) {
        // Variables
        int currentLine = 1;
        char buffer[100];

        // Results
        mvwprintw(win, currentLine++, 1, "%15s %35s %8s %10s %13s %25s %25s", 
            "CourseId", 
            "Name", 
            "NoECTS", 
            "Semester", 
            "IsNecessary?", 
            "ProfessorIds",
            "StudentIds");
        for (auto course : courses)
        {
            mvwprintw(win, currentLine++, 1, "%15s %35s %8d %10d %13s %25s %25s", 
                course.getCourseId().c_str(), 
                course.getName().c_str(),
                course.getNoEcts(),
                course.getSemester(),
                (course.getIsNecessary() ? "true" : "false"),
                concatenateVector(course.getProfessorsIds()).c_str(),
                concatenateVector(course.getStudentsIds()).c_str());
        }

    // Options
    print_options:
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "Move the arrows to select a new option.");
        mvwprintw(win, currentLine++, 1, "Press <q> to quit.");
        wrefresh(win);
    };
    void assignProfessor(WINDOW *win) {
        // Variables
        int currentLine = 1;
        char buffer[100];
        bool exists = false;
        string professorId;
        Course courseToUpdate;

        mvwprintw(win, currentLine++, 1, "Complete the following questions to assign a professor to an existing course.");
        
        mvwprintw(win, currentLine++, 1, "[?] What is the ID of the professor? ");
        echo();
        wgetnstr(win, buffer, 100);
        professorId = string(buffer);

        // Check if the professor exists
        for (auto professor : professors)
        {
            if (professor.getIdentityID() == professorId)
                exists = true;
            
        }
        if (!exists)
        {
            mvwprintw(win, currentLine++, 1, "[!] Professor with identityID: %s does not exist.", buffer);
            goto print_options;
        }

        // Input CourseId
        mvwprintw(win, currentLine++, 1, "[?] What is the ID of the course? ");
        echo();
        wgetnstr(win, buffer, 100);

        // Check if the course exists
        exists = false;
        for (auto &course : courses)
        {
            if (course.getCourseId() == string(buffer))
            {
                exists = true;
                course.addProfessorId(professorId);
            }
        }
        if (!exists)
        {
            mvwprintw(win, currentLine++, 1, "[!] Course with courseId: %s does not exist.", buffer);
            goto print_options;
        }
  
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "[+] Course with courseId: %s was updated successfully.", courseToUpdate.getCourseId().c_str());

    // Options
    print_options:
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "Press <enter> to assign a professor to a course.");
        mvwprintw(win, currentLine++, 1, "Move the arrows to select a new option.");
        mvwprintw(win, currentLine++, 1, "Press <q> to quit.");
        wrefresh(win);
    }
    void registerStudent(WINDOW *win) {
        // Variables
        int currentLine = 1;
        char buffer[100];
        bool exists = false;
        string studentId;
        Course courseToUpdate;

        mvwprintw(win, currentLine++, 1, "Complete the following questions to register a student to an existing course.");
        
        mvwprintw(win, currentLine++, 1, "[?] What is the ID of the student? ");
        echo();
        wgetnstr(win, buffer, 100);
        studentId = string(buffer);

        // Check if the professor exists
        for (auto student : students)
        {
            if (student.getIdentityID() == studentId)
                exists = true;
            
        }
        if (!exists)
        {
            mvwprintw(win, currentLine++, 1, "[!] Student with identityID: %s does not exist.", buffer);
            goto print_options;
        }

        // Input CourseId
        mvwprintw(win, currentLine++, 1, "[?] What is the ID of the course? ");
        echo();
        wgetnstr(win, buffer, 100);

        // Check if the course exists
        exists = false;
        for (auto &course : courses)
        {
            if (course.getCourseId() == string(buffer))
            {
                exists = true;
                course.addStudentId(studentId);
            }
        }
        if (!exists)
        {
            mvwprintw(win, currentLine++, 1, "[!] Course with courseId: %s does not exist.", buffer);
            goto print_options;
        }
  
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "[+] Course with courseId: %s was updated successfully.", courseToUpdate.getCourseId().c_str());

    // Options
    print_options:
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "Press <enter> to register another student to a course.");
        mvwprintw(win, currentLine++, 1, "Move the arrows to select a new option.");
        mvwprintw(win, currentLine++, 1, "Press <q> to quit.");
        wrefresh(win);
    }
    void saveCourses() {
        ofstream file(COURSES_CSV_FILE);

        if (file.is_open())
        {
            for (const auto course : courses)
            {
                file << course.toCSVString() << endl;
            }

            file.close();
        }
        else
        {
            cerr << "Unable to open file" << endl;
        }
    }
    void loadCourses() {
        ifstream file(COURSES_CSV_FILE);
        string line;

        if (file.is_open())
        {
            while (getline(file, line))
            {
                courses.push_back(Course::fromCSVLine(line));
            }
            file.close();
        }
        else
        {
            cerr << "Unable to open file" << endl;
        }
    }

    // Professors
    void createProfessor(WINDOW *win) {
        // Variables
        int currentLine = 1;
        char buffer[100];
        Professor newProfessor;

        // Input
        mvwprintw(win, currentLine++, 1, "Complete the following questions to create a new professor.");
        mvwprintw(win, currentLine++, 1, "[?] What is the ID of the professor? ");
        echo();
        wgetnstr(win, buffer, 100);
        newProfessor.setIdentityID(string(buffer));

        mvwprintw(win, currentLine++, 1, "[?] What is the first name of the professor? ");
        echo();
        wgetnstr(win, buffer, 100);
        newProfessor.setFirstName(string(buffer));

        mvwprintw(win, currentLine++, 1, "[?] What is the last name of the professor? ");
        echo();
        wgetnstr(win, buffer, 100);
        newProfessor.setLastName(string(buffer));

        mvwprintw(win, currentLine++, 1, "[?] When is the birthday of the professor (dd/mm/yyyy)? ");
        echo();
        wgetnstr(win, buffer, 100);
        newProfessor.setBirthDate(string(buffer));

        mvwprintw(win, currentLine++, 1, "[?] What is the field of the professor? ");
        echo();
        wgetnstr(win, buffer, 100);
        newProfessor.setField(string(buffer));

        // Validation
        // 1. Check if professor already exists
        for (auto professor : professors)
        {
            if (professor.getIdentityID() == newProfessor.getIdentityID())
            {
                mvwprintw(win, currentLine++, 1, "[!] Professor with identityID: %s already exists.", newProfessor.getIdentityID().c_str());
                goto print_options;
            }
        }

        // Add to courses
        professors.push_back(newProfessor);

        // Result
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "[+] Professor with identityID: %s was created successfully.", newProfessor.getIdentityID().c_str());

    // Options
    print_options:
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "Press <enter> to create a new professor.");
        mvwprintw(win, currentLine++, 1, "Move the arrows to select a new option.");
        mvwprintw(win, currentLine++, 1, "Press <q> to quit.");
        wrefresh(win);
    };
    void readProfessor(WINDOW *win) {
        // Variables
        int currentLine = 1;
        char buffer[100];
        bool professorExists = false;
        Professor professorToRead;
        string professorIdToRead;

        // Input
        mvwprintw(win, currentLine++, 1, "Complete the following questions to get the details of an existing professor.");
        mvwprintw(win, currentLine++, 1, "[?] What is the ID of the professor? ");
        echo();
        wgetnstr(win, buffer, 100);
        professorIdToRead = string(buffer);

        // Validation
        // 1. Check if professor exists
        for (auto professor : professors)
        {
            if (professor.getIdentityID() == professorIdToRead)
            {
                professorExists = true;
                professorToRead = professor;
            }
        }
        if (!professorExists)
        {
            mvwprintw(win, currentLine++, 1, "[!] Professor with IdentityID: %s does not exist.", professorIdToRead.c_str());
            goto print_options;
        }

        // Result
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "[+] p.identityID: %s", professorToRead.getIdentityID().c_str());
        mvwprintw(win, currentLine++, 1, "[+] p.firstName: %s", professorToRead.getFirstName().c_str());
        mvwprintw(win, currentLine++, 1, "[+] p.lastName: %s", professorToRead.getLastName().c_str());
        mvwprintw(win, currentLine++, 1, "[+] p.Birthday: %s", professorToRead.getBirthDate().c_str());
        mvwprintw(win, currentLine++, 1, "[+] p.Field: %s", professorToRead.getField().c_str());

    // Options
    print_options:
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "Press <enter> to get the details of another professor.");
        mvwprintw(win, currentLine++, 1, "Move the arrows to select a new option.");
        mvwprintw(win, currentLine++, 1, "Press <q> to quit.");
        wrefresh(win);
    };
    void updateProfessor(WINDOW *win) {
        // Variables
        int currentLine = 1;
        char buffer[100];
        bool e = false;
        Professor *professorToUpdate;

        // Input
        mvwprintw(win, currentLine++, 1, "Complete the following questions to update an existing professor.");
        mvwprintw(win, currentLine++, 1, "[?] What is the ID of the professor? ");
        echo();
        wgetnstr(win, buffer, 100);

        // Validation
        // 1. If the course does not exist, then print options.
        for (auto &professor : professors)
        {
            if (professor.getIdentityID() == string(buffer))
            {
                e = true;
                professorToUpdate = &professor;
            }
        }
        if (!e)
        {
            mvwprintw(win, currentLine++, 1, "[!] Professor with identityID: %s does not exist.", buffer);
            goto print_options;
        }

        mvwprintw(win, currentLine++, 1, "[?] What is the first name of the professor? ");
        echo();
        wgetnstr(win, buffer, 100);
        (*professorToUpdate).setFirstName(string(buffer));

        mvwprintw(win, currentLine++, 1, "[?] What is the last name of the professor? ");
        echo();
        wgetnstr(win, buffer, 100);
        (*professorToUpdate).setLastName(string(buffer));

        mvwprintw(win, currentLine++, 1, "[?] When is the birthday of the professor (dd/mm/yyyy)? ");
        echo();
        wgetnstr(win, buffer, 100);
        (*professorToUpdate).setBirthDate(string(buffer));

        mvwprintw(win, currentLine++, 1, "[?] What is the field of the professor? ");
        echo();
        wgetnstr(win, buffer, 100);
        (*professorToUpdate).setField(string(buffer));

        // Results
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "[+] Professor with identityID: %s was updated successfully.", (*professorToUpdate).getIdentityID().c_str());

    // Options
    print_options:
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "Press <enter> to update another professor.");
        mvwprintw(win, currentLine++, 1, "Move the arrows to select a new option.");
        mvwprintw(win, currentLine++, 1, "Press <q> to quit.");
        wrefresh(win);
    };
    void deleteProfessor(WINDOW *win) {
        // Variables
        int currentLine = 1;
        char buffer[100];
        bool professorExists = false;
        string professorIdToDelete;

        // Input
        mvwprintw(win, currentLine++, 1, "Complete the following questions to delete an existing professor.");
        mvwprintw(win, currentLine++, 1, "[?] What is the ID of the professor? ");
        echo();
        wgetnstr(win, buffer, 100);
        professorIdToDelete = string(buffer);

        // Validation
        // 1. Check if professor exists
        for (auto professor : professors)
        {
            if (professor.getIdentityID() == professorIdToDelete)
            {
                professorExists = true;
            }
        }
        if (!professorExists)
        {
            mvwprintw(win, currentLine++, 1, "[!] Professor with identityID: %s does not exist.", professorIdToDelete.c_str());
            goto print_options;
        }

        // Remove
        professors.erase(std::remove_if(professors.begin(), professors.end(),
                                        [professorIdToDelete](const Professor &p)
                                        { return p.getIdentityID() == professorIdToDelete; }),
                         professors.end());

        // Results
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "[+] Professor with identityID: %s was removed successfully.", professorIdToDelete.c_str());

    // Options
    print_options:
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "Press <enter> to remove another professor.");
        mvwprintw(win, currentLine++, 1, "Move the arrows to select a new option.");
        mvwprintw(win, currentLine++, 1, "Press <q> to quit.");
        wrefresh(win);
    };
    void listProfessors(WINDOW *win) {
        // Variables
        int currentLine = 1;
        char buffer[100];

        // Results
        mvwprintw(win, currentLine++, 1, "Id FirstName LastName");
        mvwprintw(win, currentLine++, 1, "=====================");
        for (auto professor : professors)
        {
            mvwprintw(win, currentLine++, 1, "%s %s %s", professor.getIdentityID().c_str(), professor.getFirstName().c_str(), professor.getLastName().c_str());
        }

    // Options
    print_options:
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "Move the arrows to select a new option.");
        mvwprintw(win, currentLine++, 1, "Press <q> to quit.");
        wrefresh(win);
    };
    void saveProfessors() {
        ofstream file(PROFESSORS_CSV_FILE);

        if (file.is_open())
        {
            for (const auto professor : professors)
            {
                file << professor.toCSVString() << endl;
            }

            file.close();
        }
        else
        {
            cerr << "Unable to open file" << endl;
        }
    }
    void loadProfessors() {
        ifstream file(PROFESSORS_CSV_FILE);
        string line;

        if (file.is_open())
        {
            while (getline(file, line))
            {
                professors.push_back(Professor::fromCSVLine(line));
            }
            file.close();
        }
        else
        {
            cerr << "Unable to open file" << endl;
        }
    }

    // Students
    void createStudent(WINDOW *win) {
        // Variables
        int currentLine = 1;
        char buffer[100];
        Student newStudent;

        // Input
        mvwprintw(win, currentLine++, 1, "Complete the following questions to create a new student.");
        mvwprintw(win, currentLine++, 1, "[?] What is the ID of the student? ");
        echo();
        wgetnstr(win, buffer, 100);
        newStudent.setIdentityID(string(buffer));

        mvwprintw(win, currentLine++, 1, "[?] What is the first name of the student? ");
        echo();
        wgetnstr(win, buffer, 100);
        newStudent.setFirstName(string(buffer));

        mvwprintw(win, currentLine++, 1, "[?] What is the last name of the student? ");
        echo();
        wgetnstr(win, buffer, 100);
        newStudent.setLastName(string(buffer));

        mvwprintw(win, currentLine++, 1, "[?] When is the birthday of the student (dd/mm/yyyy)? ");
        echo();
        wgetnstr(win, buffer, 100);
        newStudent.setBirthDate(string(buffer));

        mvwprintw(win, currentLine++, 1, "[?] Which is the current semester of the student? ");
        echo();
        wgetnstr(win, buffer, 100);
        newStudent.setCurrentSemester(Semester(stringToInt(buffer)));

        // Validation
        // 1. Check if professor already exists
        for (auto student : students)
        {
            if (student.getIdentityID() == newStudent.getIdentityID())
            {
                mvwprintw(win, currentLine++, 1, "[!] Student with identityID: %s already exists.", newStudent.getIdentityID().c_str());
                goto print_options;
            }
        }

        // Add to courses
        students.push_back(newStudent);

        // Result
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "[+] Student with identityID: %s was created successfully.", newStudent.getIdentityID().c_str());

    // Options
    print_options:
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "Press <enter> to create a new student.");
        mvwprintw(win, currentLine++, 1, "Move the arrows to select a new option.");
        mvwprintw(win, currentLine++, 1, "Press <q> to quit.");
        wrefresh(win);
    };
    void readStudent(WINDOW *win) {
        // Variables
        int currentLine = 1;
        char buffer[100];
        bool studentExists = false;
        Student studentToRead;
        string studentIdToRead;

        // Input
        mvwprintw(win, currentLine++, 1, "Complete the following questions to get the details of an existing student.");
        mvwprintw(win, currentLine++, 1, "[?] What is the ID of the student? ");
        echo();
        wgetnstr(win, buffer, 100);
        studentIdToRead = string(buffer);

        // Validation
        // 1. Check if student exists
        for (auto student : students)
        {
            if (student.getIdentityID() == studentIdToRead)
            {
                studentExists = true;
                studentToRead = student;
            }
        }
        if (!studentExists)
        {
            mvwprintw(win, currentLine++, 1, "[!] Student with IdentityID: %s does not exist.", studentIdToRead.c_str());
            goto print_options;
        }

        // Result
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "[+] p.identityID: %s", studentToRead.getIdentityID().c_str());
        mvwprintw(win, currentLine++, 1, "[+] p.firstName: %s", studentToRead.getFirstName().c_str());
        mvwprintw(win, currentLine++, 1, "[+] p.lastName: %s", studentToRead.getLastName().c_str());
        mvwprintw(win, currentLine++, 1, "[+] p.Birthday: %s", studentToRead.getBirthDate().c_str());

    // Options
    print_options:
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "Press <enter> to get the details of another student.");
        mvwprintw(win, currentLine++, 1, "Move the arrows to select a new option.");
        mvwprintw(win, currentLine++, 1, "Press <q> to quit.");
        wrefresh(win);
    };
    void updateStudent(WINDOW *win) {
        // Variables
        int currentLine = 1;
        char buffer[100];
        bool e = false;
        Student *studentToUpdate;

        // Input
        mvwprintw(win, currentLine++, 1, "Complete the following questions to update an existing student.");
        mvwprintw(win, currentLine++, 1, "[?] What is the ID of the student? ");
        echo();
        wgetnstr(win, buffer, 100);

        // Validation
        // 1. If the course does not exist, then print options.
        for (auto &student : students)
        {
            if (student.getIdentityID() == string(buffer))
            {
                e = true;
                studentToUpdate = &student;
            }
        }
        if (!e)
        {
            mvwprintw(win, currentLine++, 1, "[!] Student with identityID: %s does not exist.", buffer);
            goto print_options;
        }

        mvwprintw(win, currentLine++, 1, "[?] What is the first name of the student? ");
        echo();
        wgetnstr(win, buffer, 100);
        (*studentToUpdate).setFirstName(string(buffer));

        mvwprintw(win, currentLine++, 1, "[?] What is the last name of the student? ");
        echo();
        wgetnstr(win, buffer, 100);
        (*studentToUpdate).setLastName(string(buffer));

        mvwprintw(win, currentLine++, 1, "[?] When is the birthday of the student (dd/mm/yyyy)? ");
        echo();
        wgetnstr(win, buffer, 100);
        (*studentToUpdate).setBirthDate(string(buffer));

        mvwprintw(win, currentLine++, 1, "[?] Which is the current semester of the student? ");
        echo();
        wgetnstr(win, buffer, 100);
        (*studentToUpdate).setCurrentSemester(Semester(stringToInt(buffer)));

        // Results
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "[+] Student with identityID: %s was updated successfully.", (*studentToUpdate).getIdentityID().c_str());

    // Options
    print_options:
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "Press <enter> to update another student.");
        mvwprintw(win, currentLine++, 1, "Move the arrows to select a new option.");
        mvwprintw(win, currentLine++, 1, "Press <q> to quit.");
        wrefresh(win);
    };
    void deleteStudent(WINDOW *win) {
        // Variables
        int currentLine = 1;
        char buffer[100];
        bool studentExists = false;
        string studentIdToDelete;

        // Input
        mvwprintw(win, currentLine++, 1, "Complete the following questions to delete an existing student.");
        mvwprintw(win, currentLine++, 1, "[?] What is the ID of the student? ");
        echo();
        wgetnstr(win, buffer, 100);
        studentIdToDelete = string(buffer);

        // Validation
        // 1. Check if student exists
        for (auto student : students)
        {
            if (student.getIdentityID() == studentIdToDelete)
            {
                studentExists = true;
            }
        }
        if (!studentExists)
        {
            mvwprintw(win, currentLine++, 1, "[!] Student with identityID: %s does not exist.", studentIdToDelete.c_str());
            goto print_options;
        }

        // Remove
        students.erase(std::remove_if(students.begin(), students.end(),
                                        [studentIdToDelete](const Student &s)
                                        { return s.getIdentityID() == studentIdToDelete; }),
                         students.end());

        // Results
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "[+] Student with identityID: %s was removed successfully.", studentIdToDelete.c_str());

    // Options
    print_options:
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "Press <enter> to remove another student.");
        mvwprintw(win, currentLine++, 1, "Move the arrows to select a new option.");
        mvwprintw(win, currentLine++, 1, "Press <q> to quit.");
        wrefresh(win);
    };
    void listStudents(WINDOW *win) {
        // Variables
        int currentLine = 1;
        char buffer[100];

        // Results
        mvwprintw(win, currentLine++, 1, "%15s %15s %15s %15s %15s %25s", 
            "IdentityID", 
            "FirstName", 
            "LastName", 
            "Birthday", 
            "Semester",
            "PassedCoursesIds");
        for (auto student : students)
        {
            mvwprintw(win, currentLine++, 1, "%15s %15s %15s %15s %15d %25s", 
                student.getIdentityID().c_str(), 
                student.getFirstName().c_str(), 
                student.getLastName().c_str(), 
                student.getBirthDate().c_str(),
                student.getCurrentSemester(),
                concatenateVector(student.getHasPassed()).c_str());
        }

    // Options
    print_options:
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "Move the arrows to select a new option.");
        mvwprintw(win, currentLine++, 1, "Press <q> to quit.");
        wrefresh(win);
    };
    void passCourse(WINDOW *win) {
        // Variables
        int currentLine = 1;
        char buffer[100];
        bool exists = false;
        string courseId;
        Student *studentToUpdate;

        mvwprintw(win, currentLine++, 1, "Complete the following questions to pass a course to an existing student.");
        
        mvwprintw(win, currentLine++, 1, "[?] What is the ID of the student? ");
        echo();
        wgetnstr(win, buffer, 100);
        string studentId = string(buffer);

        // Check if the student exists
        for (auto &student : students)
        {
            if (student.getIdentityID() == studentId) {
                exists = true;
                studentToUpdate = &student;
            }
            
        }
        if (!exists)
        {
            mvwprintw(win, currentLine++, 1, "[!] Student with identityID: %s does not exist.", buffer);
            goto print_options;
        }

        // Input CourseId
        mvwprintw(win, currentLine++, 1, "[?] What is the ID of the course? ");
        echo();
        wgetnstr(win, buffer, 100);

        // Check if the course exists
        exists = false;
        for (auto course : courses)
        {
            if (course.getCourseId() == string(buffer))
            {
                exists = true;
                courseId = string(buffer);
            }
        }
        if (!exists)
        {
            mvwprintw(win, currentLine++, 1, "[!] Course with courseId: %s does not exist.", buffer);
            goto print_options;
        }

        (*studentToUpdate).addPassedCourse(courseId);

        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "[+] Student with identityID: %s was updated successfully.", studentToUpdate->getIdentityID().c_str());

    // Options
    print_options:
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "Press <enter> to register another student to a course.");
        mvwprintw(win, currentLine++, 1, "Move the arrows to select a new option.");
        mvwprintw(win, currentLine++, 1, "Press <q> to quit.");
        wrefresh(win);
    }
    void saveStudents() {
        ofstream file(STUDENTS_CSV_FILE);

        if (file.is_open())
        {
            for (const auto student : students)
            {
                file << student.toCSVString() << endl;
            }

            file.close();
        }
        else
        {
            cerr << "Unable to open file" << endl;
        }
    }
    void loadStudents() {
        ifstream file(STUDENTS_CSV_FILE);
        string line;

        if (file.is_open())
        {
            while (getline(file, line))
            {
                students.push_back(Student::fromCSVLine(line));
            }
            file.close();
        }
        else
        {
            cerr << "Unable to open file" << endl;
        }
    }

    void saveAll() {
        saveCourses();
        saveProfessors();
        saveStudents();
    }
    void loadAll() {
        loadCourses();
        loadProfessors();
        loadStudents();
    }
};

#endif // SECRETARY_H
