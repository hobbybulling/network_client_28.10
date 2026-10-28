#pragma once

#include <string>
#include <exception>

class ClientError : public std::exception {
private:
    std::string funcName;
    std::string paramValues;
    std::string errorType;
    std::string message;

public:
    ClientError(std::string func, std::string params, std::string type, std::string msg);
    const char* what() const noexcept override;
    void printDiagnostic() const;
};