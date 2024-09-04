//
// Created by Alexandre Beaulieu on 2024-08-28.
//

// You may need to build the project (run Qt uic code generator) to get "ui_mainWindow.h" resolved

#include "mainwindow.h"
#include "ui_mainWindow.h"
#include "DatabaseController.h"
#include "iostream"
#include <vector>
mainWindow::mainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::mainWindow) {
    ui->setupUi(this);
    ui->statusbar->showMessage("Disconnected");
}

mainWindow::~mainWindow() {
    delete ui;
    //if DB is connected it deletes database to make sure it is disconnected and memory allocation is properly handled
    if(database->connected()){
    delete database;}
}
 //opens login window and sends DB address to its pointer
void mainWindow::on_actionConnect_triggered() {
    login = new loginwindow(nullptr);
    //connects signals to properly send and receive
    connect(this,&mainWindow::SendDb, login,&loginwindow::receiveDB);
    connect(login,&loginwindow::loginClosed,this,&mainWindow::on_loginClosed);
    emit SendDb(database);
    login->show();

}
// when close signal is sent
void mainWindow::on_loginClosed() {
    //when close signal is sent disconnects proper channels
    disconnect(this,&mainWindow::SendDb, login,&loginwindow::receiveDB);
    disconnect(login,&loginwindow::loginClosed,this,&mainWindow::on_loginClosed);
    std::cout << "login Closed";
    //set for window do be deleted for memory allocation
    login->deleteLater();
    if(database->connected()){
        //updates status bar
    ui->statusbar->showMessage("Connected");
    }

}
//all zones work the same checks to mkake sure it is either checked or un checked
void mainWindow::on_zone1_toggled(bool checked) {
    if(checked){
        std::cout << "zone 1 checked";
        zone[1]=1;
    }
    else{
        std::cout << "zone 1 unchecked";
        zone[1]=0;
    }
}

void mainWindow::on_zone2_toggled(bool checked) {
    if(checked){
        std::cout << "zone 2 checked";
        zone[2]=1;
    }
    else{
        std::cout << "zone 2 unchecked";
        zone[2]=0;
    }
}

void mainWindow::on_zone3_toggled(bool checked) {
    if(checked){
        std::cout << "zone 3 checked";
        zone[3]=1;
    }
    else{
        std::cout << "zone 3 unchecked";
        zone[3]=0;
    }
}

void mainWindow::on_zone4_toggled(bool checked) {
    if(checked){
        std::cout << "zone 4 checked";
        zone[4]=1;
    }
    else{
        std::cout << "zone 4 unchecked";
        zone[4]=0;
    }
}

void mainWindow::on_zone5_toggled(bool checked) {
        if(checked){std::cout << "zone 5 checked";
        zone[5]=1;
    }
    else{
        std::cout << "zone 5 unchecked";
        zone[5]=0;
    }

}

void mainWindow::on_zone6_toggled(bool checked) {
    if(checked){
        std::cout << "zone 6 checked";
        zone[6]=1;
    }
    else{
        std::cout << "zone 6 unchecked";
        zone[6]=0;
    }
}

void mainWindow::on_zone7_toggled(bool checked) {
    if(checked){
        std::cout << "zone 7 checked";
        zone[7]=1;
    }
    else{
        std::cout << "zone 7 unchecked";
        zone[7]=0;
    }
}

void mainWindow::on_zone8_toggled(bool checked) {
    if(checked){
        std::cout << "zone 8 checked";
        zone[8]=1;
    }
    else{
        std::cout << "zone 8 unchecked";
        zone[8]=0;
    }
}

void mainWindow::on_zone9_toggled(bool checked) {
    if(checked){
        std::cout << "zone 9 checked";
        zone[9]=1;
    }
    else{
        std::cout << "zone 9 unchecked";
        zone[9]=0;
    }
}
//checks or unchecks all zones
void mainWindow::on_zone10_toggled(bool checked) {
    if(checked){
        for(int i =0; i <10;i++){
        zone[i]=1;
        }
    }
    else{
        for(int i =0; i <10;i++){
            zone[i]=0;
        }
    }
}
void mainWindow::on_zone0_toggled(bool checked){
    if(checked){
        std::cout << "zone 0 checked";
        zone[0]=1;
    }
    else{
        std::cout << "zone 0 unchecked";
        zone[0]=0;
    }
}
//when checkin button is clicked
void mainWindow::on_checkinButton_clicked() {
    //make sure it is connected
    if(!database->connected()){
        ui->statusbar->showMessage("Error Not Connected to Database");
        return;
    }
    //goes thru all zones to properly send the query for only the ones wanted
    for(int i = 0; i < 10; i++) {
        std::vector<std::string> Bindvalue{1};
        Bindvalue[0] = std::to_string(i);
        if(zone[i] == 1){
            database->prepareStatement("UPDATE assets set assigned_to = null, location_id = 0 where _snipeit_zone_4 = ?");
            database->prepareBind(Bindvalue);
            database->executeStatement();
        }
        else{
            continue;
        }
    }
}


//same principle as checkin
void mainWindow::on_checkoutButton_clicked() {
    std::vector<std::string> bindValues(2);
    if(!database->connected()){
        ui->statusbar->showMessage("Error Not Connected to Database");
        return;
    }
    bool first = true;
   for(int i = 0; i< 10; i++){
       if (zone[i] == 1){

           std::vector <std::string> toBeBinded {3};
           toBeBinded[0] = std::to_string(i+4);
           toBeBinded[1]=toBeBinded[0];
           toBeBinded[2] = std::to_string(i);
           database->prepareStatement("update assets set assigned_to = ?, location_id = ? where _snipeit_zone_4 = ?;");
           database->prepareBind(toBeBinded);
           database->executeStatement();
           //because of weird bug that im not sure where it comes from try it without and you will see
           if (first){
               database->prepareStatement("update assets set assigned_to = ?, location_id = ? where _snipeit_zone_4 = ?;");
               database->prepareBind(toBeBinded);
               database->executeStatement();
           }
           first =false;
           continue;
       }
   }



}


