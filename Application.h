//
// Created by LEGION on 1/9/2023.
//

#ifndef GROUPASM_APPLICATION_H
#define GROUPASM_APPLICATION_H


#include "House.h"
#include "Member.h"
#include "Database.h"
#include "Admin.h"
#include <iostream>
#include <vector>
#include <iomanip>
using std::cin;
using std::cout;
using std::string;
using std::vector;

class House;
class Member;
class Admin;
class Database;

class Application
{
private:
    Member *member = nullptr;
    House *house = nullptr;
    Database *memsData = nullptr;
    Database *houseData = nullptr;
    Database *requestsData = nullptr;
    Database *reviewMemData = nullptr;
    Database *reviewHouseData = nullptr;
    vector<int> houseOption;
    vector<int> requestOption;
    Admin admin;


public:
    Application();
    void reloadData(string memsData, string houseData, string requestsData, string reviewMemData, string reviewHouseData);
    bool registerMember();
    void addHouse();
    bool memberLogin();
    bool adminLogin();
    void listHouse();
    void unlistHouse();
    bool searchHouse();
    bool requestHouse();
    bool showAllRequest();
    void showRequestedHouse();
    void acceptRequest();
    void showMemInfo(int id);
    void showHouseInfo(int id);
    void guestHouseInfo();
    void adminHousesInfo();
    void adminMemberInfo();
    void showComments(int id);
    bool rateHouse();
    bool rateOccupier();
    bool returnHouse();
    void logout();
    void updateData();
    void mainMenu();

};


#endif //GROUPASM_APPLICATION_H
