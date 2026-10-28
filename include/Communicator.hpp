#pragma once

#include <string>
#include <vector>
#include <cstdint>

class Communicator {
private:
    std::string serverAddress;
    uint16_t serverPort;
    int socketFd;

public:
    Communicator(std::string address, uint16_t port);
    ~Communicator();

    void connectToServer();
    void authenticate(const std::string& authMsg);
    std::vector<uint32_t> sendAndReceiveData(const std::vector<std::vector<uint32_t>>& vectors);
    void disconnect();
};