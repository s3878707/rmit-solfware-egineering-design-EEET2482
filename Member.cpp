//
// Created by LEGION on 1/9/2023.
//

#include "Member.h"
#include "Application.h"
#include <iostream>
using std::cout;
using std::string;

Member::Member(int id, string username, string password,string fullname, int phone,double rating, int credits, int occupyingHouse)
{
    this->id = id;
    this->username = username;
    this->password = password;
    this->fullname = fullname;
    this->phone = phone;
    this->rating = rating;
    this->credits = credits;
    this->occupyingHouse = occupyingHouse;
}

