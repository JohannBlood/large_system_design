#include <iostream>
#include <stdexcept>
#include <gtest/gtest.h>

class TMyException : public std::runtime_error {
public:
    TMyException(const std::string& message) : std::runtime_error(message) {}

    friend std::ostream& operator<<(std::ostream& os, const TMyException& ex) {
        return os << "Custom Exception: " << ex.what();
    }
};

class DerivedException1 : public TMyException {
public:
    DerivedException1(const std::string& message) : TMyException(message) {}
};

class DerivedException2 : public TMyException {
public:
    DerivedException2(const std::string& message) : TMyException(message) {}
};

TEST(CustomExceptionTest, Exception1) {
    EXPECT_THROW(throw DerivedException1("Exception 1 occurred"), TMyException);
}

TEST(CustomExceptionTest, Exception2) {
    EXPECT_THROW(throw DerivedException2("Exception 2 occurred"), TMyException);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
