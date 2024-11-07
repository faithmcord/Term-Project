/**********************
*
* File Name:    Database.cpp
* Author(s):    Xander Palermo <ajp2s@missouristate.edu>
* Description:  A container object that manages and preserves all loaded customers in memory
*
* Course:      CSC 455 - Software Quality Assurance
* Instructor:  Mohammed Belkhouche
* Project:     Term Project
* Date:        8 November 2024
*
***********************/

#include <map>
#include <string>
#include <iostream>
#include <cstdio>
#include "Utilities.cpp"


template <typename item>
class DataBase {
    string savePath;

    std::map<int, item> container;

public:
    virtual ~DataBase() = default;

    explicit DataBase(const string &loadFile);

    virtual int addNew(item object);

    virtual int remove(int ID);

    virtual int search(int ID);

    void display();

    virtual int preserveState();
};

template <typename item>
DataBase<item>::DataBase (const string &loadFile) {
    savePath = loadFile;
}

template<typename item>
int DataBase<item>::addNew(item object) {
    int key = object.getID();
    container[key] = object;
    return 0;
}

template<typename item>
int DataBase<item>::remove(int ID) {
    auto index = container.find(ID);
    if (index != container.end()) {
        container.erase(ID);
        return 0;
    }
    else
        return -1;
}

template<typename item>
int DataBase<item>::search(int (ID)) {
    auto index = container.find(ID);
    if (index != container.end()) {
        return 0;
    }
    else
        return -1;
}

template<typename item>
void DataBase<item>::display() {
    auto index = container.begin();
    auto end = container.end();
    while(index != end) {
        std::string output = index -> second.toString();
        std::cout << output << endl;
        ++index;
    }
}

template<typename item>
int DataBase<item>::preserveState() {
    bool fileExists = Utilities::doesFileExist(savePath);
    std::fstream saveFile;
    if (fileExists) {
        std::remove(savePath.c_str());
        saveFile.open(savePath,std::ios::app);
    }
    else {
        saveFile.open(savePath, std::ios::app);
    }
    auto index = container.begin();
    auto end = container.end();
    while(index != end) {
        std::string output = index -> second.toString();
        saveFile << output << endl;
        ++index;
    }
    saveFile.close();
    return 0;
}





