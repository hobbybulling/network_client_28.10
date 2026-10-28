#pragma once

#include <string>
#include <vector>
#include <cstdint>

class DataReader {
private:
    std::string inputFilePath;

public:
    explicit DataReader(std::string path);
    std::vector<std::vector<uint32_t>> readVectors();
};