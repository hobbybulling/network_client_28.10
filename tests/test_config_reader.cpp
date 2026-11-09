#include <UnitTest++/UnitTest++.h>
#include "ConfigReader.hpp"
#include "ClientError.hpp"
#include <fstream>
#include <cstdio>

const char* CONFIG_FILE = "test_config.conf";

struct ConfigFixture {
    ConfigFixture() { std::remove(CONFIG_FILE); }
    ~ConfigFixture() { std::remove(CONFIG_FILE); }
};

TEST_FIXTURE(ConfigFixture, ReadValidCredentials) {
    std::ofstream out(CONFIG_FILE);
    out << "user:P@ssW0rd\n";
    out.close();

    ConfigReader reader(CONFIG_FILE);
    reader.readCredentials();
    CHECK_EQUAL("user", reader.getLogin());
    CHECK_EQUAL("P@ssW0rd", reader.getPassword());
}

TEST_FIXTURE(ConfigFixture, MissingFileThrows) {
    ConfigReader reader("nonexistent_file.conf");
    CHECK_THROW(reader.readCredentials(), ClientError);
}

TEST_FIXTURE(ConfigFixture, InvalidFormatThrows) {
    std::ofstream out(CONFIG_FILE);
    out << "no_colon_here\n";
    out.close();

    ConfigReader reader(CONFIG_FILE);
    CHECK_THROW(reader.readCredentials(), ClientError);
}