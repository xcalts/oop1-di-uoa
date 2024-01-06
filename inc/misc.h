#ifndef MISC_H
#define MISC_H

#include <cstring>
#include <cctype>
#include <cstdlib>
#include <string>
#include <regex>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

bool isValidDateFormat(const string &date)
{
    // Define a regex pattern for the "dd/mm/yyyy" format
    std::regex dateRegex(R"(\b(?:0[1-9]|[12][0-9]|3[01])/(0[1-9]|1[0-2])/\d{4}\b)");

    // Check if the date matches the pattern
    return std::regex_match(date, dateRegex);
}

string getCurrentDateAsString()
{
    // Get the current time point
    auto now = std::chrono::system_clock::now();

    // Convert the time point to a time_t object
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // Convert time_t to a tm structure in the local timezone
    std::tm *localTime = std::localtime(&currentTime);

    // Format the date as a string in "dd/mm/yyyy" format
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << localTime->tm_mday << "/"
        << std::setfill('0') << std::setw(2) << (localTime->tm_mon + 1) << "/"
        << (localTime->tm_year + 1900);

    return oss.str();
}

bool stringToBool(const char* str) {
    if (strcmp(str, "true") == 0 || strcmp(str, "1") == 0) {
        return true;
    } else if (strcmp(str, "false") == 0 || strcmp(str, "0") == 0) {
        return false;
    }

    // Optional: Throw an exception or handle the error for invalid input
    // throw std::invalid_argument("Invalid boolean string");
    return false; // Default case, can also be treated as an error
}

int stringToInt(const char* str) {
    return atoi(str);
}

vector<string> splitString(const string& str, char delimiter) {
    vector<string> tokens;
    stringstream ss(str);
    string token;

    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

string concatenateVector(const vector<string>& vec) {
    if (vec.empty()) {
        return "";
    }

    string result;
    for (size_t i = 0; i < vec.size() - 1; ++i) {
        result += vec[i] + ';';
    }
    result += vec.back(); // Add the last element without the delimiter
    
    return result;
}

#endif // MISC_H