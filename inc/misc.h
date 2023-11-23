#ifndef MISC_H
#define MISC_H

#include <string>
#include <regex>
#include <chrono>
#include <iostream>
#include <iomanip>

bool isValidDateFormat(const std::string &date)
{
    // Define a regex pattern for the "dd/mm/yyyy" format
    std::regex dateRegex(R"(\b(?:0[1-9]|[12][0-9]|3[01])/(0[1-9]|1[0-2])/\d{4}\b)");

    // Check if the date matches the pattern
    return std::regex_match(date, dateRegex);
}

std::string getCurrentDateAsString()
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

#endif // MISC_H