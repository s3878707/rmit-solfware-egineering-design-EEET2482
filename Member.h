//
// Created by LEGION on 1/9/2023.
//

#ifndef GROUPASM_MEMBER_H
#define GROUPASM_MEMBER_H
#include "House.h"
#include <iostream>
using std::cout;
using std::string;

class House;

class Member
{
public:
    int id;
    string username;
    string password;
    string fullname;
    int phone;
    int credits;
    double rating;
    int occupyingHouse;

public:
    Member(int id, string username, string password,string fullname, int phone,double rating, int credits, int occupyingHouse);
};

#endif //GROUPASM_MEMBER_H
