#pragma once

#include <string>
#include <cstdint>

class Authenticator {
private:
    std::string saltHex;
    std::string passHash;
    std::string authMsg;

public:
    Authenticator() = default;

    std::string generateSalt();
    std::string calcSHA1(const std::string& inputData);
    std::string prepareAuthMsg(const std::string& login, const std::string& password);

    const std::string& getAuthMsg() const { return authMsg; }
};