//
// Created by LEGION on 1/9/2023.
//

#include "Application.h"
#include "House.h"
#include "Member.h"
#include "Database.h"
#include "Admin.h"
#include <iomanip>
#include <iostream>
#include <vector>
#include <limits>
using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::setw;
class Database;

Application::Application() {}


void Application::reloadData(string memsData, string houseData, string requestsData, string reviewMemData, string reviewHouseData){
    this->memsData = new Database(memsData,"Member");
    this->memsData->readFile();
    this->houseData = new Database(houseData,"House");
    this->houseData->readFile();
    this->requestsData = new Database(requestsData,"Requests");
    this->requestsData->readFile();
    this->reviewMemData = new Database(reviewMemData,"MemReview");
    this->reviewMemData->readFile();
    this->reviewHouseData = new Database(reviewHouseData,"HouseReview");
    this->reviewHouseData->readFile();
}


bool Application::registerMember()
{
    int phone, id, credits;
    string username, password, fullname;
    vector<string> data;
    id = this->memsData->getDatabase().size() + 1;
    data.push_back(std::to_string(id));
    cout << "-->Enter username: ";
    do
    {
        getline(cin, username);
    } while (username == "");
    while(memsData->checkValue("username",username)){
        cout << "*Username already existed!*\n-->Enter username: ";
        do
        {
            getline(cin, username);
        } while (username == "");
    }
    data.push_back(username);
    cout << "-->Enter password: ";
    do
    {
        getline(cin, password);
    } while (password == "");
    data.push_back(password);
    cout << "-->Enter fullname: ";
    do {
        getline(cin, fullname);
    } while (fullname == "");
    data.push_back(fullname);
    cout << "-->Enter phone: ";
    cin >> phone;
    while(std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout << "Enter only number: ";
        std::cin >> phone;
    }
    data.push_back(std::to_string(phone));
    this->member = new Member(id,username, password, fullname, phone,0,500,0);
    data.push_back(std::to_string(this->member->rating));
    data.push_back(std::to_string(this->member->credits));
    data.push_back(std::to_string(this->member->occupyingHouse));
    this->memsData->addMember(data);
    return true;
}


void Application::addHouse(){
    int id, rent;
    float minRating;
    string location, description;
    vector<string> data;
    id = this->member->id;
    data.push_back(std::to_string(id));
    cout << "-->Enter house's location (Sai Gon, Ha Noi, Hue): ";
    do
    {
        getline(cin, location);
    } while (location == "");
    while (location != "Sai Gon" && location != "Hue" && location != "Ha Noi") {
        cout << "*Please only enter either Sai Gon, Ha Noi, or Hue*\n";
        cout << "-->Enter house's location (Sai Gon, Ha Noi, Hue): ";
        getline(cin, location);
    }
    data.push_back(location);
    cout << "-->Enter description: ";
    do
    {
        getline(cin, description);
    } while (description == "");
    data.push_back(description);
    cout << "->>Enter rent :";
    cin >> rent;
    while(std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout << "Enter only number: ";
        std::cin >> rent;
    }
    data.push_back(std::to_string(rent));
    cout << "-->Enter the minimum required rating(from -10 to 10): ";
    cin >> minRating;
    while(std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout << "Enter only number: ";
        std::cin >> minRating;
    }
    while (minRating < -10 || minRating > 10){
        cout << "*Rating must be an integer from -10 to 10*\n";
        cout << "-->Enter the minimum required rating(from -10 to 10): ";
        cin >> minRating;
        while(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout << "Enter only number: ";
            std::cin >> minRating;
        }
    }
    this->house = new House(this->member->id, location, description, rent, 0, 0, minRating,0);
    data.push_back(std::to_string(this->house->isListed));
    data.push_back(std::to_string(this->house->occupier));
    data.push_back(std::to_string(minRating));
    data.push_back(std::to_string(this->house->rating));
    this->houseData->addMember(data);
    cout << "Registration successful!\n";
}


void Application::listHouse() {
    houseData->setValueByIDPerson(this->house->id,"isListed","1");
    cout << "Your house is listed on the market successfully";
}


void Application::unlistHouse() {
    houseData->setValueByIDPerson(this->house->id,"isListed","0");
    cout << "Your house is removed from the market successfully";
}


