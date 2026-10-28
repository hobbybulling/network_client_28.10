#include "Authenticator.hpp"
#include "ClientError.hpp"
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <cryptopp/osrng.h>
#include <cryptopp/filters.h>
#include <iomanip>
#include <sstream>

std::string Authenticator::generateSalt() {
    CryptoPP::AutoSeededRandomPool prng;
    CryptoPP::byte salt[8];
    prng.GenerateBlock(salt, sizeof(salt));

    std::string encoded;
    CryptoPP::ArraySource(salt, sizeof(salt), true,
        new CryptoPP::HexEncoder(
            new CryptoPP::StringSink(encoded)
        )
    );

    if (encoded.length() < 16) {
        encoded = std::string(16 - encoded.length(), '0') + encoded;
    }
    return encoded;
}

std::string Authenticator::calcSHA1(const std::string& inputData) {
    CryptoPP::SHA1 sha1;
    std::string digest;

    CryptoPP::StringSource(inputData, true,
        new CryptoPP::HashFilter(sha1,
            new CryptoPP::HexEncoder(
                new CryptoPP::StringSink(digest),
                false
            )
        )
    );
    return digest;
}

std::string Authenticator::prepareAuthMsg(const std::string& login, const std::string& password) {
    saltHex = generateSalt();
    std::string saltPass = saltHex + password;
    passHash = calcSHA1(saltPass);

    authMsg = login + saltHex + passHash;
    return authMsg;
}