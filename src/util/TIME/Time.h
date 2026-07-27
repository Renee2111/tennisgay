#ifndef TIME_H
#define TIMEU_H

#include <string>

class Time {
public:
    static bool isLeapYear(int year);

    static bool isValidDateTime(const std::string &datetime);

    static std::string inputDateTime();
};

#endif