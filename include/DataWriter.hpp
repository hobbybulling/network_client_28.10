#pragma once

#include <string>
#include <vector>
#include <cstdint>

class DataWriter {
private:
    std::string outputFilePath;

public:
    explicit DataWriter(std::string path);
    void writeResults(const std::vector<uint32_t>& results);
};