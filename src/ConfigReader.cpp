#include "ConfigReader.hpp"
#include "ClientError.hpp"
#include <fstream>
#include <sstream>

ConfigReader::ConfigReader(std::string path) : configFilePath(std::move(path)) {}

void ConfigReader::readCredentials() {
    std::ifstream file(configFilePath);
    if (!file.is_open()) {
        throw ClientError("ConfigReader::readCredentials", "path=" + configFilePath, "IOError", "Failed to open configuration file.");
    }

    std::string line;
    if (std::getline(file, line)) {
        size_t pos = line.find(':');
        if (pos == std::string::npos) {
            throw ClientError("ConfigReader::readCredentials", "line=" + line, "InterfaceError", "Invalid config file format. Expected login:password");
        }
        login = line.substr(0, pos);
        password = line.substr(pos + 1);
    } else {
        throw ClientError("ConfigReader::readCredentials", "path=" + configFilePath, "IOError", "Configuration file is empty.");
    }

    if (login.empty() || password.empty()) {
        throw ClientError("ConfigReader::readCredentials", "login=" + login, "InterfaceError", "Login or password cannot be empty.");
    }
}