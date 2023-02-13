#include "Admin.h"
#include <iostream>
using std::cin;
using std::cout;
using std::string;

Admin::Admin()
{
    this->username = "admin";
    this->password = "123456";
}

string Admin::getUsername() {
    return username;
}

string Admin::getPassword() {
    return password;
}
