/**********************
*
* File Name:    Clientele.h
* Author(s):    Xander Palermo <ajp2s@missouristate.edu>
* Description:  A container object that manages and preserves all loaded customers in memory
*
* Course:      CSC 455 - Software Quality Assurance
* Instructor:  Mohammed Belkhouche
* Project:     Term Project
* Date:        8 November 2024
*
***********************/

#ifndef CLIENTELE_H
#define CLIENTELE_H

#include "Customer.h"
#include "Database.h"

std::string DEFAULT_CLIENTELE_SAVE_PATH = "./resources/customers.txt";

/**
 * @class Clientele
 * @brief a dictionary of all customers of the store indexed by their customer ID
 */
class Clientele final : public Database<Customer> {
    /**
     * @brief the directory of the save file
     */
    std::string savePath;

public:
    //abstract
    /**
     * @brief constructor for Clientele
     *
     * @post if loadFile did not exist, clientele will initialize as empty
     *
     * @param loadFile file that previous state of object was captured in
     */
    using Database::Database;

    /**
     * @brief Creates a new customer and stores it into the dictionary
     *
     * @pre userName is unique
     * @pre firstName & lastName < 12 characters long
     * @pre age is within the range [18,100]
     *
     * @param userName          the designated username the new customer chooses (123ABCDEF)
     * @param firstName         the first name of the new customer
     * @param lastName          the last name of the new customer
     * @param age               the age of the new customer
     * @param creditCardInfo    the Credit Card number of the new customer (xxxx-xxxx-xxxx)
     *
     * @return the user ID of the newly registered customer or the following error code
     *
     * @throws std::invalid_argument if validation fails
     */
    std::string registerCustomer(const std::string &userName, const std::string &firstName, const std::string &lastName,
                                 int age,
                                 const std::string &creditCardInfo);

    /**
     * @brief finds a customer in self and relays the amount of rewards points they have
     *
     * @pre custID belongs to a customer that is currently registered
     *
     * @param custID the id of the Customer that rewards are being retrieved
     *
     * @return the amount of rewards saved by the customer
     * @return -1 if custID not found
     */
    int getCustomerRewards(const std::string &custID);

    /**
     * @brief adds or subtracts rewards to a specified customer's rewards bank
     *
     * @post if rewards will subtract to a negative amount, it will be set to 0
     *
     * @param custID the id of the Customer that rewards are being updated
     * @param amount the amount of reward points to be added to the customer's rewards bank.
     *                  If amount is negative, amount will be subtracted
     *
     * @return 0 on success
     * @return -1 if customer does not exist
     */
    int updateCustomerRewards(const std::string &custID, int amount);

    void save() override;

    void load() override;
};


inline std::string Clientele::registerCustomer(const std::string &userName, const std::string &firstName,
                                               const std::string &lastName,
                                               const int age, const std::string &creditCardInfo) {
    const Customer newCustomer = Customer(userName, firstName, lastName, age, creditCardInfo);
    this->addNew(newCustomer);
    std::string custID = newCustomer.getID();
    return custID;
}

inline int Clientele::getCustomerRewards(const std::string &custID) {
    const auto index = container.find(custID);
    const auto end = container.end();
    if (index == end) {
        // customer does not exist
        return -1;
    } else {
        const int reward = index->second.getRewardPoints();
        return reward;
    }
}

inline int Clientele::updateCustomerRewards(const std::string &custID, const int amount) {
    const auto index = container.find(custID);
    const auto end = container.end();
    if (index == end) {
        return -1;
    } else {
        index->second.addRewardPoints(amount);
        return 0;
    }
}

inline void Clientele::save() {
    std::fstream saveFile;
    saveFile.open(savePath, std::ios::out);
    int indexNumber = 0;
    auto indexPointer = container.begin();
    const auto end = container.end();
    while (indexPointer != end) {
        saveFile << "Customer " << ++indexNumber << '\n';
        std::string output;
        output += indexPointer->second.toString();
        saveFile << output << '\n';
        ++indexPointer;
    }
    saveFile.close();
}

inline void Clientele::load() {
    bool fileExists = Utilities::doesFileExist(DEFAULT_CLIENTELE_SAVE_PATH);
    if (!fileExists) {
        return;
    } else {
        /* Do nothing */
    }
    std::fstream saveFile;
    saveFile.open(DEFAULT_CLIENTELE_SAVE_PATH);

    // Colors text Red lol
    std::string errorColorMod = "\033[1;31m";
    std::string defaultColorMod = "\033[1;39m";

    while ( true ) {
        std::string line, userNameString, fullNameString, firstNameString, lastNameString,
                        ageString, creditCardNumberString, rewardPointsString;

        std::getline ( saveFile, line );
        if ( line.empty() ) {
            break;
        } else {
            /* Do nothing */
        }
        std::getline ( saveFile, line );

        std::getline ( saveFile, userNameString );
        std::getline ( saveFile, fullNameString);
        std::getline ( saveFile, ageString);
        std::getline ( saveFile, creditCardNumberString );
        std::getline ( saveFile, rewardPointsString );

        // String Comprehension
        userNameString.erase(0,10);
        fullNameString.erase(0,6);
        unsigned long split = fullNameString.find(' ');
        firstNameString = fullNameString.substr(0,split-1);
        lastNameString = fullNameString.substr(split+1, std::string::npos);
        ageString.erase(0,5);
        creditCardNumberString.erase(0,20);
        rewardPointsString.erase(0,0);



        try {
            this -> registerCustomer(userNameString, firstNameString, lastNameString, std::stoi(ageString), creditCardNumberString );
        } catch ( std::invalid_argument &invalid_argument ) {
            std::cout << errorColorMod << "Problem encountered while loading " << savePath << ": " << invalid_argument.what()
                // << "Failed to load customer:\nUsername: " << userNameString << "\nFirst Name: " << firstNameString << "\nLast Name: " << lastNameString
                // << "\nAge: " << ageString << "\nCredit Card Number: " << creditCardNumberString << "\nReward Points: " << rewardPointsString
                << defaultColorMod << '\n';
        } catch ( std::out_of_range &out_of_range) {
            std::cout << errorColorMod << "Problem encountered while loading " << savePath << ": " << out_of_range.what()
                // << "Failed to load customer:\nUsername: " << userNameString << "\nFirst Name: " << firstNameString << "\nLast Name: " << lastNameString
                // << "\nAge: " << ageString << "\nCredit Card Number: " << creditCardNumberString << "\nReward Points: " << rewardPointsString
                << defaultColorMod << '\n';
        }
    }
    saveFile.close();
}


#endif //CLIENTELE_H
