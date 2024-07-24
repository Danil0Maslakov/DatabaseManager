#pragma once
#ifndef DATABASEMANAGER_H 
#define DATABASEMANAGER_H 
#include "mysql_driver.h"
#include "mysql_connection.h"
#include <cppconn/statement.h> 
#include <cppconn/prepared_statement.h> 
#include <cppconn/resultset.h> 
#include<cppconn/driver.h>
#include <string> 
#include<cppconn/metadata.h>
#include<thread>

class DatabaseManager { 
public: DatabaseManager(const std::string& host, const std::string& user, const std::string& password, const std::string& database); 
	~DatabaseManager(); void createEmployeeTable(); 
	void addEmployee(const std::string& fullName, const std::string& birthDate, const std::string& gender); 
	sql::ResultSet* getAllEmployees(); 
	sql::ResultSet* getFilteredEmployees(const std::string& gender, const std::string& lastNameStart); 
private: 
	sql::mysql::MySQL_Driver* driver; 
	sql::Connection* con; };

#endif