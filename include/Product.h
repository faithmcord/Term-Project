//
// Created by Xander Palermo on 11/13/24.
//

#ifndef PRODUCT_H
#define PRODUCT_H


int productCount = 0;

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
     * @return true if the product ID is doesn't exist, false otherwise.
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

    // Accessorsn
    std::string getID() const {
        return productID; }
    int getQuantity() const {
        return quantity; }
    std::string toString() const {
        std::string product =
        "Product ID: " + productID + "/n" +
        "Name: " + name + "/n" +
        "Price: " + std::to_string(price) + "/n" +
        "Quantity: " + std::to_string(quantity);
        return product;
    }
};

#endif //PRODUCT_H
