//
// Created by LEGION on 1/9/2023.
//

#ifndef GROUPASM_DATABASE_H
#define GROUPASM_DATABASE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
using std::cout;
using std::fstream;
using std::vector;
using std::string;
using std::stringstream;
using std::map;

class Database {
public:
    vector<map<string,string>> database;
    string filePath;
    vector<string> header;
    string fileType;

public:
    Database(string filePath, string fileType);
    int writeFile();
    void addMember(vector<string> memberInfo);
    bool readFile();
    string searchValueByIDPerson(int id, string key);
    void setValueByIDPerson(int id, string key, string value);
    vector<map<string,string>> getDatabase();
    bool checkValue(string key, string value);
};


#endif //GROUPASM_DATABASE_H
