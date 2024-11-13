/**********************
*
* File Name:    Database.h
* Author(s):    Xander Palermo <ajp2s@missouristate.edu>
* Description:  A container object that manages and preserves information as key:value pairs in memory
*
* Course:      CSC 455 - Software Quality Assurance
* Instructor:  Mohammed Belkhouche
* Project:     Term Project
* Date:        8 November 2024
*
***********************/

#ifndef DATABASE_H
#define DATABASE_H

#include <cstdio>
#include <iostream>
#include <map>
#include <string>

#include "Utilities.h"

constexpr char END_CHAR = '\n';

/**
* @class Database
* @brief A container object that manages and preserves information as key:value pairs in memory
*
*       a wrapper class around std::map
*/
template<typename item>
class Database {
protected:
    /**
    * @brief the path to the file that the method .preserveState() calls
    */
    std::string savePath{};

    /**
    * @brief the data structure used to store all key:value pairs
    */
    std::map<std::string, item> container{};

public:
    /**
     * @brief de-constructor for a Database Object
     */
    virtual ~Database() = default;

    /**
    * @brief standard constructor for a database object
    *
    * @param loadFile the path to the location that Database will load and save to
    */
    explicit Database(const std::string &loadFile);

    /**
    * @brief adds a new key:value pair to the database
    *
    * Key is retrieved by using the .getID method of the object.
    *
    * If a key:value pair already exist at the generated key, then nothing will be done.
    *
    * @pre the value parameter has a .getID method
    *
    * @param value the item to be put into the database (referenced to by its key, its ID)
    *
    * @return 0 if the key:value was successfully added to the database
    * @return -1 if a key:value pair already exists in the database with that key
    */
    virtual int addNew(item value);

    /**
     * @brief removes an existing key:value pair from the database
     *
     * if there exists no key:value pair at the specified key (ID), then nothing will be done.
     *
     * @param ID the key that the key:value pair is indexed at
     *
     * @return 0 if the key:value pair was successfully deleted from the database
     * @return -1 if there does not exist a key:value pair does not exist at the specified location
     */
    virtual int remove(const std::string &ID);

    /**
    * @brief checks if a key:value pair already exist in the database
    *
    * @param ID the key that is being queried for its existence
    *
    * @return true if a key:value pair exist in the database
    * @return false if there is no key:value pair with the specified key
    */
    virtual bool doesExist(const std::string &ID);

    /**
    * @brief finds a key:value pair and prints its value to terminal
    *
    * @pre a key:value pair exist at specified location
    *
    * @param ID the key that is being queried for its existence
    *
    * @return void
    */
    void displayOne(const std::string &ID);

    /**
    * @brief prints every key:value pair contained in the database to terminal
    *
    * @pre the database is not empty
    *
    * @return void
    */
    void displayAll();

    /**
    * @brief saves the current state of the database to the file loaded from at time of construction
    *
    * this action will delete an existing file from loadtime, so a new one will be made in its place
    *
    * @return void
    */
    virtual void preserveState();
};

template<typename item>
Database<item>::Database(const std::string &loadFile) {
    savePath = loadFile;
}

template<typename item>
int Database<item>::addNew(item value) {
    std::string ID = value.getID();
    auto index = container.find(ID);
    if (index != container.end()) {
        // T already exists
        return -1;
    } else {
        container.emplace(ID, value);
        return 0;
    }
}

template<typename item>
int Database<item>::remove(const std::string &ID) {
    auto index = container.find(ID);
    if (index != container.end()) {
        // T already exists
        container.erase(ID);
        return 0;
    } else
        return -1;
}

template<typename item>
bool Database<item>::doesExist(const std::string &ID) {
    auto index = container.find(ID);
    if (index != container.end()) {
        //T already exists
        return true;
    } else
        return false;
}

template<typename item>
void Database<item>::displayOne(const std::string &ID) {
    auto index = container.find(ID);
    auto end = container.end();
    if (index != end) {
        std::string output = index->second.toString();
        std::cout << output << END_CHAR;
    } else {
        std::cout << "NO ENTRY EXISTS" << END_CHAR;
    }
}


template<typename item>
void Database<item>::displayAll() {
    auto index = container.begin();
    auto end = container.end();
    if (index == end) {
        std::cout << "NO ENTRIES EXIST" << END_CHAR;
    } else {
        while (index != end) {
            std::string output = index->second.toString();
            std::cout << output << END_CHAR;
            ++index;
        }
    }
}

template<typename item>
void Database<item>::preserveState() {
    bool fileExists = Utilities::doesFileExist(savePath);
    std::fstream saveFile;
    if (fileExists) {
        std::remove(savePath.c_str());
        saveFile.open(savePath, std::ios::out);
    } else {
        saveFile.open(savePath, std::ios::out);
    }
    auto index = container.begin();
    auto end = container.end();
    while (index != end) {
        std::string output = index->second.toString();
        saveFile << output << END_CHAR;
        ++index;
    }
    saveFile.close();
}

#endif //DATABASE_H