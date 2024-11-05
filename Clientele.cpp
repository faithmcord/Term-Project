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


/**********
 * @class Clientele
 * @brief a dictionary of all customers of the store indexed by their customer ID
 */
class Clientele: public map<int, Customer::Customer>{
  private:

  public:


    /******************
     * @brief Creates a new customer and stores it into the dictionary
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
    int registerCustomer(string userName, string firstName, string lastName, int age, string creditCardInfo) {
        return 9999999;
      }

    /*************
     *@brief deletes a customer
     *
     *
     *
     *
     */
    int removeCustomer(Customer::Customer customer) {
        return 0;
    }

    //log in before shopping
    int search(int custID) {

        return 0;
    }



}