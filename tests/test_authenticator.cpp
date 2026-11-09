#include <UnitTest++/UnitTest++.h>
#include "Authenticator.hpp"
#include <string>

TEST(GenerateSaltLengthAndFormat) {
    Authenticator auth;
    std::string salt = auth.generateSalt();
    CHECK_EQUAL(16, salt.length());
    for (char c : salt) {
        CHECK((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F'));
    }
}

TEST(CalcSHA1KnownVector) {
    Authenticator auth;
    std::string input = "A1B2C3D4E5F60708password";
    std::string expected = "0C06E183E6A5180B4272533AF832327B84F7BC6E"; 
    CHECK_EQUAL(expected, auth.calcSHA1(input));
}

TEST(PrepareAuthMsgStructure) {
    Authenticator auth;
    std::string msg = auth.prepareAuthMsg("user1", "pass123");
    CHECK_EQUAL(61, msg.length());
    CHECK_EQUAL("user1", msg.substr(0, 5));
}