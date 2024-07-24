#include "Employee.h"
#include <sstream>
#include<iomanip>
#pragma warning(disable:4996)

Employee::Employee(const std::string& fullName, const std::string& birthDate, const std::string& gender)
    : fullName(fullName), birthDate(birthDate), gender(gender) {}

int Employee::calculateAge() const {
    std::tm birth = {};
    std::istringstream ss(birthDate);
    ss >> std::get_time(&birth, "%Y-%m-%d");
    std::time_t birth_time = std::mktime(&birth);

    std::time_t now = std::time(nullptr);
    std::tm* now_tm = std::localtime(&now);

    int age = now_tm->tm_year - birth.tm_year;
    if (now_tm->tm_mon < birth.tm_mon || (now_tm->tm_mon == birth.tm_mon && now_tm->tm_mday < birth.tm_mday)) {
        age--;
    }
    return age;
}

std::string Employee::getFullName() const {
    return fullName;
}

std::string Employee::getBirthDate() const {
    return birthDate;
}

std::string Employee::getGender() const {
    return gender;
}