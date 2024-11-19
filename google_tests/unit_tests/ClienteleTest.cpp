#include "gtest/gtest.h"
#include "include/Clientele.h"

class ClienteleTest : public testing::Test {
protected:
    void SetUp() override {
        clientele = new Clientele(DEFAULT_CLIENTELE_SAVE_PATH);
    }

    void TearDown() override {
        delete clientele;
    }

    Clientele *clientele = nullptr;
};

void fill(Clientele &clientele) {
    for (int i = 1; i <= 5; i++) {
        std::string username = "U12" + std::to_string(i) + "TESTER";
        std::string cardNum = "1234-5678-901" + std::to_string(i);
        clientele.registerCustomer(username, "TEST", "USER", 50, cardNum);
    }
}

TEST_F(ClienteleTest, registerCustomer) {
    EXPECT_NO_THROW(clientele -> registerCustomer("U123ABCDEF", "Test", "Name", 30,"1234-5678-9012"));
    EXPECT_FALSE(clientele -> empty());

    EXPECT_NO_THROW(clientele -> registerCustomer("U555tester", "TEST", "USER", 40, "5555-5555-5555"));

    EXPECT_THROW(clientele -> registerCustomer("U12TESTER","Test","Name",30,"1234-5678-9012"), std::invalid_argument);
    EXPECT_THROW(clientele -> registerCustomer("U1234TESTER","Test","Name",30,"1234-5678-9012"), std::invalid_argument);
    EXPECT_THROW(clientele -> registerCustomer("U124TESTERTESTER","Test","Name",30,"1234-5678-9012"), std::invalid_argument);
}

TEST_F(ClienteleTest, fill) {
    fill(*clientele);
    EXPECT_FALSE(clientele->empty());
}

TEST_F(ClienteleTest, findUser) {
    fill(*clientele);
    EXPECT_FALSE(clientele->empty());
    for (int i = 1; i <= 5; i++) {
        std::string username = "U12" + std::to_string(i) + "TESTER";
        const std::string customerID = clientele->findUser(username);
        const bool customerFound = !customerID.empty();
        EXPECT_TRUE(customerFound);
    }
    for (int i = 6; i <= 9; i++) {
        std::string username = "U12" + std::to_string(i) + "TESTER";
        const std::string customerID = clientele->findUser(username);
        const bool customerFound = !customerID.empty();
        EXPECT_FALSE(customerFound);
    }
}