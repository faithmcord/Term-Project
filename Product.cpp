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

    static std::unordered_set<std::string> productIDs; /**< Set of existing product IDs to ensure uniqueness */

public:
    /**
     * @brief Constructor for Product creation.
     * @param productID Unique product ID.
     * @param name The product name or description.
     * @param price The product price.
     * @param quantity The quantity of the product in stock.
     * @throws std::invalid_argument if validation fails.
     */
    Product(const std::string& productID, const std::string& name, double price, int quantity);

    /**
     * @brief Checks if the product ID format is valid.
     * @param productID The product ID to validate.
     * @return true if the product ID is valid, false otherwise.
     */
    bool isValidProductID(const std::string& productID);

    /**
     * @brief Checks if the quantity is a positive number.
     * @param quantity The quantity to validate.
     * @return true if the quantity is valid, false otherwise.
     */
    bool isValidQuantity(int quantity);

    /**
     * @brief Adds stock to the product's quantity.
     * @param quantity The amount to add.
     */
    void addStock(int quantity);

    /**
     * @brief Removes stock from the product's quantity.
     * @param quantity The amount to remove.
     */
    void removeStock(int quantity);

    // Accessors
    std::string getProductID() const { return productID; }
    int getQuantity() const { return quantity; }
};

// Initialize static variable
std::unordered_set<std::string> Product::productIDs;

Product::Product(const std::string& productID, const std::string& name, double price, int quantity)
{
    if (!isValidProductID(productID) || productIDs.count(productID))
    {
        throw std::invalid_argument("Invalid or duplicate product ID.");
    }
    if (price < 0.0 || !isValidQuantity(quantity))
    {
        throw std::invalid_argument("Invalid price or quantity.");
    }

    this->productID = productID;
    this->name = name;
    this->price = price;
    this->quantity = quantity;

    productIDs.insert(productID);
}

bool Product::isValidProductID(const std::string& productID) {
    return std::regex_match(productID, std::regex("^Prod\\d{5}$"));
}

bool Product::isValidQuantity(int quantity) {
    return quantity > 0;
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