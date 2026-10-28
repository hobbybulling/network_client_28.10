#pragma once

#include <string>
#include <cstdint>

class CLIHandler {
private:
    std::string serverAddress;
    uint16_t serverPort;
    std::string inputFilePath;
    std::string outputFilePath;
    std::string configFilePath;
    bool helpRequested;

public:
    CLIHandler();
    void parse(int argc, char** argv);
    void printHelp() const;

    const std::string& getServerAddress() const { return serverAddress; }
    uint16_t getServerPort() const { return serverPort; }
    const std::string& getInputFilePath() const { return inputFilePath; }
    const std::string& getOutputFilePath() const { return outputFilePath; }
    const std::string& getConfigFilePath() const { return configFilePath; }
    bool isHelpRequested() const { return helpRequested; }
};