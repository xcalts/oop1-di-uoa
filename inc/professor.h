#ifndef PROFESSOR_H
#define PROFESSOR_H

#include "person.h"
#include <string>

using namespace std;

class Professor : public Person
{
private:
    /* Fields */
    string field;

public:
    /* Constructors */
    Professor() : Person() {}

    /* Getters */
    const string &getField() const {
        return field;
    }

    /* Setters */
    void setField(const string &newField) {
        field = newField;
    }

    /* CSV Serialization */ 
    static Professor fromCSVLine(const string& line) {
        stringstream ss(line);
        string token;
        vector<string> tokens;

        // Split line by commas
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        Professor professor;
        professor.setIdentityID(tokens[0]);
        professor.setFirstName(tokens[1]);
        professor.setLastName(tokens[2]);
        professor.setBirthDate(tokens[3]);
        professor.setField(tokens[4]);

        return professor;
    }
    string toCSVString() const {
        stringstream ss;
        
        ss << getIdentityID() << "," << getFirstName() << "," << getLastName() << "," << getBirthDate() << "," << getField();

        return ss.str();
    }
};

#endif // PROFESSOR_H
