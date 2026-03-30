//
// Created by Alexandre Beaulieu on 2024-08-27.
//

#include "DatabaseController.h"
#include <QDebug>
#include <cstring>
#include <sstream>

bool DBController::connect(const std::string &Server, const std::string &Username,
                           const std::string &Password, const std::string &Database) {
    if (mysql_real_connect(connection, Server.c_str(), Username.c_str(),
                           Password.c_str(), Database.c_str(), 3306, nullptr, 0)) {
        STMT = mysql_stmt_init(connection);
        qDebug() << "Connected to database";
        return true;
    }
    qWarning() << "Error connecting to database:" << mysql_error(connection);
    return false;
}

DBController::DBController() {
    connection = mysql_init(nullptr);
}

DBController::~DBController() {
    if (STMT) mysql_stmt_close(STMT);
    if (connection) mysql_close(connection);
    qDebug() << "Database disconnected";
}

void DBController::prepareStatement(const std::string &Query) {
    if (mysql_stmt_prepare(STMT, Query.c_str(), Query.size()) != 0) {
        qWarning() << "Error preparing statement:" << mysql_stmt_error(STMT);
    }
}

void DBController::bindStatement() {
    if (mysql_stmt_bind_param(STMT, bind.data()) != 0) {
        qWarning() << "Error binding parameters:" << mysql_stmt_error(STMT);
    }
}

void DBController::prepareBind(const std::vector<std::string> &Values) {
    bind.clear();
    intValues.clear();
    floatValues.clear();
    stringValues.clear();
    strLength.clear();

    // Reserve capacity to prevent reallocation, which would invalidate
    // the buffer pointers stored in MYSQL_BIND entries
    size_t n = Values.size();
    intValues.reserve(n);
    floatValues.reserve(n);
    stringValues.reserve(n);
    strLength.reserve(n);
    bind.reserve(n);

    for (size_t i = 0; i < Values.size(); ++i) {
        int valueInt = 0;
        float valueFloat = 0.0f;

        MYSQL_BIND bindEntry;
        memset(&bindEntry, 0, sizeof(bindEntry));

        if (isInteger(Values[i], valueInt)) {
            intValues.push_back(valueInt);
            bindEntry.buffer_type = MYSQL_TYPE_LONG;
            bindEntry.buffer = &intValues.back();
            bindEntry.is_null = 0;
            bindEntry.length = 0;
        } else if (isFloat(Values[i], valueFloat)) {
            floatValues.push_back(valueFloat);
            bindEntry.buffer_type = MYSQL_TYPE_FLOAT;
            bindEntry.buffer = &floatValues.back();
            bindEntry.is_null = 0;
            bindEntry.length = 0;
        } else {
            stringValues.push_back(Values[i]);
            bindEntry.buffer_type = MYSQL_TYPE_STRING;
            bindEntry.buffer = (char *)stringValues.back().data();
            bindEntry.buffer_length = stringValues.back().size();
            bindEntry.is_null = 0;
            strLength.push_back(stringValues.back().size());
            bindEntry.length = &strLength.back();
        }

        bind.push_back(bindEntry);
    }

    bindStatement();
}

void DBController::executeStatement() {
    if (mysql_stmt_execute(STMT)) {
        qWarning() << "Error executing statement:" << mysql_stmt_error(STMT);
    }
}

bool DBController::connected() {
    if (mysql_ping(connection)) {
        return false;
    }
    return true;
}

bool isFloat(const std::string &str, float &number) {
    std::istringstream iss(str);
    char c;
    if (iss >> number) {
        if (!(iss >> c)) return true;
    }
    return false;
}

bool isInteger(const std::string &str, int &number) {
    std::istringstream iss(str);
    char c;
    if (iss >> number) {
        if (!(iss >> c)) return true;
    }
    return false;
}
