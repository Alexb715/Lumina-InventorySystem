//
// Created by Alexandre Beaulieu on 2024-08-27.
//
#ifndef DATABASECONTROL_DATABASECONTROLLER_H
#define DATABASECONTROL_DATABASECONTROLLER_H

#include "mysql/mysql.h"
#include <vector>
#include <string>

class DBController {
private:
    MYSQL *connection;
    MYSQL_STMT *STMT = nullptr;
    std::vector<MYSQL_BIND> bind;
    std::vector<int> intValues;
    std::vector<float> floatValues;
    std::vector<std::string> stringValues;
    std::vector<unsigned long> strLength;

public:
    ~DBController();
    DBController();
    bool connect(const std::string &Server, const std::string &Username,
                 const std::string &Password, const std::string &Database);
    void prepareStatement(const std::string &Query);
    void bindStatement();
    void prepareBind(const std::vector<std::string> &Values);
    void executeStatement();
    bool connected();
};

bool isInteger(const std::string &str, int &number);
bool isFloat(const std::string &str, float &number);

#endif //DATABASECONTROL_DATABASECONTROLLER_H
