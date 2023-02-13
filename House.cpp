//
// Created by LEGION on 1/9/2023.
//

#include "House.h"
#include "Member.h"
#include <iostream>
using std::string;

class Member;

House::House(int id,string location, string description, int rent, int isListed, int occupier, double minRating, double rating) {
    this->id = id;
    this->location = location;
    this->description = description;
    this->rent = rent;
    this->isListed = isListed;
    this->occupier = occupier;
    this->minRating = minRating;
    this->rating = rating;
}


