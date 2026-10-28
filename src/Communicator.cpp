#include "Communicator.hpp"
#include "ClientError.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <errno.h>

Communicator::Communicator(std::string address, uint16_t port)
    : serverAddress(std::move(address)), serverPort(port), socketFd(-1) {}

Communicator::~Communicator() {
    disconnect();
}

void Communicator::connectToServer() {
    socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFd == -1) {
        throw ClientError("Communicator::connectToServer", "socket() failed", "NetworkError", std::strerror(errno));
    }

    struct timeval timeout{180, 0};
    setsockopt(socketFd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));

    sockaddr_in serv_addr{};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(serverPort);
    if (inet_pton(AF_INET, serverAddress.c_str(), &serv_addr.sin_addr) <= 0) {
        throw ClientError("Communicator::connectToServer", "address=" + serverAddress, "NetworkError", "Invalid IP address format.");
    }

    if (connect(socketFd, reinterpret_cast<sockaddr*>(&serv_addr), sizeof(serv_addr)) == -1) {
        throw ClientError("Communicator::connectToServer", "port=" + std::to_string(serverPort), "NetworkError", std::strerror(errno));
    }
}

void Communicator::authenticate(const std::string& authMsg) {
    ssize_t sent = send(socketFd, authMsg.c_str(), authMsg.length(), 0);
    if (sent == -1) {
        throw ClientError("Communicator::authenticate", "authMsg length=" + std::to_string(authMsg.length()), "AuthError", std::strerror(errno));
    }

    char response[256];
    std::memset(response, 0, sizeof(response));
    ssize_t received = recv(socketFd, response, sizeof(response) - 1, 0);
    if (received <= 0) {
        throw ClientError("Communicator::authenticate", "recv() failed", "AuthError", "Server disconnected or failed to respond during authentication.");
    }

    std::string respStr(response, received);
    if (respStr.rfind("OK", 0) == std::string::npos) {
        throw ClientError("Communicator::authenticate", "response=" + respStr, "AuthError", "Authentication failed by server.");
    }
}

std::vector<uint32_t> Communicator::sendAndReceiveData(const std::vector<std::vector<uint32_t>>& vectors) {
    uint32_t vecCount = static_cast<uint32_t>(vectors.size());
    if (send(socketFd, &vecCount, sizeof(vecCount), 0) == -1) {
        throw ClientError("Communicator::sendAndReceiveData", "vecCount=" + std::to_string(vecCount), "NetworkError", std::strerror(errno));
    }

    std::vector<uint32_t> results;
    results.reserve(vecCount);

    for (size_t i = 0; i < vectors.size(); ++i) {
        uint32_t size = static_cast<uint32_t>(vectors[i].size());
        if (send(socketFd, &size, sizeof(size), 0) == -1) {
            throw ClientError("Communicator::sendAndReceiveData", "vector_index=" + std::to_string(i), "NetworkError", std::strerror(errno));
        }

        if (size > 0) {
            if (send(socketFd, vectors[i].data(), size * sizeof(uint32_t), 0) == -1) {
                throw ClientError("Communicator::sendAndReceiveData", "vector_index=" + std::to_string(i), "NetworkError", std::strerror(errno));
            }
        }

        uint32_t resVal = 0;
        ssize_t recvBytes = recv(socketFd, &resVal, sizeof(resVal), MSG_WAITALL);
        if (recvBytes != sizeof(resVal)) {
            throw ClientError("Communicator::sendAndReceiveData", "vector_index=" + std::to_string(i), "NetworkError", "Failed to receive calculation result from server.");
        }
        results.push_back(resVal);
    }

    return results;
}

void Communicator::disconnect() {
    if (socketFd != -1) {
        close(socketFd);
        socketFd = -1;
    }
}