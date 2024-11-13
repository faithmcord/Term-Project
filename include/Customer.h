//
// Created by Xander Palermo on 11/13/24.
//

#ifndef CUSTOMER_H
#define CUSTOMER_H

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
    inline static std::string generateUserID();

    /**
     * @brief Checks if the username format is valid.
     * @param username The username to validate.
     * @return true if the username is valid, false otherwise.
     */
    inline static bool isValidUsername(const std::string& username);

    /**
     * @brief Checks if the name format is valid.
     * @param name The name (first or last) to validate.
     * @return true if the name is valid, false otherwise.
     */
    inline static bool isValidName(const std::string& name);

    /**
     * @brief Checks if the age is within the valid range.
     * @param age The age to validate.
     * @return true if the age is valid, false otherwise.
     */
    inline static bool isValidAge(int age);

    /**
     * @brief Checks if the credit card number format is valid.
     * @param card The credit card number to validate.
     * @return true if the credit card number is valid, false otherwise.
     */
    inline static bool isValidCreditCard(const std::string& card);

    /**
     * @brief Adds reward points to the customer's account.
     * @param points The points to add, must be positive.
     */
    inline void addRewardPoints(int points);

    // Accessors
    std::string getID() const {
        return userID; }
    int getRewardPoints() const {
        return rewardPoints; }
    std::string toString() const {
        std::string customer =
        "Customer ID: " + userID + "/n" +
        "Username: " + username + "/n" +
        "Name: " + firstName + " " + lastName + "/n" +
        "Age: " + std::to_string(age) + "/n" +
        "Credit Card Number: " + creditCard;
        return customer;
    }
};

#endif //CUSTOMER_H
