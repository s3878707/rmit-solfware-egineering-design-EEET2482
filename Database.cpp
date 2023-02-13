//
// Created by LEGION on 1/9/2023.
//

#include "Database.h"
#include <iostream>
#include <vector>
#include <map>
using std::cout;
using std::fstream;
using std::vector;
using std::string;
using std::stringstream;
using std::map;


    Database::Database(string filePath, string fileType) {
        this->filePath = filePath;
        this->fileType = fileType;
    }


    int Database::writeFile() {
        std::fstream myfile;
        myfile.open(filePath, std::ios::out);
        if (!myfile) {
            std::cerr << "Fail to create/open file \n";
            return -1;
        }
        for (int i = 0; i < header.size(); i++) {
            myfile << header[i] << ",";
        }
        myfile << "\n";
        for (int i = 0; i < database.size(); i++) {
            for (int j = 0; j < header.size(); j++) {
                auto search = database[i].find(header[j]);
                myfile << search->second << ",";
            }
            myfile << "\n";
        }
        myfile.close();
        return 0;
    }


    void Database::addMember(vector<string> memberInfo){
        map<string, string> databaseMem;
        for (int i = 0; i < memberInfo.size(); i++) {
            databaseMem.insert(std::pair<string, string>(header[i],memberInfo[i]));
        }
        database.push_back(databaseMem);
    }


    bool Database::readFile() {
        std::fstream myfile;
        myfile.open(filePath,std::ios::out);
        myfile.close();
        myfile.open(filePath, std::ios::in);
        if (!myfile) {
            std::cerr << "Fail to create/open file \n";
            return -1;
        }
        if (fileType == "Member"){
            header= {"id","username","password","fullname","phone number","rating","credit","rent house"};
            }
        if (fileType == "House"){
            header = {"id","location","description","rent","isListed","occupier","minRating","rating"};
        }
        if (fileType == "Requests"){
            header = {"id","house","status"};
        }
        if (fileType == "MemReview"){
            header = {"reviewerID","occupier","rating","comment"};
        }
        if (fileType == "HouseReview"){
            header = {"reviewerID","houseID","rating","comment"};
        }
        while (!myfile.eof()) {
            myfile.ignore(100, '\n');
            map<string, string> databaseMem;
            string category;
            for (int i = 0; i < header.size(); i++) {
                std::getline(myfile, category, ',');
                if (category == ""){
                    return false;
                }
                databaseMem.insert(std::pair<string, string>(header[i], category));

            }
            database.push_back(databaseMem);
        }
        myfile.close();
        return true;
    }


    string Database::searchValueByIDPerson(int id, string key) {
        int temp;
        for (int i=0; i < database.size(); i++) {
            auto search = database[i].find("id");
            if (std::to_string(id) == search->second) {
                temp = i;
            }
        }
        return database[temp].find(key) ->second;
    }


    bool Database::checkValue(string key, string value){
        for (int i = 0; i < database.size(); i++) {
            auto search = database[i].find(key);
            if (value == search->second){
                return true;
            }
        }
        return false;
    }


    void Database::setValueByIDPerson(int id, string key, string value){
        int temp;
        for (int i=0; i < database.size(); i++) {
            auto search = database[i].find("id");
            if (id == std::stoi(search->second)) {
                temp = i;
            }
        }
        database[temp].find(key)->second.replace(0,
                                                 database[temp].find(key)->second.size() ,value);
    }


    vector<map<string,string>> Database::getDatabase() {
        return database;
    }