bool Application::memberLogin() {
    string username, password;
    cout << "Enter your username : ";
    do {
        getline(cin, username);
    } while (username == "");
    for (int i = 0; i < memsData->getDatabase().size(); i++) {
        auto search = memsData->getDatabase()[i].find("username");
        if (username == search->second) {
            while (true) {
                cout << "Enter your password: ";
                do {
                    getline(cin, password);
                } while (password == "");
                search = memsData->getDatabase()[i].find("password");
                if (password == search->second) {
                    this->member = new Member(std::stoi(memsData->searchValueByIDPerson(i + 1, "id")),
                                              memsData->searchValueByIDPerson(i + 1, "username"),
                                              memsData->searchValueByIDPerson(i + 1, "password"),
                                              memsData->searchValueByIDPerson(i + 1, "fullname"),
                                              std::stoi(memsData->searchValueByIDPerson(i + 1, "phone number")),
                                              std::stod(memsData->searchValueByIDPerson(i + 1, "rating")),
                                              std::stoi(memsData->searchValueByIDPerson(i + 1, "credit")),
                                              std::stoi(memsData->searchValueByIDPerson(i + 1, "rent house"))
                    );
                    this->house = new House(this->member->id,
                                            houseData->searchValueByIDPerson(this->member->id,"location"),
                                            houseData->searchValueByIDPerson(this->member->id,"description"),
                                            stoi(houseData->searchValueByIDPerson(this->member->id,"rent")),
                                            stoi(houseData->searchValueByIDPerson(this->member->id,"isListed")),
                                            std::stoi(houseData->searchValueByIDPerson(this->member->id,"occupier")),
                                            std::stof(houseData->searchValueByIDPerson(this->member->id,"minRating")),
                                            std::stod(houseData->searchValueByIDPerson(this->member->id,"rating"))
                                            );
                    return true;
                } else {
                    cout << "Wrong password \n Please enter again .";
                }
            }
        }
    }
    cout << "There is no account ";
    return false;
}


bool Application::requestHouse(){
    if (this->member->occupyingHouse == -1){
        cout << "Your request are waiting for the owner !";
        return false;
    }
    if (this->member->occupyingHouse == 0){
        int id;
        bool found = false;
        while (!found){
            cout << "Enter the house that you want: ";
            cin >> id;
            while(std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                std::cout << "Enter only number: ";
                std::cin >> id;
            }
            for (int i = 0; i < this->houseOption.size(); i++) {
                if (id == this->houseOption[i]){
                    found = true;
                    break;
                }
            }
        }
        if (houseData->searchValueByIDPerson(id,"isListed")== "0"){
            cout << "This house is not available. Please choose other house";
            return false;
        }
        if (stoi(this->houseData->searchValueByIDPerson(id,"occupier")) != 0){
            cout << "This house is occupied !";
            return false;
        }
        if (stoi(this->houseData->searchValueByIDPerson(this->member->id,"id")) == id){
            cout << "You cannot choose your own house";
            return false;
        }
        vector<string> data;
        data.push_back(std::to_string(this->member->id));
        data.push_back(std::to_string(id));
        data.emplace_back("Waiting for owner to accept the request !");
        requestsData->addMember(data);
        memsData->setValueByIDPerson(this->member->id,"rent house","-1");
        cout << "Successfully requested house!\n";
        return true;
    } else{
        cout << "You are occupying a house!\n";
        return false;
    }
}


void Application::acceptRequest() {
    bool found = false;
    string id;
    int credit = stoi(this->memsData->searchValueByIDPerson(this->member->id,"credit"));
    while (!found) {
        cout << "Enter the id : ";
        cin >> id;
        while(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout << "Enter only number: ";
            std::cin >> id;
        }
        for (int i = 0; i < this->requestOption.size(); i++) {
            if (id == std::to_string(this->requestOption[i])) {
                found = true;
                break;
            }
        }
    }
    memsData->setValueByIDPerson(stoi(id), "rent house", std::to_string(this->member->id));
    houseData->setValueByIDPerson(this->member->id, "occupier", id);
    credit += this->house->rent;
    memsData->setValueByIDPerson(this->member->id, "credit", std::to_string(credit));
    int creditLeft = std::stoi(this->memsData->searchValueByIDPerson(std::stoi(id), "credit")) - this->house->rent;
    this->memsData->setValueByIDPerson(stoi(id), "credit", std::to_string(creditLeft));
    int i = 0;
    for (map<string, string> map1: requestsData->database) {
        if (std::to_string(this->member->id) == requestsData->getDatabase()[i].find("house")->second) {
            if (id != requestsData->getDatabase()[i].find("id")->second) {
                memsData->setValueByIDPerson(stoi(requestsData->getDatabase()[i].find("id")->second), "rent house", "0");
            }
            requestsData->database.erase(requestsData->database.begin() + i);
            i = 0;
        } else {
            i++;
        }
    }
    cout <<"Successfully accepted request !\n";
}


