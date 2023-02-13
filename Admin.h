#ifndef _ADMIN_H_
#define _ADMIN_H_
/* make sure that this file will be included only once
   (when the keyword _MEMBER_H_ is not defined before)
*/

#include <iostream>
using std::cin;
using std::cout;
using std::string;

class Admin
{
private:
    string username;
    string password;

public:
    Admin();
    string getUsername();
    string getPassword();
};

#endif