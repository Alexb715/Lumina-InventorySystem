//
// Created by Alexandre Beaulieu on 2024-08-27.
//
#include "mysql.h"
#include <iostream>
#include <vector>
#include "sstream"
#ifndef DATABASECONTROL_DATABASECONTROLLER_H
#define DATABASECONTROL_DATABASECONTROLLER_H
class DBController{
private:
    //connection to DB
 MYSQL *connection;
    //statement for query
 MYSQL_STMT *STMT;
 //bind
 std::vector<MYSQL_BIND> bind;
 std::vector<int> intValues;        // Store integer values
 std::vector<float> floatValues;    // Store float values
 std::vector<std::string> stringValues; // Store string values
 std::vector<unsigned long> strLength;
public:
    ~DBController();
    DBController();
    bool connect(std::string Server, std::string Username, std::string Password, std::string Database);
    void prepareStatement (std::string Query);
    void bindStatement();
    void prepareBind(std::vector<std::string> Values);
    void executeStatement();
    bool connected();
};
//checks if is an integer
bool isInteger(const std::string& str, int &number);
//checks if its a float
bool isFloat(const std::string& str, float &number);

#endif //DATABASECONTROL_DATABASECONTROLLER_H
