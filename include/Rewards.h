//
// Created by Xander Palermo on 11/14/24.
//

#ifndef REWARDS_H
#define REWARDS_H
#include "Inventory.h"
#include "Product.h"

#endif //REWARDS_H

const std::string DEFAULT_REWARDS_SAVE_PATH = "./resources/rewards.txt";

class Rewards final : public Inventory {
private:

    std::string savePath;

public:

    explicit Rewards(const std::string &loadFile);

    ~Rewards() override = default;

    std::string createReward (const std::string &rewardName, int price, int initialStock);

    int getRewardValue (const std::string &rewardID);

    void displayAll() override;

    void save() override;

  };

inline Rewards::Rewards(const std::string &loadFile): Inventory(loadFile) {
    savePath = loadFile;
}

inline std::string Rewards::createReward(const std::string &rewardName, int price, int initialStock) {
    const Product newReward = Product(rewardName, price, initialStock);
    this -> addNew(newReward);
    std::string rewardID = newReward.getID();
    return rewardID;
}

inline int Rewards::getRewardValue(const std::string &rewardID) {
    return this -> getPrice(rewardID);
}

inline void Rewards::displayAll() {
    auto index = container.begin();
    auto end = container.end();
    if (index == end) {
        std::cout << "NO ENTRIES EXIST" << '\n';
    } else {
        int counter = 1;
        while (index != end) {
            std::cout << "Product " << counter << ": \n";
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




