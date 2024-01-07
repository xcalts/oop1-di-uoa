#ifndef SECRETARY_H
#define SECRETARY_H

#include <algorithm>
#include <curses.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "attendance.h"
#include "course.h"
#include "misc.h"
#include "professor.h"
#include "sixmonth.h"
#include "student.h"
#include "semester.h"

#define COURSES_CSV_FILE "./data/courses.csv"
#define PROFESSORS_CSV_FILE "./data/professors.csv"
#define STUDENTS_CSV_FILE "./data/students.csv"
#define SIXMONTHS_CSV_FILE "./data/sixmonths.csv"
#define ATTENDANCES_CSV_FILE "./data/attendances.csv"

using namespace std;

class Secretary
{
private:
    /* Fields */
    vector<Course> courses;
    vector<Professor> professors;
    vector<Student> students;
    vector<Sixmonth> sixmonths;
    vector<Attendance> attendances;

public:
    /* Constructors */
    Secretary() {}

    /* Deconstructors */
    ~Secretary() {}

    /* API */
    /* Courses */
    void createCourse(WINDOW *win) {
        // Variables
        int currentLine = 1;
        char buffer[100];
        Course newCourse;

        // Input ID
        mvwprintw(win, currentLine++, 1, "Complete the following questions to create a new course.");
        mvwprintw(win, currentLine++, 1, "[?] What is the ID of the course? ");
        echo();
        wgetnstr(win, buffer, 100);
        newCourse.setCourseId(string(buffer));

        // Check if a course with the same courseId already exists.
        for (auto course : courses)
        {
            if (course.getCourseId() == newCourse.getCourseId())
            {
                mvwprintw(win, currentLine++, 1, "[!] Course with courseId: %s already exists.", newCourse.getCourseId().c_str());
                goto exit;
            }
        }

        mvwprintw(win, currentLine++, 1, "[?] What is the name of the course? ");
        echo();
        wgetnstr(win, buffer, 100);
        newCourse.setName(string(buffer));

        // Check if a course with the same name already exists
        for (auto course : courses)
        {
            if (course.getName() == newCourse.getName())
            {
                mvwprintw(win, currentLine++, 1, "[!] Course with name: %s already exists.", newCourse.getName().c_str());
                goto exit;
            }
        }

        mvwprintw(win, currentLine++, 1, "[?] How many ECTS does the course give (1 - 10)? ");
        echo();
        wgetnstr(win, buffer, 100);
        newCourse.setNoEcts(stringToInt(buffer));

        // Check if the new course has valid noEcts value.
        if (newCourse.getNoEcts() > 10 || newCourse.getNoEcts() < 1)
        {
            mvwprintw(win, currentLine++, 1, "[!] The course's number of etcs must be inside [1,10].");
            goto exit;
        }

        mvwprintw(win, currentLine++, 1, "[?] In which semester is the course teached (1-8)? ");
        echo();
        wgetnstr(win, buffer, 100);
        newCourse.setSemester(Semester(stringToInt(buffer)));

        // Check if the new course has valid semester value.
        if (newCourse.getSemester() < 1 || newCourse.getSemester() > 8)
        {
            mvwprintw(win, currentLine++, 1, "[!] The course's semester must be inside [1,8].");
            goto exit;
        }

        mvwprintw(win, currentLine++, 1, "[?] Is the course necessary to pass (1|true or 0|false)? ");
        echo();
        wgetnstr(win, buffer, 100);
        newCourse.setIsNecessary(stringToBool(buffer));

        // Add to courses
        courses.push_back(newCourse);

        // Result
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "[+] Course with courseId: %s was created successfully.", newCourse.getCourseId().c_str());

        // Exit
        exit:
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

