/**********************
*
* File Name:    Rewards.h
* Author(s):    Xander Palermo <ajp2s@missouristate.edu>
* Description:  A database that holds rewards that can be exchanged for reward points
*
* Course:      CSC 455 - Software Quality Assurance
* Instructor:  Mohammed Belkhouche
* Project:     Term Project
* Date:        8 November 2024
*
***********************/
#ifndef REWARDS_H
#define REWARDS_H

#include "Inventory.h"
#include "Product.h"

const std::string DEFAULT_REWARDS_SAVE_PATH = "rewards.txt";

/**
 * @class Rewards
 *
 * A database that holds rewards that can be exchanged for reward points
 *
 *      model is an extension of Inventory (using products to store rewards)
 *
 *  Notes: While product is capable of storing a double, reward points are stored as int. So there is a
 *          type narrowing that occurs when saving and editing these rewards
 */
class Rewards final : public Inventory {
private:

    std::string savePath;    /** @brief the path to the file that the method .save() calls */

public:
    /**
     * @brief default constructor for a Rewards Object
     *
     * @param loadFile the path to the file to be loaded from
     */
    explicit Rewards(const std::string &loadFile);

    /**
     * Adds a new reward to the database identified by the reward ID
     *
     *  rewards use a product class
     *
     * @param rewardName The name of the reward to be added
     * @param price The amount of points to be redeemed for the reward
     * @param initialStock The amount of items of the reward in stock
     * @return returns the ID of the new reward
     */
    std::string createReward (const std::string &rewardName, int price, int initialStock);

    /**
     * Attempt to find a "price" of a reward identified within the database
     *
     * @param rewardID the identifier of the reward to be checked
     * @return the value of the specified reward, -1 if it does not exist
     */
    int getRewardValue (const std::string &rewardID);

    /**
     *
     */
    void displayAll() override;

    /**
     * Saves the current state of the inventory to the savePath set upon creation of the object
     */
    void save() override;

    // load function is inherited from inventory

  };

inline Rewards::Rewards(const std::string &loadFile): Inventory(loadFile) {
    savePath = loadFile;
}

inline std::string Rewards::createReward(const std::string &rewardName, const int price, const int initialStock) {
    const Product newReward = Product(rewardName, price, initialStock);
    this -> addNew(newReward);
    std::string rewardID = newReward.getID();
    return rewardID;
}

inline int Rewards::getRewardValue(const std::string &rewardID) {
    return this -> getPrice(rewardID); // NOLINT(*-narrowing-conversions)
}

inline void Rewards::displayAll() {
    auto index = container.begin();
    auto end = container.end();
    if (index == end) {
        std::cout << "NO ENTRIES EXIST" << '\n';
    } else {
        int counter = 1;
        while (index != end) {
            std::cout << "Reward " << counter << ": \n";
            std::string output = index->second.toString();
            std::cout << output << '\n';
            ++index;
            ++counter;
        }
    }
}

inline void Rewards::save() {
    std::fstream saveFile;
    saveFile.open(savePath, std::ios::out);
    int indexNumber = 0;
    auto indexPointer = container.begin();
    const auto end = container.end();
    while (indexPointer != end) {
        saveFile << "Reward " << ++indexNumber << ":\n";
        std::string output;
        output += indexPointer->second.toString();
        saveFile << output << '\n';
        ++indexPointer;
    }
    saveFile.close();
}

#endif //REWARDS_H