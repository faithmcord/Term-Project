/**********************
*
* File Name:    Clientele.cpp
* Author(s):    Xander Palermo <ajp2s@missouristate.edu>
* Description:  A container object that manages and preserves all loaded customers in memory
*
* Course:      CSC 455 - Software Quality Assurance
* Instructor:  Mohammed Belkhouche
* Project:     Term Project
* Date:        8 November 2024
*
***********************/

#include "Clientele.h"

#include "Inventory.h"

std::string Clientele::registerCustomer(const string &userName, const string &firstName, const string &lastName,
                                        const int age, const string &creditCardInfo) {
    const Customer newCustomer = Customer(userName, firstName, lastName, age, creditCardInfo);
    Clientele::addNew(newCustomer);
    std::string custID = newCustomer.getUserID();
    return custID;
}

int Clientele::getCustomerRewards(const std::string &custID) {
    const auto index = container.find(custID);
    const auto end = container.end();
    if (index == end) { // customer does not exist
        return -1;
    }
    else {
        const int reward = index -> second.getRewardPoints();
        return reward;
    }
}

int Clientele::updateCustomerRewards(const std::string &custID, const int amount) {
    const auto index = container.find(custID);
    const auto end = container.end();
    if (index == end) {
        return -1;
    }
    else {
        index -> second.addRewardPoints(amount);
        return 0;
    }
}