void Application::adminHousesInfo(){
    for (int i = 0; i < houseData->getDatabase().size(); i++) {
        showHouseInfo(i+1);
        if (this->houseData->searchValueByIDPerson(i+1, "isListed") == "1"){
            cout << "House " <<  i+1 << " is listed on market, ";
            if (this->houseData->searchValueByIDPerson(i+1,"occupier") == "0"){
                cout << "House " << i+1 <<  " is available for renting";
            }else {
                cout << "House " << i+1 << " is occupied by Member" << this->memsData->searchValueByIDPerson(
                        std::stoi(this->houseData->searchValueByIDPerson(i+1, "occupier")), "id");
            }
        }
        else{
            cout << "House " << i+1 << " is not listed on market";
        }
        showComments(i +1);
        cout << "\n";
    }
}


void Application::adminMemberInfo(){
    for (int i = 0; i < this->memsData->getDatabase().size(); ++i) {
        showMemInfo(i+1);
        cout << "\n";
    }
}


bool Application::searchHouse(){
    string location;
    cout << "Enter location (Ha Noi/Sai Gon/Hue): ";
    do {
        getline(cin, location);
    } while (location =="");
    while (location != "Ha Noi" && location!= "Sai Gon" && location != "Hue"){
        cout <<"Please follow the format of the cities :";
        getline(cin, location);
    }
    for (int i = 0; i < this->houseData->getDatabase().size(); i++) {
        auto search = this->houseData->getDatabase()[i].find("location");
        if (location == search->second) {
            if (this->houseData->getDatabase()[i].find("isListed")->second == std::to_string(1)) {
                if (stoi(this->memsData->searchValueByIDPerson(this->member->id,"credit"))
                >= stoi(this->houseData->getDatabase()[i].find("rent")->second)) {
                    if (stod(this->memsData->searchValueByIDPerson(this->member->id,"rating")) >=
                        std::stod(this->houseData->getDatabase()[i].find("minRating")->second)) {
                        showHouseInfo(std::stoi(this->houseData->getDatabase()[i].find("id")->second));
                        this->houseOption.push_back(std::stoi(this->houseData->getDatabase()[i].find("id")->second));
                        return true;
                    }
                }
            }
        }
    }
    cout << "There is no suitable house";
    return false;
}


void Application::showMemInfo(int id){
    cout <<"* ID: " << id
         << "   Username: " << std::setw(5) << this->memsData->searchValueByIDPerson(id, "username")
         << "   Password: " << std::setw(5) << this->memsData->searchValueByIDPerson(id, "password")
         << "   Fullname: " << std::setw(5) << this->memsData->searchValueByIDPerson(id,"fullname")
         << "   Phone number: " << std::setw(5) << this->memsData->searchValueByIDPerson(id, "phone number")
         << "   Credits: " << std::setw(5) << this->memsData->searchValueByIDPerson(id,"credit")
         << "   Rating: " << std::setw(5) << this->memsData->searchValueByIDPerson(id,"rating");
    if(stoi(this->memsData->searchValueByIDPerson(id,"rent house")) ==0 ) {
        cout << "\nMember " << id << " is not renting a house\n";
    }
    else if(stoi(this->memsData->searchValueByIDPerson(id,"rent house")) == -1){
        cout << "\nMember " << id << " is requesting a house\n";
    }else{
        cout << "\nMember " << id << " is renting House " << this->houseData->searchValueByIDPerson(
                std::stoi(this->memsData->getDatabase()[id - 1].find("rent house")->second), "id") <<"\n";
    }
}


