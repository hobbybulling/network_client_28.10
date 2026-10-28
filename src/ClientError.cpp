#include "ClientError.hpp"
#include <iostream>

ClientError::ClientError(std::string func, std::string params, std::string type, std::string msg)
    : funcName(std::move(func)), paramValues(std::move(params)), errorType(std::move(type)), message(std::move(msg)) {}

const char* ClientError::what() const noexcept {
    return message.c_str();
}

void ClientError::printDiagnostic() const {
    std::cerr << "=== Client Error Diagnostic ===" << std::endl;
    std::cerr << "Function: " << funcName << std::endl;
    std::cerr << "Parameters/Variables: " << paramValues << std::endl;
    std::cerr << "Error Type: " << errorType << std::endl;
    std::cerr << "Details: " << message << std::endl;
}