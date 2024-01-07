#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <vector>

#include "person.h"
#include "semester.h"

using namespace std;

class Course
{
private:
    /* Fields */
    string courseId;              // The UUID of the course.
    string name;                  // The name of the course.
    int noEcts;                   // The number of ECTS of the course.
    Semester semester;            // The semester that it is teached.
    bool isNecessary;             // True, if the course is necessary for gradutation.

public:
    /* Constructors */
    Course() {}

    /* Deconstructor */
    virtual ~Course() {}

    /* Setters */
    void setCourseId(const string& id) {
        courseId = id;
    }
    void setName(const string& courseName) {
        name = courseName;
    }
    void setNoEcts(int ects) {
        noEcts = ects;
    }
    void setSemester(const Semester& sem) {
        semester = sem;
    }
    void setIsNecessary(bool necessary) {
        isNecessary = necessary;
    }
    
    /* Getters */
    string getCourseId() const {
        return courseId;
    }
    string getName() const {
        return name;
    }
    int getNoEcts() const {
        return noEcts;
    }
    Semester getSemester() const {
        return semester;
    }
    bool getIsNecessary() const {
        return isNecessary;
    }

    /* CSV */ 
    static Course fromCSVLine(const string& line) {
        stringstream ss(line);
        string token;
        vector<string> tokens;

        // Split line by commas
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        Course course;
        course.setCourseId(tokens[0]);
        course.setName(tokens[1]);
        course.setNoEcts(stoi(tokens[2]));
        course.setSemester(Semester(stringToInt(tokens[3].c_str())));
        course.setIsNecessary(tokens[4] == "true");
        // course.setProfessorsIds(splitString(tokens[5], ';'));
        // course.setStudentsIds(splitString(tokens[6], ';'));

        return course;
    }
    string toCSVString() const {
        stringstream ss;
        ss << courseId << "," << name << "," << noEcts << "," << semester << ",";
        ss << (isNecessary ? "true" : "false");

        // Serialize professorsIds
        // for (size_t i = 0; i < professorsIds.size(); ++i) {
        //     ss << professorsIds[i];
        //     if (i < professorsIds.size() - 1) ss << ";";
        // }
        // ss << ",";

        // // Serialize studentsIds
        // for (size_t i = 0; i < studentsIds.size(); ++i) {
        //     ss << studentsIds[i];
        //     if (i < studentsIds.size() - 1) ss << ";";
        // }

        return ss.str();
    }
};



#endif // COURSE_H