void Application::showHouseInfo(int id){
    cout<< "* House ID: " << id
            << "   Location: "     <<std::setw(5) << this->houseData->searchValueByIDPerson(id, "location")
            << "   Description: " << std::setw(5)<< this->houseData->searchValueByIDPerson(id, "description")
            << "   Rent: "        << std::setw(5)<< this->houseData->searchValueByIDPerson(id, "rent")
            << "   Min-rating: "   << std::setw(5)<< this->houseData->searchValueByIDPerson(id, "minRating")
            << "   Rating: "      << std::setw(5)<<this->houseData->searchValueByIDPerson(id,"rating");
        cout<< "\n";
}


void Application::showComments(int id){
    cout << "\nREIVIEWS: \n";
    for (int i = 0; i < this->reviewHouseData->getDatabase().size(); ++i) {
        if (std::to_string(id) == this->reviewHouseData->getDatabase()[i].find("houseID")->second){
            cout << "+";
            cout << this->reviewHouseData->getDatabase()[i].find("comment")->second << "\n";
        }
    }
}


bool Application::showAllRequest(){
    if (this->requestsData->getDatabase().size() >0) {
        for (int i = 0; i < this->requestsData->getDatabase().size(); i++) {
            if (std::to_string(this->member->id) == this->requestsData->getDatabase()[i].find("house")->second) {
                this->showMemInfo(stoi(this->requestsData->getDatabase()[i].find("id")->second));
                this->requestOption.push_back(std::stoi(this->requestsData->getDatabase()[i].find("id")->second));
            }
        }
        return true;
    }
    cout << "You don't have any request !";
    return false;
};


void Application::showRequestedHouse() {
    if (stoi(this->memsData->searchValueByIDPerson(this->member->id,"rent house")) > 0){
        cout << "Congratulations! Your request was accepted\n";
    }
    if(stoi(this->memsData->searchValueByIDPerson(this->member->id,"rent house")) == 0){
        cout << "You are not requesting any house or your request was rejected\n";
    }
    if(stoi(this->memsData->searchValueByIDPerson(this->member->id,"rent house")) < 0){
        cout << "Your request is waiting for approval. Request details:\n";
        for (int i = 0; i < this->requestsData->getDatabase().size(); i++) {
            if (this->member->id == stoi(this->requestsData->database[i].find("id")->second)) {
                this->showHouseInfo(stoi(this->requestsData->database[i].find("house")->second));
            }
        }
    }
}

bool Application::adminLogin() {
    string username, password;
    cout << "-->Enter admin username: ";
    do {
        getline(cin, username);
    } while (username == "");
    if (username != admin.getUsername()) {
        cout << "*Incorrect admin account*\n";
        return false;
    }
    cout << "-->Enter admin password: ";
    do {
        getline(cin, password);
    } while (password == "");
    while (password != admin.getPassword()) {
        cout << "*Incorrect admin's password*\n";
        cout << "-->Enter admin password: ";
        getline(cin, password);
    }
    if (password == admin.getPassword() && username == admin.getUsername()) {
        return true;
    } else {
        return false;
    }
}


bool Application::rateOccupier() {
    if (this->houseData->searchValueByIDPerson(this->member->id,"occupier") == std::to_string(0)){
        cout << "You don't have any occupier in use\n";
        return false;
    }
    double score;
    double rating = 0;
    int reviewers = 1;
    string comment;
    vector<string> data;
    data.push_back(std::to_string(this->member->id));
    data.push_back(this->houseData->searchValueByIDPerson(this->member->id,"occupier"));
    cout << "Enter the score you want for Member "<< this->houseData->searchValueByIDPerson(this->member->id,"occupier")  <<" (from -10 to 10): ";
    cin >> score;
    while(std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout << "Enter only number: ";
        std::cin >> score;
    }
    data.push_back(std::to_string(score));
    while (score <-10 || score >10){
        cout <<"Please enter you score again (from -10 to 10): ";
        cin >> score;
        while(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout << "Enter only number: ";
            std::cin >> score;
        }
    }
    cout <<"Enter the comment for this occupier: ";
    do {
        getline(cin, comment);
    } while (comment=="");
    data.push_back(comment);
    for (int i = 0; i  < this->reviewMemData->getDatabase().size(); i++) {
        if (this->houseData->searchValueByIDPerson(this->member->id,"occupier") ==
        this->reviewMemData->database[i].find("occupier")->second){
        reviewers++;
        rating += stod(this->reviewMemData->getDatabase()[i].find("rating")->second);
        }
    }
    cout << rating;
    rating = (rating + score) / reviewers;
    this->reviewMemData->addMember(data);
    this->memsData->setValueByIDPerson(stoi(this->houseData->searchValueByIDPerson(this->member->id,"occupier")),"rating", std::to_string(rating));
    cout << "Thank you for your review ^^";
    return true;
}


