//
// Created by Xander Palermo on 11/19/24.
//

#include <gtest/gtest.h>
#include <include/Transaction.h>

class TransactionTest : public testing::Test {

};

TEST_F(TransactionTest, toString) {
    std::cout << "Working... " << std::endl;
    const std::string string = Transaction::conversionToString();
    std::cout << string;
}