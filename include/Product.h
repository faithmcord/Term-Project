/**********************
*
* File Name:    Product.h
* Author(s):    Faith Cordsiemon <fmc778s@missouristate.edu>
* Description:  An object class defining a product.
*
* Course:      CSC 455 - Software Quality Assurance
* Instructor:  Mohammed Belkhouche
* Project:     Term Project
* Date:        8 November 2024
*
***********************/

#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <unordered_set>

/**
 * @class Product
 * @brief Manages product details for inventory.
 */
class Product {
private:
    std::string productID;         /**< Unique product ID in format Prod followed by 5 digits */
    std::string name;              /**< Product name or description */
    double price;                  /**< Price of the product */
    int quantity;                  /**< Number of product items available in store */

    static std::unordered_set<std::string> productIDs;  /**< Set of existing product IDs to ensure uniqueness */
    static int productCount;                            /**< Count of users to generate unique product ID */

public:
    /**
     * @brief Constructor for Product creation.
     * @param productID Unique product ID.
     * @param name The product name or description.
     * @param price The product price.
     * @param quantity The quantity of the product in stock.
     * @throws std::invalid_argument if validation fails.
     */
    Product(const std::string& name, double price, int quantity);

    /**
     * @brief Generates a unique User ID.
     * @return The generated User ID in format Prod followed by 5 digits.
     */
    inline static std::string generateProductID();

    /**
     * @brief Checks if the quantity is a positive number.
     * @param quantity The quantity to validate.
     * @return true if the quantity is valid, false otherwise.
     */
    inline static bool isValidQuantity(int quantity);

    /**
     * @brief Checks if the product ID already exists.
     * @param productID The product ID to validate.
     * @return true if the product ID doesn't exist, false otherwise.
     */
    inline static bool isValidProductID(std::string productID);

    /**
     * @brief Adds stock to the product's quantity.
     * @param quantity The amount to add.
     */
    inline void addStock(int quantity);

    /**
     * @brief Removes stock from the product's quantity.
     * @param quantity The amount to remove.
     */
    inline void removeStock(int quantity);

    // Accessors
    std::string getID() const {
        return productID; }
    int getQuantity() const {
        return quantity; }
    double getPrice() const {
        return price; }
    std::string toString() const {
        std::string product =
        "Product ID: " + productID + "\n" +
        "Name: " + name + "\n" +
        "Price: " + std::to_string(price) + "\n" +
        "Quantity: " + std::to_string(quantity);
        return product;
    }

    // Setters
    static void clear() {
        productCount = 0;
        productIDs.clear();
    }
};


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
    if (name.empty()) {
        throw std::invalid_argument("Invalid name.");
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

#endif //PRODUCT_H