        // Check if a course with this courseId exists
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
            goto exit;
        }

        // Result
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "[+] c.courseId: %s", courseToRead.getCourseId().c_str());
        mvwprintw(win, currentLine++, 1, "[+] c.name: %s", courseToRead.getName().c_str());
        mvwprintw(win, currentLine++, 1, "[+] c.noEcts: %i", courseToRead.getNoEcts());
        mvwprintw(win, currentLine++, 1, "[+] c.semester: %i", courseToRead.getSemester());
        mvwprintw(win, currentLine++, 1, "[+] c.isNecessary: %s", courseToRead.getIsNecessary() ? "true" : "false");

    // Options
    exit:
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
        bool courseExists = false;
        Course changedCourse;
        Course* courseToUpdate;

        // Input courseId
        mvwprintw(win, currentLine++, 1, "Complete the following questions to update an existing course.");
        mvwprintw(win, currentLine++, 1, "[?] What is the ID of the course? ");
        echo();
        wgetnstr(win, buffer, 100);

        // Check if a course with this courseId exists
        for (auto &course : courses)
        {
            if (course.getCourseId() == string(buffer))
            {
                courseExists = true;
                courseToUpdate = &course;
            }
        }
        if (!courseExists)
        {
            mvwprintw(win, currentLine++, 1, "[!] Course with courseId: %s does not exist.", buffer);
            goto exit;
        }

        // Input name
        mvwprintw(win, currentLine++, 1, "[?] What is the name of the course? ");
        echo();
        wgetnstr(win, buffer, 100);
        changedCourse.setName(string(buffer));

        // Check if a course with the same name already exists
        for (auto course : courses)
        {
            if (course.getName() == changedCourse.getName())
            {
                mvwprintw(win, currentLine++, 1, "[!] Course with name: %s already exists.", changedCourse.getName().c_str());
                goto exit;
            }
        }

        // Input noEcts
        mvwprintw(win, currentLine++, 1, "[?] How many ECTS does the course give (1 - 10)? ");
        echo();
        wgetnstr(win, buffer, 100);
        changedCourse.setNoEcts(stringToInt(buffer));

        // Check if the new course has valid noEcts value
        if (changedCourse.getNoEcts() > 10 || changedCourse.getNoEcts() < 1)
        {
            mvwprintw(win, currentLine++, 1, "[!] The course's number of etcs must be inside [1,10].");
            goto exit;
        }

        // Input semester
        mvwprintw(win, currentLine++, 1, "[?] In which semester is the course teached (1-8)? ");
        echo();
        wgetnstr(win, buffer, 100);
        changedCourse.setSemester(Semester(stringToInt(buffer)));

        // Check if the new course has valid semester value
        if (changedCourse.getSemester() < 1 || changedCourse.getSemester() > 8)
        {
            mvwprintw(win, currentLine++, 1, "[!] The course's semester must be inside [1,8].");
            goto exit;
        }

        // Input isNecessary
        mvwprintw(win, currentLine++, 1, "[?] Is the course necessary to pass (1|true or 0|false)? ");
        echo();
        wgetnstr(win, buffer, 100);
        changedCourse.setIsNecessary(stringToBool(buffer));

        // Apply the changes
        (*courseToUpdate).setName(changedCourse.getName());
        (*courseToUpdate).setNoEcts(changedCourse.getNoEcts());
        (*courseToUpdate).setSemester(changedCourse.getSemester());
        (*courseToUpdate).setIsNecessary(changedCourse.getIsNecessary());

        // Results
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "[+] Course with courseId: %s was updated successfully.", (*courseToUpdate).getCourseId().c_str());

    // exit
    exit:
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

        // Check if the course exists
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
            goto exit;
        }

        // Delete it
        courses.erase(std::remove_if(courses.begin(), courses.end(),
                                     [courseIdToDelete](const Course &c)
                                     { return c.getCourseId() == courseIdToDelete; }),
                      courses.end());

        // Results
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "[+] Course with courseId: %s was removed successfully.", courseIdToDelete.c_str());

    // Options
    exit:
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
        mvwprintw(win, currentLine++, 1, "%15s %35s %8s %10s %13s", 
            "CourseId", 
            "Name", 
            "NoECTS", 
            "Semester", 
            "IsNecessary?");
        for (auto course : courses)
        {
            if(currentLine > 30) 
            {
                mvwprintw(win, currentLine++, 1, "See the courses.csv for more.");
                goto exit;
            }

            mvwprintw(win, currentLine++, 1, "%15s %35s %8d %10d %13s", 
                course.getCourseId().c_str(), 
                course.getName().c_str(),
                course.getNoEcts(),
                course.getSemester(),
                (course.getIsNecessary() ? "true" : "false"));
        }

    // Options
    exit:
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "Move the arrows to select a new option.");
        mvwprintw(win, currentLine++, 1, "Press <q> to quit.");
        wrefresh(win);
    };
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

    /* Professors */
    void createProfessor(WINDOW *win) {
        // Variables
        int currentLine = 1;
        char buffer[100];
        Professor newProfessor;

        // Input identityId
        mvwprintw(win, currentLine++, 1, "Complete the following questions to create a new professor.");
        mvwprintw(win, currentLine++, 1, "[?] What is the ID of the professor? ");
        echo();
        wgetnstr(win, buffer, 100);
        newProfessor.setIdentityID(string(buffer));

        // Check if a professor with the same identityId already exists.
        for (auto professor : professors)
        {
            if (professor.getIdentityID() == newProfessor.getIdentityID())
            {
                mvwprintw(win, currentLine++, 1, "[!] Professor with identityId: %s already exists.", newProfessor.getIdentityID().c_str());
                goto exit;
            }
        }

        // Input firstName
        mvwprintw(win, currentLine++, 1, "[?] What is the first name of the professor? ");
        echo();
        wgetnstr(win, buffer, 100);
        newProfessor.setFirstName(string(buffer));

        // Input lastName
        mvwprintw(win, currentLine++, 1, "[?] What is the last name of the professor? ");
        echo();
        wgetnstr(win, buffer, 100);
        newProfessor.setLastName(string(buffer));

        // Input birthday
        mvwprintw(win, currentLine++, 1, "[?] When is the birthday of the professor (dd/mm/yyyy)? ");
        echo();
        wgetnstr(win, buffer, 100);
        newProfessor.setBirthDate(string(buffer));
        
        // Check if birthday is of correct format
        if (!isValidDateFormat(newProfessor.getBirthDate()))
        {
            mvwprintw(win, currentLine++, 1, "[!] The birthday must be of format dd/mm/yyyy.");
            goto exit;
        }

        // Input field
        mvwprintw(win, currentLine++, 1, "[?] What is the field of the professor? ");
        echo();
        wgetnstr(win, buffer, 100);
        newProfessor.setField(string(buffer));

        // Add
        professors.push_back(newProfessor);

        // Result
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "[+] Professor with identityId: %s was created successfully.", newProfessor.getIdentityID().c_str());

    // Options
    exit:
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

        // Check if the professor exists
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
            goto exit;
        }

        // Print Results
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "[+] p.identityId: %s", professorToRead.getIdentityID().c_str());
        mvwprintw(win, currentLine++, 1, "[+] p.firstName: %s", professorToRead.getFirstName().c_str());
        mvwprintw(win, currentLine++, 1, "[+] p.lastName: %s", professorToRead.getLastName().c_str());
        mvwprintw(win, currentLine++, 1, "[+] p.Birthday: %s", professorToRead.getBirthDate().c_str());
        mvwprintw(win, currentLine++, 1, "[+] p.Field: %s", professorToRead.getField().c_str());

    // Options
    exit:
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
        bool professorExists = false;
        Professor changedProfessor;
        Professor *professorToUpdate;

        // Input identityId
        mvwprintw(win, currentLine++, 1, "Complete the following questions to create a new professor.");
        mvwprintw(win, currentLine++, 1, "[?] What is the ID of the professor? ");
        echo();
        wgetnstr(win, buffer, 100);
        changedProfessor.setIdentityID(string(buffer));

        // Check if the professor with this identityId exists
        for (auto professor : professors)
        {
            if (professor.getIdentityID() == changedProfessor.getIdentityID())
            {
                professorExists = true;
                goto exit;
            }
        }
        if(!professorExists) {
            mvwprintw(win, currentLine++, 1, "[!] Professor with identityId: %s does not exist.", changedProfessor.getIdentityID().c_str());
            goto exit;
        }

        // Input firstName
        mvwprintw(win, currentLine++, 1, "[?] What is the first name of the professor? ");
        echo();
        wgetnstr(win, buffer, 100);
        changedProfessor.setFirstName(string(buffer));

        // Input lastName
        mvwprintw(win, currentLine++, 1, "[?] What is the last name of the professor? ");
        echo();
        wgetnstr(win, buffer, 100);
        changedProfessor.setLastName(string(buffer));

        // Input birthday
        mvwprintw(win, currentLine++, 1, "[?] When is the birthday of the professor (dd/mm/yyyy)? ");
        echo();
        wgetnstr(win, buffer, 100);
        changedProfessor.setBirthDate(string(buffer));
        
        // Check if birthday is of correct format
        if (!isValidDateFormat(changedProfessor.getBirthDate()))
        {
            mvwprintw(win, currentLine++, 1, "[!] The birthday must be of format dd/mm/yyyy.");
            goto exit;
        }

        // Input field
        mvwprintw(win, currentLine++, 1, "[?] What is the field of the professor? ");
        echo();
        wgetnstr(win, buffer, 100);
        changedProfessor.setField(string(buffer));

        // Apply changes
        (*professorToUpdate).setFirstName(changedProfessor.getFirstName());
        (*professorToUpdate).setLastName(changedProfessor.getLastName());
        (*professorToUpdate).setBirthDate(changedProfessor.getBirthDate());
        (*professorToUpdate).setField(changedProfessor.getField());

        // Results
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "[+] Professor with identityId: %s was updated successfully.", (*professorToUpdate).getIdentityID().c_str());

    // Options
    exit:
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

        // Input identityId
        mvwprintw(win, currentLine++, 1, "Complete the following questions to delete an existing professor.");
        mvwprintw(win, currentLine++, 1, "[?] What is the ID of the professor? ");
        echo();
        wgetnstr(win, buffer, 100);
        professorIdToDelete = string(buffer);

        // Check if the professor with this identityId exists
        for (auto professor : professors)
        {
            if (professor.getIdentityID() == professorIdToDelete)
            {
                professorExists = true;
            }
        }
        if (!professorExists)
        {
            mvwprintw(win, currentLine++, 1, "[!] Professor with identityId: %s does not exist.", professorIdToDelete.c_str());
            goto exit;
        }

        // Remove
        professors.erase(std::remove_if(professors.begin(), professors.end(),
                                        [professorIdToDelete](const Professor &p)
                                        { return p.getIdentityID() == professorIdToDelete; }),
                         professors.end());

        // Results
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "[+] Professor with identityId: %s was removed successfully.", professorIdToDelete.c_str());

    // Options
    exit:
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

        // Print professors
        mvwprintw(win, currentLine++, 1, "%6s %15s %15s %10s %15s","Id", "FirstName", "LastName", "Birthday", "Field");
        for (auto professor : professors)
        {
            if(currentLine > 30) 
            {
                mvwprintw(win, currentLine++, 1, "See the professors.csv for more.");
                goto exit;
            }

            mvwprintw(win, currentLine++, 1, "%6s %15s %15s %10s %15s", 
                professor.getIdentityID().c_str(), 
                professor.getFirstName().c_str(), 
                professor.getLastName().c_str(),
                professor.getBirthDate().c_str(),
                professor.getField().c_str());
        }

    // Options
    exit:
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

    /* Students */
    void createStudent(WINDOW *win) {
        // Variables
        int currentLine = 1;
        char buffer[100];
        Student newStudent;

        // Input name
        mvwprintw(win, currentLine++, 1, "Complete the following questions to create a new student.");
        mvwprintw(win, currentLine++, 1, "[?] What is the ID of the student? ");
        echo();
        wgetnstr(win, buffer, 100);
        newStudent.setIdentityID(string(buffer));

        // Check if a student with the same id already exists
        for (auto student : students)
        {
            if (student.getIdentityID() == newStudent.getIdentityID())
            {
                mvwprintw(win, currentLine++, 1, "[!] Student with identityId: %s already exists.", newStudent.getIdentityID().c_str());
                goto exit;
            }
        }

        // Input firstName
        mvwprintw(win, currentLine++, 1, "[?] What is the first name of the student? ");
        echo();
        wgetnstr(win, buffer, 100);
        newStudent.setFirstName(string(buffer));

        // Input lastName
        mvwprintw(win, currentLine++, 1, "[?] What is the last name of the student? ");
        echo();
        wgetnstr(win, buffer, 100);
        newStudent.setLastName(string(buffer));

        // Input birthday
        mvwprintw(win, currentLine++, 1, "[?] When is the birthday of the student (dd/mm/yyyy)? ");
        echo();
        wgetnstr(win, buffer, 100);
        newStudent.setBirthDate(string(buffer));

        // Check if birthday is of correct format
        if (!isValidDateFormat(newStudent.getBirthDate()))
        {
            mvwprintw(win, currentLine++, 1, "[!] The birthday must be of format dd/mm/yyyy.");
            goto exit;
        }

        // Input semester
        mvwprintw(win, currentLine++, 1, "[?] Which is the current semester of the student? ");
        echo();
        wgetnstr(win, buffer, 100);
        newStudent.setCurrentSemester(Semester(stringToInt(buffer)));

        // Check if the new student has valid semester value.
        for (auto course : courses)
        {
            if (newStudent.getCurrentSemester() < 1 || newStudent.getCurrentSemester() > 8)
            {
                mvwprintw(win, currentLine++, 1, "[!] The student's semester must be inside [1,8].");
                goto exit;
            }
        }

        // Add to courses
        students.push_back(newStudent);

        // Result
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "[+] Student with identityId: %s was created successfully.", newStudent.getIdentityID().c_str());

    // Options
    exit:
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

        // Check if the student with this identityId exists
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
            goto exit;
        }

        // Print Results
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "[+] p.identityId: %s", studentToRead.getIdentityID().c_str());
        mvwprintw(win, currentLine++, 1, "[+] p.firstName: %s", studentToRead.getFirstName().c_str());
        mvwprintw(win, currentLine++, 1, "[+] p.lastName: %s", studentToRead.getLastName().c_str());
        mvwprintw(win, currentLine++, 1, "[+] p.Birthday: %s", studentToRead.getBirthDate().c_str());
        mvwprintw(win, currentLine++, 1, "[+] p.Semester: %d", studentToRead.getCurrentSemester());

    // Options
    exit:
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
        Student changedStudent;
        Student *studentToUpdate;

        // Input
        mvwprintw(win, currentLine++, 1, "Complete the following questions to update an existing student.");
        mvwprintw(win, currentLine++, 1, "[?] What is the ID of the student? ");
        echo();
        wgetnstr(win, buffer, 100);
        changedStudent.setIdentityID(string(buffer));

        // Check if the course exists
        for (auto &student : students)
        {
            if (student.getIdentityID() == changedStudent.getIdentityID())
            {
                e = true;
                studentToUpdate = &student;
            }
        }
        if (!e)
        {
            mvwprintw(win, currentLine++, 1, "[!] Student with identityId: %s does not exist.", changedStudent.getIdentityID().c_str());
            goto exit;
        }

        mvwprintw(win, currentLine++, 1, "[?] What is the first name of the student? ");
        echo();
        wgetnstr(win, buffer, 100);
        changedStudent.setFirstName(string(buffer));

        mvwprintw(win, currentLine++, 1, "[?] What is the last name of the student? ");
        echo();
        wgetnstr(win, buffer, 100);
        changedStudent.setLastName(string(buffer));

        mvwprintw(win, currentLine++, 1, "[?] When is the birthday of the student (dd/mm/yyyy)? ");
        echo();
        wgetnstr(win, buffer, 100);
        changedStudent.setBirthDate(string(buffer));

        // Check if birthday is of correct format
        if (!isValidDateFormat(changedStudent.getBirthDate()))
        {
            mvwprintw(win, currentLine++, 1, "[!] The birthday must be of format dd/mm/yyyy.");
            goto exit;
        }

        mvwprintw(win, currentLine++, 1, "[?] Which is the current semester of the student? ");
        echo();
        wgetnstr(win, buffer, 100);
        changedStudent.setCurrentSemester(Semester(stringToInt(buffer)));

        // Check if the semester is of correct format.
        for (auto course : courses)
        {
            if (changedStudent.getCurrentSemester() < 1 || changedStudent.getCurrentSemester() > 8)
            {
                mvwprintw(win, currentLine++, 1, "[!] The student's semester must be inside [1,8].");
                goto exit;
            }
        }

        // Apply changes
        (*studentToUpdate).setFirstName(changedStudent.getFirstName());
        (*studentToUpdate).setLastName(changedStudent.getLastName());
        (*studentToUpdate).setBirthDate(changedStudent.getBirthDate());
        (*studentToUpdate).setCurrentSemester(changedStudent.getCurrentSemester());

        // Results
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "[+] Student with identityId: %s was updated successfully.", (*studentToUpdate).getIdentityID().c_str());

    // Options
    exit:
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

        // Check if student with this identityId exists
        for (auto student : students)
        {
            if (student.getIdentityID() == studentIdToDelete)
            {
                studentExists = true;
            }
        }
        if (!studentExists)
        {
            mvwprintw(win, currentLine++, 1, "[!] Student with identityId: %s does not exist.", studentIdToDelete.c_str());
            goto exit;
        }

        // Delete
        students.erase(std::remove_if(students.begin(), students.end(),
                                        [studentIdToDelete](const Student &s)
                                        { return s.getIdentityID() == studentIdToDelete; }),
                         students.end());

        // Results
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "[+] Student with identityId: %s was removed successfully.", studentIdToDelete.c_str());

    // Options
    exit:
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
        mvwprintw(win, currentLine++, 1, "%15s %15s %15s %15s %15s", 
            "IdentityID", 
            "FirstName", 
            "LastName", 
            "Birthday", 
            "Semester");
        for (auto student : students)
        {
            if(currentLine > 30) 
            {
                mvwprintw(win, currentLine++, 1, "See the students.csv for more.");
                goto exit;
            }

            
            mvwprintw(win, currentLine++, 1, "%15s %15s %15s %15s %15d", 
                student.getIdentityID().c_str(), 
                student.getFirstName().c_str(), 
                student.getLastName().c_str(), 
                student.getBirthDate().c_str(),
                student.getCurrentSemester());
        }

    // Options
    exit:
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "Move the arrows to select a new option.");
        mvwprintw(win, currentLine++, 1, "Press <q> to quit.");
        wrefresh(win);
    };
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

    /* Sixmonths */
    void createSixmonth(WINDOW *win) {
        // Variables
        int currentLine = 1;
        char buffer[100];
        Sixmonth newSixmonth;

        // Ask for Input
        mvwprintw(win, currentLine++, 1, "Complete the following questions to create a new sixmonth.");
        mvwprintw(win, currentLine++, 1, "[?] What is the ID of the sixmonth? ");
        echo();
        wgetnstr(win, buffer, 100);
        newSixmonth.setSixmonthId(string(buffer));

        // Check if a sixmonth with the same sixmonthId already exists.
        for (auto sixmonth : sixmonths)
        {
            if (sixmonth.getSixmonthId() == newSixmonth.getSixmonthId())
            {
                mvwprintw(win, currentLine++, 1, "[!] Sixmonth with sixmonthId: %s already exists.", newSixmonth.getSixmonthId().c_str());
                goto exit;
            }
        }


        // Input year
        mvwprintw(win, currentLine++, 1, "[?] What is the year of the sixmonth? ");
        echo();
        wgetnstr(win, buffer, 100);
        newSixmonth.setYear(stringToInt(buffer));

        // Input isWinter
        mvwprintw(win, currentLine++, 1, "[?] Is it a winter sixmonth (1|true or 0|false)? ");
        echo();
        wgetnstr(win, buffer, 100);
        newSixmonth.setIsWinter(stringToBool(buffer));

        // Check if the same sixmonth already exists.
        for (auto sixmonth : sixmonths)
        {
            if (sixmonth.getYear() == newSixmonth.getYear() &&
                sixmonth.getIsWinter() == newSixmonth.getIsWinter())
            {
                mvwprintw(win, currentLine++, 1, "[!] A %s sixmonth at year %d already exists",
                    newSixmonth.getIsWinter() ? "winter" : "spring",
                    newSixmonth.getYear());
                goto exit;
            }
        }

        // Add
        sixmonths.push_back(newSixmonth);

        // Result
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "[+] [!] Sixmonth with sixmonthId: %s was created successfully.",
            newSixmonth.getSixmonthId().c_str());

        // Exit
        exit:
            mvwprintw(win, currentLine++, 1, " ");
            mvwprintw(win, currentLine++, 1, "Press <enter> to create a new sixmonth.");
            mvwprintw(win, currentLine++, 1, "Move the arrows to select a new option.");
            mvwprintw(win, currentLine++, 1, "Press <q> to quit.");
            wrefresh(win);
    };
    void readSixmonth(WINDOW *win) {
        // Variables
        int currentLine = 1;
        char buffer[100];
        bool sixmonthExists = false;
        string sixmonthId;
        Sixmonth sixmonthToRead;

        // Input year
        mvwprintw(win, currentLine++, 1, "Complete the following questions to get the details of an existing sixmonth.");
        mvwprintw(win, currentLine++, 1, "[?] What is the ID of the sixmonth? ");
        echo();
        wgetnstr(win, buffer, 100);
        sixmonthId = string(buffer);

        // Check if the specified sixmonth exists
        for (auto sixmonth : sixmonths)
        {
            if (sixmonth.getSixmonthId() == sixmonthId)
            {
                sixmonthExists = true;
                sixmonthToRead = sixmonth;
            }
        }
        if (!sixmonthExists)
        {
            mvwprintw(win, currentLine++, 1, "[!] A sixmonth with sixmonthId: %s does not exist.",
                sixmonthId.c_str());
            goto exit;
        }

        // Result
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "[+] s.sixmonthId: %s", sixmonthToRead.getSixmonthId().c_str());
        mvwprintw(win, currentLine++, 1, "[+] s.year: %d", sixmonthToRead.getYear());
        mvwprintw(win, currentLine++, 1, "[+] s.isWinter: %s", sixmonthToRead.getIsWinter() ? "Winter" : "Spring");

    // Options
    exit:
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "Press <enter> to get the details of another sixmonth.");
        mvwprintw(win, currentLine++, 1, "Move the arrows to select a new option.");
        mvwprintw(win, currentLine++, 1, "Press <q> to quit.");
        wrefresh(win);
    };
    void deleteSixmonth(WINDOW *win) {
        // Variables
        int currentLine = 1;
        char buffer[100];
        bool sixmonthExists = false;
        string sixmonthIdToDel;

        // Input ID
        mvwprintw(win, currentLine++, 1, "Complete the following questions to delete an existing sixmonth.");
        mvwprintw(win, currentLine++, 1, "[?] What is the ID of the sixmonth? ");
        echo();
        wgetnstr(win, buffer, 100);
        sixmonthIdToDel = string(buffer);

        // Check if the specified sixmonth exists
        for (auto sixmonth : sixmonths)
        {
            if (sixmonth.getSixmonthId() == sixmonthIdToDel)
                sixmonthExists = true;
        }
        if (!sixmonthExists)
        {
            mvwprintw(win, currentLine++, 1, "[!] A sixmonth with sixmonthId: %s does not exist.",
                sixmonthIdToDel.c_str());
            goto exit;
        }

        // Delete it
        sixmonths.erase(std::remove_if(sixmonths.begin(), sixmonths.end(),
                                     [sixmonthIdToDel](const Sixmonth &s)
                                     { return s.getSixmonthId() == sixmonthIdToDel; }),
                      sixmonths.end());

        // Results
        mvwprintw(win, currentLine++, 1, " ");
        
        mvwprintw(win, currentLine++, 1, "[+] Sixmonth with sixmonthId: %s was deleted successfully.",
            sixmonthIdToDel.c_str());

    // Options
    exit:
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "Press <enter> to remove another sixmonth.");
        mvwprintw(win, currentLine++, 1, "Move the arrows to select a new option.");
        mvwprintw(win, currentLine++, 1, "Press <q> to quit.");
        wrefresh(win);
    };
    void listSixmonths(WINDOW *win) {
        // Variables
        int currentLine = 1;
        char buffer[100];

        // Results
        mvwprintw(win, currentLine++, 1, "%10s %5s %12s", 
            "SixmonthId",
            "Year", 
            "IsWinter?");
        for (auto sixmonth : sixmonths)
        {
            if(currentLine > 30) 
            {
                mvwprintw(win, currentLine++, 1, "See the sixmonths.csv for more.");
                goto exit;
            }

            
            mvwprintw(win, currentLine++, 1, "%10s %5d %12s",
                sixmonth.getSixmonthId().c_str(),
                sixmonth.getYear(),
                (sixmonth.getIsWinter() ? "true" : "false"));
        }

    // Options
    exit:
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "Move the arrows to select a new option.");
        mvwprintw(win, currentLine++, 1, "Press <q> to quit.");
        wrefresh(win);
    };
    void saveSixmonths() {
        ofstream file(SIXMONTHS_CSV_FILE);

        if (file.is_open())
        {
            for (const auto sixmonth : sixmonths)
            {
                file << sixmonth.toCSVString() << endl;
            }

            file.close();
        }
        else
        {
            cerr << "Unable to open file" << endl;
        }
    }
    void loadSixmonths() {
        ifstream file(SIXMONTHS_CSV_FILE);
        string line;

        if (file.is_open())
        {
            while (getline(file, line))
            {
                sixmonths.push_back(Sixmonth::fromCSVLine(line));
            }
            file.close();
        }
        else
        {
            cerr << "Unable to open file" << endl;
        }
    }

    /* Attendances */
    void createAttendance(WINDOW *win) {
        // Variables
        int currentLine = 1;
        char buffer[100];
        bool attendanceExists = false;
        bool sixmonthExists = false;
        bool studentExists = false;
        bool courseExists = false;
        Student attendeeStudent;
        Course attendedCourse;
        Attendance newAttendace;

        // Input attendanceId
        mvwprintw(win, currentLine++, 1, "Complete the following questions to create a new attendance.");
        mvwprintw(win, currentLine++, 1, "[?] What is the ID of the attendance? ");
        echo();
        wgetnstr(win, buffer, 100);
        newAttendace.setAttendanceId(string(buffer));
        
        // Check if attendance with this attendanceId exists
        for (auto attendance : attendances)
        {
            if (attendance.getAttendanceId() == newAttendace.getAttendanceId())
                attendanceExists = true;
        }
        if (attendanceExists)
        {
            mvwprintw(win, currentLine++, 1, "[!] An attendance with attendanceId: %s already exists.",
                newAttendace.getAttendanceId().c_str());
            goto exit;
        }

        // Input sixmonthId
        mvwprintw(win, currentLine++, 1, "[?] What is the ID of the sixmonth? ");
        echo();
        wgetnstr(win, buffer, 100);
        newAttendace.setSixmonthId(string(buffer));

        // Check if sixmonth with this sixmonthId exists
        for (auto sixmonth : sixmonths)
        {
            if (sixmonth.getSixmonthId() == newAttendace.getSixmonthId())
                sixmonthExists = true;
        }
        if (!sixmonthExists)
        {
            mvwprintw(win, currentLine++, 1, "[!] A sixmonth with sixmonthId: %s does not exist.",
                newAttendace.getSixmonthId().c_str());
            goto exit;
        }

        // Input studentId
        mvwprintw(win, currentLine++, 1, "[?] What is the ID of the student? ");
        echo();
        wgetnstr(win, buffer, 100);
        newAttendace.setStudentId(string(buffer));

        // Check if student with this identityId exists
        for (auto student : students)
        {
            if (student.getIdentityID() == newAttendace.getStudentId()) {
                studentExists = true;
                attendeeStudent = student;
            }
        }
        if (!studentExists)
        {
            mvwprintw(win, currentLine++, 1, "[!] A student with identityId: %s does not exist.",
                newAttendace.getStudentId().c_str());
            goto exit;
        }

        // Input courseId
        mvwprintw(win, currentLine++, 1, "[?] What is the ID of the course? ");
        echo();
        wgetnstr(win, buffer, 100);
        newAttendace.setCourseId(string(buffer));

        // Check if course with this course exists
        for (auto course : courses)
        {
            if (course.getCourseId() == newAttendace.getCourseId()) {
                courseExists = true;
                attendedCourse = course;
            }
        }
        if (!courseExists)
        {
            mvwprintw(win, currentLine++, 1, "[!] A course with courseId: %s does not exist.",
                newAttendace.getCourseId().c_str());
            goto exit;
        }

        // Check if the student can attend the course.
        if(attendeeStudent.getCurrentSemester() < attendedCourse.getSemester())
        {
            mvwprintw(win, currentLine++, 1, "[!] A student of semester %d cannot attend a course of semestere %d.",
                attendeeStudent.getCurrentSemester(),
                attendedCourse.getSemester());
            goto exit;
        }

        // Input grade
        mvwprintw(win, currentLine++, 1, "[?] What is the grade (1-10)? ");
        echo();
        wgetnstr(win, buffer, 100);
        newAttendace.setGrade(stringToInt(buffer));

        // Check if the grade's value is valid
        if(newAttendace.getGrade() < 1 || newAttendace.getGrade() > 10)
        {
            mvwprintw(win, currentLine++, 1, "[!] Grade must take a value inside [1, 10].");
            goto exit;
        } 

        // Add
        attendances.push_back(newAttendace);

        // Result
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "[+] Attendance with attendanceId: %s was created successfully.",
            newAttendace.getAttendanceId().c_str());

        // Exit
        exit:
            mvwprintw(win, currentLine++, 1, " ");
            mvwprintw(win, currentLine++, 1, "Press <enter> to create a new attendance.");
            mvwprintw(win, currentLine++, 1, "Move the arrows to select a new option.");
            mvwprintw(win, currentLine++, 1, "Press <q> to quit.");
            wrefresh(win);
    };
    void readAttendance(WINDOW *win) {
        // Variables
        int currentLine = 1;
        char buffer[100];
        bool attendanceExists = false;
        string attendanceId;
        Attendance attendanceToRead;

        // Input attendanceId
        mvwprintw(win, currentLine++, 1, "Complete the following questions to get the details of an existing attendance.");
        mvwprintw(win, currentLine++, 1, "[?] What is the ID of the attendance? ");
        echo();
        wgetnstr(win, buffer, 100);
        attendanceId = string(buffer);

        // Check if the specified attendance exists
        for (auto attendance : attendances)
        {
            if (attendance.getAttendanceId() == attendanceId)
            {
                attendanceExists = true;
                attendanceToRead = attendance;
            }
        }
        if (!attendanceExists)
        {
            mvwprintw(win, currentLine++, 1, "[!] An attendance with attendanceId: %s does not exist.",
                attendanceId.c_str());
            goto exit;
        }

        // Result
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "[+] s.attendanceId: %s", attendanceToRead.getAttendanceId().c_str());
        mvwprintw(win, currentLine++, 1, "[+] s.sixmonthId: %s", attendanceToRead.getSixmonthId().c_str());
        mvwprintw(win, currentLine++, 1, "[+] s.studentId: %s", attendanceToRead.getStudentId().c_str());
        mvwprintw(win, currentLine++, 1, "[+] s.courseId: %s", attendanceToRead.getCourseId().c_str());
        mvwprintw(win, currentLine++, 1, "[+] s.grade: %d", attendanceToRead.getGrade());

    // Options
    exit:
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "Press <enter> to get the details of another attendance.");
        mvwprintw(win, currentLine++, 1, "Move the arrows to select a new option.");
        mvwprintw(win, currentLine++, 1, "Press <q> to quit.");
        wrefresh(win);
    };
    void updateAttendance(WINDOW *win) {
        // Variables
        int currentLine = 1;
        char buffer[100];
        bool attendanceExists = false;
        bool sixmonthExists = false;
        bool studentExists = false;
        bool courseExists = false;
        Student attendeeStudent;
        Course attendedCourse;
        Attendance changedAttendance;
        Attendance* attendanceToUpdate;

        // Input attendanceId
        mvwprintw(win, currentLine++, 1, "Complete the following questions to update an existing attendance.");
        mvwprintw(win, currentLine++, 1, "[?] What is the ID of the attendace? ");
        echo();
        wgetnstr(win, buffer, 100);

        // Check if an attendance with this attendanceId exists
        for (auto &attendance : attendances)
        {
            if (attendance.getAttendanceId() == string(buffer))
            {
                attendanceExists = true;
                attendanceToUpdate = &attendance;
            }
        }
        if (!attendanceExists)
        {
            mvwprintw(win, currentLine++, 1, "[!] Attendance with attendanceId: %s does not exist.", buffer);
            goto exit;
        }

        // Input sixmonthId
        mvwprintw(win, currentLine++, 1, "[?] What is the ID of the sixmonth? ");
        echo();
        wgetnstr(win, buffer, 100);
        changedAttendance.setSixmonthId(string(buffer));

        // Check if sixmonth with this sixmonthId exists
        for (auto sixmonth : sixmonths)
        {
            if (sixmonth.getSixmonthId() == changedAttendance.getSixmonthId())
                sixmonthExists = true;
        }
        if (!sixmonthExists)
        {
            mvwprintw(win, currentLine++, 1, "[!] A sixmonth with sixmonthId: %s does not exist.",
                changedAttendance.getSixmonthId().c_str());
            goto exit;
        }

        // Input studentId
        mvwprintw(win, currentLine++, 1, "[?] What is the ID of the student? ");
        echo();
        wgetnstr(win, buffer, 100);
        changedAttendance.setStudentId(string(buffer));

        // Check if student with this identityId exists
        for (auto student : students)
        {
            if (student.getIdentityID() == changedAttendance.getStudentId()) {
                studentExists = true;
                attendeeStudent = student;
            }
        }
        if (!studentExists)
        {
            mvwprintw(win, currentLine++, 1, "[!] A student with identityId: %s does not exist.",
                changedAttendance.getStudentId().c_str());
            goto exit;
        }

        // Input courseId
        mvwprintw(win, currentLine++, 1, "[?] What is the ID of the course? ");
        echo();
        wgetnstr(win, buffer, 100);
        changedAttendance.setCourseId(string(buffer));

        // Check if course with this course exists
        for (auto course : courses)
        {
            if (course.getCourseId() == changedAttendance.getCourseId()) {
                courseExists = true;
                attendedCourse = course;
            }
        }
        if (!courseExists)
        {
            mvwprintw(win, currentLine++, 1, "[!] A course with courseId: %s does not exist.",
                changedAttendance.getCourseId().c_str());
            goto exit;
        }

        // Input grade
        mvwprintw(win, currentLine++, 1, "[?] What is the grade (1-10)? ");
        echo();
        wgetnstr(win, buffer, 100);
        changedAttendance.setGrade(stringToInt(buffer));

        // Check if the grade's value is valid
        if(changedAttendance.getGrade() < 1 || changedAttendance.getGrade() > 10)
        {
            mvwprintw(win, currentLine++, 1, "[!] Grade must take a value inside [1, 10].");
            goto exit;
        } 

        // Check if the student can attend the course.
        if(attendeeStudent.getCurrentSemester() < attendedCourse.getSemester())
        {
            mvwprintw(win, currentLine++, 1, "[!] A student of semester %d cannot attend a course of semestere %d.",
                attendeeStudent.getCurrentSemester(),
                attendedCourse.getSemester());
            goto exit;
        }

        // Apply the changes
        (*attendanceToUpdate).setSixmonthId(changedAttendance.getSixmonthId());
        (*attendanceToUpdate).setStudentId(changedAttendance.getStudentId());
        (*attendanceToUpdate).setCourseId(changedAttendance.getCourseId());
        (*attendanceToUpdate).setGrade(changedAttendance.getGrade());

        // Results
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "[+] Attendance with attendanceId: %s was updated successfully.",
            (*attendanceToUpdate).getAttendanceId().c_str());

    // exit
    exit:
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "Press <enter> to update another course.");
        mvwprintw(win, currentLine++, 1, "Move the arrows to select a new option.");
        mvwprintw(win, currentLine++, 1, "Press <q> to quit.");
        wrefresh(win);
    };
    void deleteAttendance(WINDOW *win) {
        // Variables
        int currentLine = 1;
        char buffer[100];
        bool attendanceExists = false;
        string attendanceIdToDel;

        // Input ID
        mvwprintw(win, currentLine++, 1, "Complete the following questions to delete an attendance.");
        mvwprintw(win, currentLine++, 1, "[?] What is the ID of the attendance? ");
        echo();
        wgetnstr(win, buffer, 100);
        attendanceIdToDel = string(buffer);

        // Check if the specified sixmonth exists
        for (auto attendance : attendances)
        {
            if (attendance.getAttendanceId() == attendanceIdToDel)
                attendanceExists = true;
        }
        if (!attendanceExists)
        {
            mvwprintw(win, currentLine++, 1, "[!] A attendance with attendanceId: %s does not exist.",
                attendanceIdToDel.c_str());
            goto exit;
        }

        // Delete it
        attendances.erase(std::remove_if(attendances.begin(), attendances.end(),
                                     [attendanceIdToDel](const Attendance &s)
                                     { return s.getAttendanceId() == attendanceIdToDel; }),
                      attendances.end());

        // Results
        mvwprintw(win, currentLine++, 1, " ");
        
        mvwprintw(win, currentLine++, 1, "[+] Attendance with attendanceId: %s was deleted successfully.",
            attendanceIdToDel.c_str());

    // Options
    exit:
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "Press <enter> to remove another attendance.");
        mvwprintw(win, currentLine++, 1, "Move the arrows to select a new option.");
        mvwprintw(win, currentLine++, 1, "Press <q> to quit.");
        wrefresh(win);
    };
    void listAttendances(WINDOW *win) {
        // Variables
        int currentLine = 1;
        char buffer[100];

        // Results
        mvwprintw(win, currentLine++, 1, "%10s %10s %10s %10s %7s", 
            "AttendanceId",
            "SixmonthId",
            "StudentId",
            "CourseId",
            "Grade");
        for (auto attendance : attendances)
        {
            if(currentLine > 30) 
            {
                mvwprintw(win, currentLine++, 1, "See the attendances.csv for more.");
                goto exit;
            }

            
            mvwprintw(win, currentLine++, 1, "%10s %10s %10s %10s %7d",
                attendance.getAttendanceId().c_str(),
                attendance.getSixmonthId().c_str(),
                attendance.getStudentId().c_str(),
                attendance.getCourseId().c_str(),
                attendance.getGrade());
        }

    // Options
    exit:
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "Move the arrows to select a new option.");
        mvwprintw(win, currentLine++, 1, "Press <q> to quit.");
        wrefresh(win);
    };
    void saveAttendances() {
        ofstream file(ATTENDANCES_CSV_FILE);

        if (file.is_open())
        {
            for (const auto attendance : attendances)
            {
                file << attendance.toCSVString() << endl;
            }

            file.close();
        }
        else
        {
            cerr << "Unable to open file" << endl;
        }
    }
    void loadAttendances() {
        ifstream file(ATTENDANCES_CSV_FILE);
        string line;

        if (file.is_open())
        {
            while (getline(file, line))
            {
                attendances.push_back(Attendance::fromCSVLine(line));
            }
            file.close();
        }
        else
        {
            cerr << "Unable to open file" << endl;
        }
    }

    /* Misc */
    void printProfessorStats(WINDOW *win) {
        // Variables
        int currentLine = 1;
        char buffer[100];
        bool professorExists = false;
        bool sixmonthExists = false;
        Professor p;
        Sixmonth s;
        string professorIdToRead;
        int indx = 0;

        // Input professorId
        mvwprintw(win, currentLine++, 1, "Complete the following questions to get the statistics of an existing professor's.");
        mvwprintw(win, currentLine++, 1, "The statistics are for the courses that he/she teached in a specific sixmonth.");
        mvwprintw(win, currentLine++, 1, "[?] What is the ID of the professor? ");
        echo();
        wgetnstr(win, buffer, 100);

        // Check if the professor exists
        for (auto professor : professors)
        {
            if (professor.getIdentityID() == string(buffer))
            {
                professorExists = true;
                p = professor;
            }
        }
        if (!professorExists)
        {
            mvwprintw(win, currentLine++, 1, "[!] Professor with IdentityID: %s does not exist.", buffer);
            goto exit;
        }

        // Input sixmonthId
        mvwprintw(win, currentLine++, 1, "[?] What is the ID of the sixmonth that you want to get statistics for? ");
        echo();
        wgetnstr(win, buffer, 100);

        // Check if the professor exists
        for (auto sixmonth : sixmonths)
        {
            if (sixmonth.getSixmonthId() == string(buffer))
            {
                sixmonthExists = true;
                s = sixmonth;
            }
        }
        if (!sixmonthExists)
        {
            mvwprintw(win, currentLine++, 1, "[!] Sixmonth with sixmonthId: %s does not exist.", buffer);
            goto exit;
        }

        mvwprintw(win, currentLine++, 1, "[+] %s %s [%s] teached the following courses the sixmonth %s:",
            p.getFirstName().c_str(),
            p.getLastName().c_str(),
            p.getIdentityID().c_str(),
            s.getSixmonthId().c_str());
        
        // Find the courses the professor teaches this sixmonth
        for(auto professorId : s.getProfessorsIds()) {
            if(professorId == p.getIdentityID()) {
                mvwprintw(win, currentLine++, 1, "[+] %s %s", 
                    courses[indx].getCourseId().c_str(), 
                    courses[indx].getName().c_str());
            }
            indx++;
        }

    // Options
    exit:
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "Press <enter> to get the statistics of another professor.");
        mvwprintw(win, currentLine++, 1, "Move the arrows to select a new option.");
        mvwprintw(win, currentLine++, 1, "Press <q> to quit.");
        wrefresh(win);
    }
    void printStudentsPassed(WINDOW *win) {
       // Variables
        int currentLine = 1;
        char buffer[100];
        bool courseExists = false;
        bool sixmonthExists = false;
        ostringstream oss;
        ofstream outfile;
        Course c;
        Sixmonth s;

        // Input sixmonthId
        mvwprintw(win, currentLine++, 1, "Complete the following questions to get the students that passed a specific course in a specific 6month.");
        mvwprintw(win, currentLine++, 1, "A file containing the students will be save in ./data/{simonthId}-{courseId}-passed.txt");
        mvwprintw(win, currentLine++, 1, "You can save them in a file.");
        mvwprintw(win, currentLine++, 1, "[?] What is the ID of the sixmonth? ");
        echo();
        wgetnstr(win, buffer, 100);

        // Check if the sixmonth exists
        for (auto sixmonth : sixmonths)
        {
            if (sixmonth.getSixmonthId() == string(buffer))
            {
                sixmonthExists = true;
                s = sixmonth;
            }
        }
        if (!sixmonthExists)
        {
            mvwprintw(win, currentLine++, 1, "[!] Sixmonth with sixmonthId: %s does not exist.", buffer);
            goto exit;
        }

        // Input courseId
        mvwprintw(win, currentLine++, 1, "[?] What is the ID of the course? ");
        echo();
        wgetnstr(win, buffer, 100);

        // Check if the course exists
        for (auto course : courses)
        {
            if (course.getCourseId() == string(buffer))
            {
                courseExists = true;
                c = course;
            }
        }
        if (!courseExists)
        {
            mvwprintw(win, currentLine++, 1, "[!] Course with courseId: %s does not exist.", buffer);
            goto exit;
        }

        mvwprintw(win, currentLine++, 1, "[+] The following students passed the course %s at the sixmonth %s:",
            c.getCourseId().c_str(),
            s.getSixmonthId().c_str());
        
        // Save in a file
        oss << "./data/" << c.getCourseId() << "-" << s.getSixmonthId() << "-passed.txt";
        outfile.open(oss.str());
        // Check if the file stream is open
        if (outfile.is_open()) {
            // Find the students that passed the given course at the given sixmonth.
            for (auto attendance : attendances) {
                if (attendance.getCourseId() == c.getCourseId() && 
                    attendance.getSixmonthId() == s.getSixmonthId() &&
                    attendance.getGrade() > 4) {
                        mvwprintw(win, currentLine++, 1, "[+] %s",
                            attendance.getStudentId().c_str());
                        
                        outfile << attendance.getStudentId() << endl;
                    }
            }
            // Close the file stream
            outfile.close();
        }
        else {
            // Handle error if file couldn't be opened
            std::cerr << "Unable to open file for writing." << std::endl;
        }

    // Options
    exit:
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "Press <enter> to get the students that passed another course.");
        mvwprintw(win, currentLine++, 1, "Move the arrows to select a new option.");
        mvwprintw(win, currentLine++, 1, "Press <q> to quit.");
        wrefresh(win); 
    }
    void printDetailedGrades(WINDOW *win) {
        // Variables
        int currentLine = 1;
        char buffer[100];
        bool studentExists = false;
        Student s;

        // Input identityId
        mvwprintw(win, currentLine++, 1, "Print all the grades of the students.");
        mvwprintw(win, currentLine++, 1, "[?] What is the ID of the student? ");
        echo();
        wgetnstr(win, buffer, 100);

        // Check if the student exists
        for (auto student : students)
        {
            if (student.getIdentityID() == string(buffer))
            {
                studentExists = true;
                s = student;
            }
        }
        if (!studentExists)
        {
            mvwprintw(win, currentLine++, 1, "[!] Student with studentId: %s does not exist.", buffer);
            goto exit;
        }

        // Find all the grades and print them.
        for (auto attendance : attendances) {
            if (attendance.getStudentId() == s.getIdentityID()) {
                    mvwprintw(win, currentLine++, 1, "[+] %s passed the course %s at the sixmonth %s with grade %d.",
                        attendance.getStudentId().c_str(),
                        attendance.getCourseId().c_str(),
                        attendance.getSixmonthId().c_str(),
                        attendance.getGrade());
                }
        }

    // Options
    exit:
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "Press <enter> to get the grades of another student.");
        mvwprintw(win, currentLine++, 1, "Move the arrows to select a new option.");
        mvwprintw(win, currentLine++, 1, "Press <q> to quit.");
        wrefresh(win); 
    }
    void printStudentsGraduates(WINDOW *win) {
        // Variables
        int currentLine = 1;
        char buffer[100];

        // Results
        mvwprintw(win, currentLine++, 1, "The students that can graduate are the following:");
        mvwprintw(win, currentLine++, 1, "%10s", 
            "StudentId");
        for (auto attendance : attendances)
        {
            if(currentLine > 30) 
            {
                mvwprintw(win, currentLine++, 1, "See the attendances.csv for more.");
                goto exit;
            }

            
            mvwprintw(win, currentLine++, 1, "%10s %10s %10s %10s %7d",
                attendance.getAttendanceId().c_str(),
                attendance.getSixmonthId().c_str(),
                attendance.getStudentId().c_str(),
                attendance.getCourseId().c_str(),
                attendance.getGrade());
        }

    // Options
    exit:
        mvwprintw(win, currentLine++, 1, " ");
        mvwprintw(win, currentLine++, 1, "Move the arrows to select a new option.");
        mvwprintw(win, currentLine++, 1, "Press <q> to quit.");
        wrefresh(win);
    }

    void saveAll() {
        saveCourses();
        saveProfessors();
        saveStudents();
        saveSixmonths();
        saveAttendances();
    }
    void loadAll() {
        loadCourses();
        loadProfessors();
        loadStudents();
        loadSixmonths();
        loadAttendances();
    }
};

#endif // SECRETARY_H
