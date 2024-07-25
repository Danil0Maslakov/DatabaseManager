#include "DatabaseManager.h"
#include <iostream>
#include<thread>
#include<vector>
#define NUMOFFSET 100
#define COLNAME 200


DatabaseManager::DatabaseManager(const std::string& host, const std::string& user, const std::string& password, const std::string& database) {
    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect(host, user, password);
    con->setSchema(database);
    pstmt = con->prepareStatement("SELECT * FROM Employees WHERE gender = ? AND fullName LIKE ? ORDER BY fullName");
}

DatabaseManager::~DatabaseManager() {
    delete con;
}

void DatabaseManager::createEmployeeTable() {
    sql::Statement* stmt = con->createStatement();
    stmt->execute("CREATE TABLE IF NOT EXISTS Employees ("
        "id INT AUTO_INCREMENT PRIMARY KEY, "
        "fullName VARCHAR(255), "
        "birthDate DATE, "
        "gender ENUM('Male', 'Female'))");
    delete stmt;
}

void DatabaseManager::addEmployee(const std::string& fullName, const std::string& birthDate, const std::string& gender) {
    sql::PreparedStatement* pstmt = con->prepareStatement("INSERT INTO Employees (fullName, birthDate, gender) VALUES (?, ?, ?)");
    pstmt->setString(1, fullName);
    pstmt->setString(2, birthDate);
    pstmt->setString(3, gender);
    pstmt->executeUpdate();
    delete pstmt;
}

sql::ResultSet* DatabaseManager::getAllEmployees() {
    sql::Statement* stmt = con->createStatement();
    return stmt->executeQuery("SELECT * FROM Employees ORDER BY fullName");
}

sql::ResultSet* DatabaseManager::getFilteredEmployees(const std::string& gender, const std::string& lastNameStart) {
    
    pstmt->setString(1, gender);
    pstmt->setString(2, lastNameStart + "%");
    return pstmt->executeQuery();
}