bool Application::rateHouse(){
    if (this->memsData->searchValueByIDPerson(this->member->id,"rent house") == "0"){
        cout << "You are not renting the house !";
        return false;
    }
    double score;
    double rating = 0;
    int reviewers = 1;
    string comment;
    vector<string> data;
    data.push_back(std::to_string(this->member->id));
    data.push_back(this->memsData->searchValueByIDPerson(this->member->id,"rent house"));
    cout << "Enter the score for House " << this->memsData->searchValueByIDPerson(this->member->id,"rent house") << " you want (from -10 to 10):";
    cin >> score;
    while(std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        std::cout << "Enter only number: ";
        std::cin >> score;
    }
    data.push_back(std::to_string(score));
    while (score <-10 || score >10){
        cout <<"Please enter you score again (from -10 to 10): ";
        cin >> score;
        while(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout << "Enter only number: ";
            std::cin >> score;
        }
    }
    cout <<"Enter the comment for this house";
    do {
        getline(cin, comment);
    } while (comment=="");
    data.push_back(comment);
    for (int i = 0; i  < this->reviewHouseData->getDatabase().size(); i++) {
        if (this->memsData->searchValueByIDPerson(this->member->id,"rent house") ==
            this->reviewHouseData->database[i].find("houseID")->second){
            reviewers++;
            rating += stod(this->reviewHouseData->getDatabase()[i].find("rating")->second);
        }
    }
    cout << reviewers;
    rating = (rating + score) / reviewers;
    this->reviewHouseData->addMember(data);
    this->houseData->setValueByIDPerson(stoi(this->memsData->searchValueByIDPerson(this->member->id,"rent house"))   ,"rating", std::to_string(rating));
    cout << "Thank you for your review ^^";
    return true;
}


void Application::guestHouseInfo(){
    for (int i = 0; i < this->houseData->getDatabase().size(); ++i) {
        showHouseInfo(i+1);
    }
}


bool Application::returnHouse() {
    if (this->memsData->searchValueByIDPerson(this->member->id, "rent house") == "0") {
        cout <<"You are not renting a house !";
        return false;
    }
    this->houseData->setValueByIDPerson(stoi(this->memsData->searchValueByIDPerson(this->member->id,"rent house")),"occupier","0");
    this->memsData->setValueByIDPerson(this->member->id,"rent house","0");
    cout << "Return successfully. Thank you for using our feature.\n";
    return true;

}


void Application::updateData(){
    this->memsData->writeFile();
    this->houseData->writeFile();
    this->requestsData->writeFile();
    this->reviewMemData->writeFile();
    this->reviewHouseData->writeFile();
}


void Application::logout() {
    cout << "Log out ...\n";
    this->member = nullptr;
    this->house = nullptr;
}


