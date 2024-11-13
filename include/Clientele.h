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

#include "include/Customer.h"
#include "Database.h"

std::string DEFAULT_CLIENTELE_SAVE_PATH = "customers.txt";

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
    std::string registerCustomer(const std::string &userName, const std::string &firstName, const std::string &lastName, int age,
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
    int getCustomerRewards (const std::string &custID);

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

#include "include/Clientele.h"
#include "include/Customer.h"

inline std::string Clientele::registerCustomer(const std::string &userName, const std::string &firstName, const std::string &lastName,
                                               const int age, const std::string &creditCardInfo) {
 const Customer newCustomer = Customer(userName, firstName, lastName, age, creditCardInfo);
 this -> addNew(newCustomer);
 std::string custID = newCustomer.getID();
 return custID;
}

inline int Clientele::getCustomerRewards(const std::string &custID) {
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

inline int Clientele::updateCustomerRewards(const std::string &custID, const int amount) {
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

inline void Clientele::save() {
 return;
}

inline void Clientele::load() {
 return;
}


#endif //CLIENTELE_H
