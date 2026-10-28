#include "DataReader.hpp"
#include "ClientError.hpp"
#include <fstream>

DataReader::DataReader(std::string path) : inputFilePath(std::move(path)) {}

std::vector<std::vector<uint32_t>> DataReader::readVectors() {
    std::ifstream file(inputFilePath, std::ios::binary);
    if (!file.is_open()) {
        throw ClientError("DataReader::readVectors", "file=" + inputFilePath, "IOError", "Failed to open input data file.");
    }

    uint32_t vectorCount = 0;
    if (!file.read(reinterpret_cast<char*>(&vectorCount), sizeof(vectorCount))) {
        throw ClientError("DataReader::readVectors", "file=" + inputFilePath, "IOError", "Failed to read vector count from file.");
    }

    std::vector<std::vector<uint32_t>> result;
    result.reserve(vectorCount);

    for (uint32_t i = 0; i < vectorCount; ++i) {
        uint32_t vecSize = 0;
        if (!file.read(reinterpret_cast<char*>(&vecSize), sizeof(vecSize))) {
            throw ClientError("DataReader::readVectors", "index=" + std::to_string(i), "IOError", "Failed to read vector size.");
        }

        std::vector<uint32_t> vec(vecSize);
        if (vecSize > 0) {
            if (!file.read(reinterpret_cast<char*>(vec.data()), vecSize * sizeof(uint32_t))) {
                throw ClientError("DataReader::readVectors", "vector_index=" + std::to_string(i) + ", size=" + std::to_string(vecSize), "IOError", "Failed to read vector elements.");
            }
        }
        result.push_back(std::move(vec));
    }

    return result;
}