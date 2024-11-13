/**********************
*
* File Name:    Product.cpp
* Author(s):    Faith Cordsiemon <fmc778s@missouristate.edu>
* Description:  An object class defining a product.
*
* Course:      CSC 455 - Software Quality Assurance
* Instructor:  Mohammed Belkhouche
* Project:     Term Project
* Date:        8 November 2024
*
***********************/

#include "Includes.cpp"
#include "include/Product.h"

// Initialize static variable
std::unordered_set<std::string> Product::productIDs;
int Product::productCount = 0;

Product::Product(const std::string& name, double price, int quantity)
{
    if (!isValidProductID(productID) || productIDs.count(productID))
    {
        throw std::invalid_argument("Invalid or duplicate product ID.");
    }
    if (price < 0.0 || !isValidQuantity(quantity))
    {
        throw std::invalid_argument("Invalid price or quantity.");
    }

    this->name = name;
    this->price = price;
    this->quantity = quantity;
    this->productID = generateProductID();

    productIDs.insert(productID);
}

std::string Product::generateProductID() {
    productCount++;
    return "Prod" + std::to_string(10000 + productCount);
}

bool Product::isValidQuantity(int quantity) {
    return quantity > 0;
}

bool Product::isValidProductID(std::string productID) {
    if (productIDs.find(productID) != productIDs.end()) {
        return false;
    } else {
        return true;
    }
}

void Product::addStock(int quantity) {
    if (isValidQuantity(quantity))
    {
        this->quantity += quantity;
    }
}

void Product::removeStock(int quantity) {
    if (quantity > 0 && this->quantity >= quantity)
    {
        this->quantity -= quantity;
    }
}