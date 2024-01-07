#ifndef SIXMONTH
#define SIXMONTH

#include <vector>
#include <iostream>
#include <string>
#include <sstream>

#include "misc.h"

using namespace std;

class Sixmonth {
private:
    /* Fields*/
    string sixmonthId;            // The UUID of the sixmonth.
    int year;                     // The academic year that the sixmonth occurs.
    bool isWinter;                // If true, then it is a winter sixmonth. Otherwise, it is spring.
    vector<string> coursesIds;    // The courses that are teached during the sixmonth.
    vector<string> professorsIds; // The professors that teach the courses this sixmonth. 
                                  // Course/Professor works like a pair.
                               
public:
    /* Constructors*/
    Sixmonth() : year(0), isWinter(false) {}
    Sixmonth(string id, int yr, bool winter, const vector<string>& courses, 
             const vector<string>& professors)
        : sixmonthId(id), year(yr), isWinter(winter), coursesIds(courses), 
          professorsIds(professors) {}

    /* Deconstructors */
    ~Sixmonth() {}

    /* Getters */
    const string &getSixmonthId() const {
        return sixmonthId;
    }
    int getYear() const {
        return year;
    }
    bool getIsWinter() const {
        return isWinter;
    }
    const vector<string>& getCoursesIds() const {
        return coursesIds;
    }
    const vector<string>& getProfessorsIds() const {
        return professorsIds;
    }
   
    /* Setters */
    void setSixmonthId(const string &id)
    {
        sixmonthId = id;
    }
    void setYear(int yr) {
        year = yr;
    }
    void setIsWinter(bool winter) {
        isWinter = winter;
    }
    void setCoursesIds(const vector<string>& courses) {
        coursesIds = courses;
    }
    void setProfessorsIds(const vector<string>& professors) {
        professorsIds = professors;
    } 

    /* CSV */ 
    static Sixmonth fromCSVLine(const string& line) {
        // Variables
        stringstream ss(line);
        string token;
        vector<string> tokens;

        // Split line by commas
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        Sixmonth sixmonth;
        sixmonth.setSixmonthId(tokens[0]);
        sixmonth.setYear(stringToInt(tokens[1].c_str()));
        sixmonth.setIsWinter(tokens[2] == "true");
        sixmonth.setCoursesIds(splitString(tokens[3], ';'));
        sixmonth.setProfessorsIds(splitString(tokens[4], ';'));

        return sixmonth;
    }
    string toCSVString() const {
        stringstream ss;
        ss << sixmonthId << "," <<  year << "," << (isWinter ? "true" : "false") << ",";

        // Serialize coursesIds
        for (size_t i = 0; i < coursesIds.size(); ++i) {
            ss << coursesIds[i];
            if (i < coursesIds.size() - 1) ss << ";";
        }
        ss << ",";

        // Serialize professorsIds
        for (size_t i = 0; i < professorsIds.size(); ++i) {
            ss << professorsIds[i];
            if (i < professorsIds.size() - 1) ss << ";";
        }

        return ss.str();
    }
};

#endif // SIXMONTH_H