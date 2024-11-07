/**********************
*
* File Name:    Inventory.cpp
* Author(s):	   Xander Palermo <ajp2s@missouristate.edu>
* Description:
*
* Course:      CSC 455 - Software Quality Assurance
* Instructor:  Mohammed Belkhouche
* Project:     Term Project
* Date:        8 November 2024
*
***********************/

#include <Inventory.h>

//GLOBAL VARIABLES
const string DEFAULT_SAVE_PATH = "products.txt";
const string DEFAULT_TRANSACTION_LOG_PATH = "transactions.txt";

Inventory::Inventory() {
    savePath = DEFAULT_SAVE_PATH;
    transactionLogPath = DEFAULT_TRANSACTION_LOG_PATH;
}

Inventory::Inventory(const string &loadFile) {
    savePath = loadFile;
    transactionLogPath = DEFAULT_TRANSACTION_LOG_PATH;
}

Inventory::Inventory(const string &loadFile, const string &transLogFile) {
    savePath = loadFile;
    transactionLogPath = transLogFile;
}

