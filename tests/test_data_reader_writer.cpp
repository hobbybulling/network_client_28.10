#include <UnitTest++/UnitTest++.h>
#include "DataReader.hpp"
#include "DataWriter.hpp"
#include "ClientError.hpp"
#include <vector>
#include <cstdio>

const char* TEST_FILE = "test_data.bin";

struct TempFileFixture {
    TempFileFixture() { std::remove(TEST_FILE); }
    ~TempFileFixture() { std::remove(TEST_FILE); }
};

TEST_FIXTURE(TempFileFixture, ReadEmptyFileThrows) {
    DataReader reader(TEST_FILE);
    CHECK_THROW(reader.readVectors(), ClientError);
}

TEST_FIXTURE(TempFileFixture, WriteThenReadValidData) {
    std::vector<uint32_t> results = {10, 20, 30};
    DataWriter writer(TEST_FILE);
    writer.writeResults(results);
}