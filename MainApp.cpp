#include "DatabaseManager.h"
#include "Employee.h"
#include <iostream>
#include <vector>
#include <chrono>

void createTable(DatabaseManager& dbManager) {
    dbManager.createEmployeeTable();
    std::cout << "Table created successfully." << std::endl;
}

void addEmployee(DatabaseManager& dbManager, const std::string& fullName, const std::string& birthDate, const std::string& gender) {
    Employee employee(fullName, birthDate, gender);
    dbManager.addEmployee(employee.getFullName(), employee.getBirthDate(), employee.getGender());
    std::cout << "Employee added successfully." << std::endl;
}

void printEmployees(sql::ResultSet* res) {
    while (res->next()) {
        std::string fullName = res->getString("fullName");
        std::string birthDate = res->getString("birthDate");
        std::string gender = res->getString("gender");
        Employee employee(fullName, birthDate, gender);
        std::cout << "Full Name: " << employee.getFullName() << ", Birth Date: " << employee.getBirthDate()
            << ", Gender: " << employee.getGender() << ", Age: " << employee.calculateAge() << std::endl;
    }
}

void getAllEmployees(DatabaseManager& dbManager) {
    sql::ResultSet* res = dbManager.getAllEmployees();
    printEmployees(res);
    delete res;
}

void fillDatabase(DatabaseManager& dbManager) {
    std::vector<std::string> firstNames = { "John", "Jane", "Alex", "Alice", "Robert", "Rachel" };
    std::vector<std::string> lastNames = { "Smith", "Johnson", "Williams", "Brown", "Jones", "Garcia" };
    std::vector<std::string> genders = { "Male", "Female" };

    for (int i = 0; i < 100000; ++i) {
        std::string fullName = lastNames[rand() % lastNames.size()] + " " + firstNames[rand() % firstNames.size()];
        std::string birthDate = std::to_string(1980 + rand() % 40) + "-" + std::to_string(1 + rand() % 12) + "-" + std::to_string(1 + rand() % 28);
        std::string gender = genders[rand() % genders.size()];
        dbManager.addEmployee(fullName, birthDate, gender);
    }

    for (int i = 0; i < 100; ++i) {
        std::string fullName = "F" + std::to_string(rand() % 1000) + " " + firstNames[rand() % firstNames.size()];
        std::string birthDate = std::to_string(1980 + rand() % 40) + "-" + std::to_string(1 + rand() % 12) + "-" + std::to_string(1 + rand() % 28);
        dbManager.addEmployee(fullName, birthDate, "Male");
    }

    std::cout << "Database filled with test data." << std::endl;
}

void queryFilteredEmployees(DatabaseManager& dbManager) {
    auto start = std::chrono::high_resolution_clock::now();
    sql::ResultSet* res = dbManager.getFilteredEmployees("Male", "F");
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    
    printEmployees(res);
    delete res;

    std::cout << "Query execution time: " << diff.count() << " seconds." << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: myApp <mode> [parameters]" << std::endl;
        return 1;
    }

    int mode = std::stoi(argv[1]);
    DatabaseManager dbManager("tcp://127.0.0.1:3306", "root", "#Madidamas1243", "testdb");//testdb нужно создать заранее
    createTable(dbManager);
    try {
        switch (mode) {
        case 1:
            createTable(dbManager);
            break;
        case 2:
            if (argc != 5) {
                std::cerr << "Usage: myApp 2 <fullName> <birthDate> <gender>" << std::endl;
                return 1;
            }
            addEmployee(dbManager, argv[2], argv[3], argv[4]);
            break;
        case 3:
            getAllEmployees(dbManager);
            break;
        case 4:
            fillDatabase(dbManager);
            break;
        case 5:
            queryFilteredEmployees(dbManager);
            break;
        default:
            std::cerr << "Invalid mode specified." << std::endl;
            return 1;
        }
    }
    catch (sql::SQLException& e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
        return 1;
    }
    catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}