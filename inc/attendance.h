#ifndef ATTENDANCE
#define ATTENDANCE

#include <string>
#include <iostream>
#include <sstream>

using namespace std;

class Attendance {
private:
    string attendanceId; // The UIID of the attendance
    string sixmonthId;   // The ID of the sixmonth
    string studentId;    // The ID of the student that owns the grade
    string courseId;     // The ID of the course that is graded
    int grade;           // The value of the grade

public:
    /* Constructors */
    Attendance() : grade(0) {}
    Attendance(const string& attendanceId, const string& sixmonthId, const std::string& studentId, const std::string& courseId, int gradeValue) 
        : attendanceId(attendanceId), sixmonthId(sixmonthId), studentId(studentId), courseId(courseId), grade(gradeValue) {}

    /* Deconstructors */
    ~Attendance() {}

    /* Getters */
    string getAttendanceId() const {
        return attendanceId;
    }
    string getSixmonthId() const {
        return sixmonthId;
    }
    string getStudentId() const {
        return studentId;
    }
    string getCourseId() const {
        return courseId;
    }
    int getGrade() const {
        return grade;
    }

    /* Setters */
    void setAttendanceId(const string &id) {
        attendanceId = id;
    }
    void setSixmonthId(const string &id) {
        sixmonthId = id;
    }
    void setStudentId(const string &id) {
        studentId = id;
    }
    void setCourseId(const string &id) {
        courseId = id;
    }
    void setGrade(int g) {
        grade = g;
    }

    /* CSV */
    static Attendance fromCSVLine(const string& line) {
        // Variables
        stringstream ss(line);
        string token;
        vector<string> tokens;

        // Split line by commas
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        // Set values
        Attendance attendance;
        attendance.setAttendanceId(tokens[0]);
        attendance.setSixmonthId(tokens[1]);
        attendance.setStudentId(tokens[2]);
        attendance.setCourseId(tokens[3]);
        attendance.setGrade(stoi(tokens[4]));

        return attendance;
    }
    string toCSVString() const {
        stringstream ss;
        
        ss << attendanceId << "," << sixmonthId << "," << studentId << "," << courseId << "," << grade;

        return ss.str();
    }
};

#endif // ATTENDANCE_H