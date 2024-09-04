//
// Created by Alexandre Beaulieu on 2024-08-27.
//

#include "DatabaseController.h"
#include "mysql.h"
#include "iostream"
#include <vector>
#include "sstream"
//connects to database
bool DBController::connect(std::string Server, std::string Username, std::string Password,std::string Database) {
    if(mysql_real_connect(connection,Server.c_str(),Username.c_str(),Password.c_str(),Database.c_str(),3306,nullptr,0)){
        STMT = mysql_stmt_init(connection);
        std::cout << "connected";
        return true;
    }
    std::cout << "error Connecting to Database";
    return false;

}
//prepares for connection
DBController::DBController() {
    connection = mysql_init(nullptr);
}
//disconnects
DBController::~DBController() {
    mysql_stmt_close(STMT);
    mysql_close(connection);
    std::cout << "disconnected";

}
//prepares the statement for Binding processe
void DBController::prepareStatement(std::string Query) {
    if(mysql_stmt_prepare(STMT,Query.c_str(), strlen(Query.c_str())) == 0){
        return;
    }
    std::cout << "error preparing statement" << mysql_stmt_error(STMT) <<std::endl;
    return;
}

void DBController::bindStatement(){
    if (mysql_stmt_bind_param(STMT, bind.data()) !=0) {
        // Error binding parameters
        std::cerr << "Error binding parameters: " << mysql_stmt_error(STMT) << std::endl;
    } else {
        // Successfully bound parameters
        std::cout << "Parameters bound successfully" << std::endl;
    }
}

//prepares all the neede values for bind (only works with string floats and int for the moment
void DBController::prepareBind(std::vector<std::string> Values){
    bind.clear(); // Clear existing binds if any
    intValues.clear();        // Clear existing integer values
    floatValues.clear();      // Clear existing float values
    stringValues.clear();     // Clear existing string values

    for (size_t i = 0; i < Values.size(); ++i) {
        int valueInt = 0;
        float valueFloat = 0.0f;
        std::string strValue;

        MYSQL_BIND bindEntry;
        memset(&bindEntry, 0, sizeof(bindEntry)); // Initialize the bind entry

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
            bindEntry.buffer = (char*)stringValues.back().data();
            bindEntry.buffer_length = stringValues.back().size();
            bindEntry.is_null = 0;
            strLength.push_back(stringValues.back().size());
            bindEntry.length = &strLength.back();
        }

        bind.push_back(bindEntry);

        std::cout << "Binding parameter " << i << ": type = " << bindEntry.buffer_type
                  << ", buffer = " << (bindEntry.buffer ? "set" : "not set")
                  << ", length = " << (bindEntry.length ? *bindEntry.length : 0)
                  << std::endl;
    }
    //Proceeds to bind values to statement
    bindStatement();
}
//executes statements in DB
void DBController::executeStatement() {
    if(mysql_stmt_execute(STMT)){
        std::cout<<"could not execute" << mysql_stmt_error(STMT) << mysql_error(connection) ;
    }

}
//make sure it is connected
bool DBController::connected(){
    if(mysql_ping(connection)){
        return false;
    }
    return true;
}


bool isFloat(const std::string& str, float &number) {
    std::istringstream iss(str);
    char c;
    if (iss >> number) {
        // Check if there are extra characters after the number
        if (!(iss >> c)) return true;
    }
    return false;
}

bool isInteger(const std::string& str, int &number) {
    std::istringstream iss(str);
    char c;
    if (iss >> number) {
        // Check if there are extra characters after the number
        if (!(iss >> c)) return true;
    }
    return false;
}