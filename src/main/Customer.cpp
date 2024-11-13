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
#include "include/Customer.h"

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