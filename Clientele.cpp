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

#include "Includes.cpp"
#include "Customer.cpp"

//NOTE: Inventory.cpp and Clientele.cpp can be abstracted to one class

/**
 * @class Clientele
 * @extends map
 * @brief a dictionary of all customers of the store indexed by their customer ID
 */
class Clientele: public map<int, Customer::Customer> {
    /**
     * @brief the directory of the save file
     */
    string savePath;

public:
    //abstract
    /**
     * @brief constructor for Clientele
     *
     * @post if loadFile did not exist, clientele will initialize as empty
     *
     * @param loadFile file that previous state of object was captured in
     */
    explicit Clientele(const string &loadFile);

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
     *          @returns -1 on invalid userName - incorrect format
     *          @returns -2 on invalid userName - already used
     *          @returns -3 on invalid firstName
     *          @returns -4 on invalid lastName
     *          @returns -5 on invalid age
     *          @returns -7 on invalid creditCardInfo
     */
    int registerCustomer(string userName, string firstName, string lastName, int age, string creditCardInfo);

    //abstract
    /**
     * @brief deletes a customer of a specified UID
     *
     * @param UID the identifying ID numbers of the customer to be deleted
     *
     * @return 0 on successful deletion
     * @return -1 on customer not found
     */
    int removeCustomer(int UID);

    //abstract
    /**
     * @brief  preforms a search through the dictionary for if a given customer exists
     *
     * @pre custID belongs to a customer that is currently registered
     *
     * @param custID the id of the Customer being searched for
     *
     * @return 0 if customer can be found
     * @return -1 if customer cannot be found
     */
    int search(int custID);

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
    int getCustomerRewards (int custID);

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
     */
    int updateCustomerRewards(int custID, int amount);

    /**
     * @brief saves the current state of Clientele
     *
     * @post if save file is missing, it will be recreated
     * @return 0 on success
     */
    int preserveState();
};

Clientele::Clientele(const string &loadFile) {
  savePath = loadFile;
}

int Clientele::registerCustomer(string userName, string firstName, string lastName, int age, string creditCardInfo) {
  return 0;
}

int Clientele::removeCustomer(int UID) {
  return 0;
}

int Clientele::search(int custID){
  return 0;
}

int Clientele::getCustomerRewards(int custID) {
 return 0;
}

int Clientele::updateCustomerRewards(int custID, int amount) {
 return 0;
}

int Clientele::preserveState() {
 return 0;
}