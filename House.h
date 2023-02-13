//
// Created by LEGION on 1/9/2023.
//

#ifndef GROUPASM_HOUSE_H
#define GROUPASM_HOUSE_H

#include "Member.h"
#include <iostream>
using std::string;

class Member;

class House
{
public:
    int id;
    string location;
    string description;
    int rent;
    double minRating;
    int isListed;
    int occupier;
    double rating;

public:
    House(int id,string location, string description, int rent, int isListed, int occupier, double minRating, double rating);
};


#endif //GROUPASM_HOUSE_H
