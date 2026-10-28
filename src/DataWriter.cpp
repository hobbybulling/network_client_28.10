#include "DataWriter.hpp"
#include "ClientError.hpp"
#include <fstream>

DataWriter::DataWriter(std::string path) : outputFilePath(std::move(path)) {}

void DataWriter::writeResults(const std::vector<uint32_t>& results) {
    std::ofstream file(outputFilePath, std::ios::binary);
    if (!file.is_open()) {
        throw ClientError("DataWriter::writeResults", "file=" + outputFilePath, "IOError", "Failed to open output results file.");
    }

    uint32_t count = static_cast<uint32_t>(results.size());
    if (!file.write(reinterpret_cast<const char*>(&count), sizeof(count))) {
        throw ClientError("DataWriter::writeResults", "count=" + std::to_string(count), "IOError", "Failed to write results count.");
    }

    if (count > 0) {
        if (!file.write(reinterpret_cast<const char*>(results.data()), count * sizeof(uint32_t))) {
            throw ClientError("DataWriter::writeResults", "count=" + std::to_string(count), "IOError", "Failed to write results data.");
        }
    }
}