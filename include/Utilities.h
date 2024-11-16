/**********************
*
* File Name:    Utilities.h
* Author(s):    Xander Palermo <ajp2s@missouristate.edu>
* Description:  a utility class that holds etc. functions of use to the program
*
* Course:      CSC 455 - Software Quality Assurance
* Instructor:  Mohammed Belkhouche
* Project:     Term Project
* Date:        8 November 2024
*
***********************/

#ifndef UTILITIES_H
#define UTILITIES_H

#include <fstream>

class Utilities {
public:
    /***
    * @brief updates clientele and inventory atomically
    */
    static bool doesFileExist(const std::string& file);


};

inline bool Utilities::doesFileExist(const std::string& file) {
    std::fstream fs;
    fs.open(file, std::ios::in);
    if (fs.is_open()) {
        fs.close();
        return true;
    } else
        return false;
}

#endif //UTILITIES_H
