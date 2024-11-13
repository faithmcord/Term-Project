/**********************
*
* File Name:    Customer.cpp
* Author(s):    Faith Cordsiemon <fmc778s@missouristate.edu>
* Description:  An object class defining a customer.
*
* Course:      CSC 455 - Software Quality Assurance
* Instructor:  Mohammed Belkhouche
* Project:     Term Project
* Date:        8 November 2024
*
***********************/

#include "Includes.cpp"

const std::string USER_NAME_ERROR = "Invalid or duplicate username.";
const std::string NAME_ERROR = "Invalid name.";
const std::string AGE_ERROR = "Invalid age.";
const std::string CREDIT_CARD_ERROR = "Invalid or duplicate credit card.";

/**
 * @class Customer
 * @brief Manages customer details and provides customer registration service.
 */
class Customer {
private:
    std::string username;          /**< Username of the customer, must be unique */
    std::string firstName;         /**< First name of the customer */
    std::string lastName;          /**< Last name of the customer */
    int age;                       /**< Age of the customer */
    std::string creditCard;        /**< Credit card number in xxxx-xxxx-xxxx format */
    std::string userID;            /**< Unique user ID in format CustID followed by 10 digits */
    int rewardPoints;              /**< Reward points for the customer */

    static std::unordered_set<std::string> usernames; /**< Set of existing usernames to ensure uniqueness */
    static std::unordered_set<std::string> creditCards; /**< Set of credit card numbers to ensure uniqueness */
    static int userCount;           /**< Count of users to generate unique user ID */

public:
    /**
     * @brief Constructor for Customer registration.
     * @param username The unique username.
     * @param firstName The first name of the customer.
     * @param lastName The last name of the customer.
     * @param age The age of the customer.
     * @param creditCard The credit card number in xxxx-xxxx-xxxx format.
     * @throws std::invalid_argument if validation fails.
     */
    Customer(const std::string& username, const std::string& firstName,
             const std::string& lastName, int age, const std::string& creditCard);

    /**
     * @brief Generates a unique User ID.
     * @return The generated User ID in format CustID followed by 10 digits.
     */
    static std::string generateUserID();

    /**
     * @brief Checks if the username format is valid.
     * @param username The username to validate.
     * @return true if the username is valid, false otherwise.
     */
    static bool isValidUsername(const std::string& username);

    /**
     * @brief Checks if the name format is valid.
     * @param name The name (first or last) to validate.
     * @return true if the name is valid, false otherwise.
     */
    static bool isValidName(const std::string& name);

    /**
     * @brief Checks if the age is within the valid range.
     * @param age The age to validate.
     * @return true if the age is valid, false otherwise.
     */
    static bool isValidAge(int age);

    /**
     * @brief Checks if the credit card number format is valid.
     * @param card The credit card number to validate.
     * @return true if the credit card number is valid, false otherwise.
     */
    static bool isValidCreditCard(const std::string& card);

    /**
     * @brief Adds reward points to the customer's account.
     * @param points The points to add, must be positive.
     */
    void addRewardPoints(int points);

    // Accessors
    std::string getID() const { 
        return userID; }
    int getRewardPoints() const { 
        return rewardPoints; }
    std::string viewCustomer() const {
        std::string customer = 
        "Customer ID: " + userID + "/n" + 
        "Username: " + username + "/n" + 
        "Name: " + firstName + " " + lastName + "/n" + 
        "Age: " + std::to_string(age) + "/n" + 
        "Credit Card Number: " + creditCard;
        return customer;
    }
};

// Initialize static variables
std::unordered_set<std::string> Customer::usernames;
std::unordered_set<std::string> Customer::creditCards;
int Customer::userCount = 0;

Customer::Customer(const std::string& username, const std::string& firstName,
                   const std::string& lastName, int age, const std::string& creditCard)
{
    if (!isValidUsername(username) || usernames.count(username))
    {
        throw std::invalid_argument(USER_NAME_ERROR);
    }
    if (!isValidName(firstName) || !isValidName(lastName))
    {
        throw std::invalid_argument(NAME_ERROR);
    }
    if (!isValidAge(age))
    {
        throw std::invalid_argument(AGE_ERROR);
    }
    if (!isValidCreditCard(creditCard) || creditCards.count(creditCard))
    {
        throw std::invalid_argument(CREDIT_CARD_ERROR);
    }

    this->username = username;
    this->firstName = firstName;
    this->lastName = lastName;
    this->age = age;
    this->creditCard = creditCard;
    this->rewardPoints = 0;
    this->userID = generateUserID();

    usernames.insert(username);
    creditCards.insert(creditCard);
}

std::string Customer::generateUserID() {
    userCount++;
    return "CustID" + std::to_string(1000000000 + userCount);
}

bool Customer::isValidUsername(const std::string& username) {
    return std::regex_match(username, std::regex("^U\\d{1,3}[a-zA-Z]{7,}$"));
}

bool Customer::isValidName(const std::string& name) {
    return name.size() <= 12 && std::regex_match(name, std::regex("^[a-zA-Z]+$"));
}

bool Customer::isValidAge(int age) {
    return age >= 18 && age <= 100;
}

bool Customer::isValidCreditCard(const std::string& card) {
    return std::regex_match(card, std::regex("^[1-9]\\d{3}-\\d{4}-\\d{4}$"));
}

void Customer::addRewardPoints(int points) {
    if (points > 0)
    {
        rewardPoints += points;
    }
}