/**********************
*
* File Name:    Utilities.h
* Author(s):    Xander Palermo <ajp2s@missouristate.edu>
* Description:  A container object that manages and preserves all loaded customers in memory
*
* Course:      CSC 455 - Software Quality Assurance
* Instructor:  Mohammed Belkhouche
* Project:     Term Project
* Date:        8 November 2024
*
***********************/

#include "include/Utilities.h"

template <typename Clientele, typename Inventory>
int Utilities::makeTransaction(const Clientele& clientele, const Inventory& inventory, int custID) {
    return 0;
}

bool Utilities::doesFileExist(const std::string& file) {
    std::fstream fs;
    fs.open(file, std::ios::in);
    if (fs.is_open()) {
        fs.close();
        return true;
    } else
        return false;
}