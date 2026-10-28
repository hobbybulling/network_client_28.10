#pragma once

#include <string>

class ConfigReader {
private:
    std::string configFilePath;
    std::string login;
    std::string password;

public:
    explicit ConfigReader(std::string path);
    void readCredentials();

    const std::string& getLogin() const { return login; }
    const std::string& getPassword() const { return password; }
};