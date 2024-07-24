#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <ctime>

class Employee {
public:
    Employee(const std::string& fullName, const std::string& birthDate, const std::string& gender);
    int calculateAge() const;
    std::string getFullName() const;
    std::string getBirthDate() const;
    std::string getGender() const;
private:
    std::string fullName;
    std::string birthDate;
    std::string gender;
};

#endif