void Application::mainMenu() {
    bool exit = false;

    cout << "EEET2482/COSC2082 ASSIGNMENT \n";
    cout << "Instructors: Mr. Linh Tran & Phong Ngo\n";
    cout << "Group 13\n";
    cout << "s3930336 - Hoang Nghia Tri Hung\n";
    cout << "s3983427 - Shirin Shujaa\n";
    cout << "s3927083 - Nguyen Duc Viet\n";
    cout << "s3777228 - Le Anh Khoa \n";
    cout << "s3878707 - Tran Ly The Quang\n\n";
    cout << "*------------------------------------------*\n";
    cout << "|  WELCOME TO HOUSE EXCHANGE APPLICATION!  |\n";
    cout << "*------------------------------------------*\n";

    this->reloadData("Member.txt",
                     "House.txt",
                     "Requests.txt",
                     "MemReview.txt",
                     "HouseReview.txt");
    this->updateData();
    while (!exit) {
        cout << "\nLogin Menu: "
                "\n0. Exit program"
                "\n1. Guest"
                "\n2. Member"
                "\n3. Admin\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        while(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout << "Enter valid option: ";
            std::cin >> choice;
        }
        cout << "\n";

        bool back = false;

        switch (choice) {
            case 0:
                exit = true;
                break;
            case 1:
                while (!back) {
                    cout << "\nGuest Menu: "
                            "\n0. Back "
                            "\n1. View all houses' information "
                            "\n2. Sign up \n";

                    cout << "Enter your choice: ";
                    cin >> choice;
                    while(std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                        std::cout << "Enter valid option: ";
                        std::cin >> choice;
                    }
                    cout << "\n";

                    switch (choice) {
                        case 0:
                            back = true;
                            break;
                        case 1:
                            this->guestHouseInfo();
                            break;
                        case 2:
                            this->registerMember();
                            this->addHouse();
                            this->updateData();
                            back = true;
                            break;
                    }
                }
                break;
            case 2:
                if (!memberLogin()) {
                    break;
                }
                while (!back) {
                    cout << "\nMember Menu: "
                            "\n0. Back "
                            "\n1. View your information "
                            "\n2. Check your request's status"
                            "\n3. List house for exchange "
                            "\n4. Unlist house "
                            "\n5. Search for suitable house "
                            "\n6. View house requests"
                            "\n7. Rate occupier"
                            "\n8. Rate renting house"
                            "\n9. Return renting house"
                            "\n10. Log out";
                    cout << "\nEnter your choice: ";
                    cin >> choice;
                    while(std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                        std::cout << "Enter valid option: ";
                        std::cin >> choice;
                    }
                    cout << "\n";
                    switch (choice) {
                        case 0:
                            back = true;
                            break;
                        case 1:
                            this->showMemInfo(this->member->id);
                            this->showHouseInfo(this->member->id);
                            this->showComments(this->member->id);
                            break;
                        case 2:
                            this->showRequestedHouse();
                            break;
                        case 3:
                            this->listHouse();
                            this->updateData();
                            break;
                        case 4:
                            this->unlistHouse();
                            this->updateData();
                            break;
                        case 5:
                            if(this->searchHouse()) {
                                char c;
                                cout << "Do you want to request a house?[Y/N]: ";
                                cin >> c;
                                while (c != 'Y' && c != 'N') {
                                    cout << "Please only enter Y for yes and N for No\n";
                                    cout << "Do you want to request a house?[Y/N]: ";
                                    cin >> c;
                                }
                                if (c == 'N') {
                                    break;
                                }
                                this->requestHouse();
                                this->updateData();
                            }
                            break;
                        case 6:
                            if (this->showAllRequest()) {
                                char ch;
                                cout << "Do you want to accept a request?[Y/N]: ";
                                cin >> ch;
                                while (ch != 'Y' && ch != 'N') {
                                    cout << "Please only enter Y for yes and N for No\n";
                                    cout << "Do you want to accept a request?[Y/N]: ";
                                    cin >> ch;
                                }

                                this->acceptRequest();
                                this->updateData();
                            }
                            break;
                        case 7:
                            this->rateOccupier();
                            this->updateData();
                            break;
                        case 8:this->rateHouse();
                            this->updateData();

                            break;
                        case 9:
                            this->returnHouse();
                            this->updateData();
                            break;
                            case 10:
                            this->updateData();
                            this->logout();
                            back = true;
                            break;
                    }
                }
                break;
            case 3:
                if (!adminLogin()) {
                    break;
                }
                while (!back) {
                    cout << "\nAdmin Menu: "
                            "\n0. Back "
                            "\n1. View all members information"
                            "\n2. View all houses information";

                    cout << "\nEnter your choice: ";
                    cin >> choice;
                    while(std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
                        std::cout << "Enter valid option: ";
                        std::cin >> choice;
                    }
                    cout << "\n";

                    switch (choice) {
                        case 0:
                            back = true;
                            break;
                        case 1:
                            this->adminMemberInfo();
                            break;
                        case 2:
                            this->adminHousesInfo();
                            break;
                    }
                }
                break;
        }
    }
    this->updateData();
}
