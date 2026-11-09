#include <UnitTest++/UnitTest++.h>
#include "CLIHandler.hpp"
#include "ClientError.hpp"

TEST(HelpFlag) {
    CLIHandler cli;
    const char* argv[] = {"client", "-h", nullptr};
    cli.parse(2, const_cast<char**>(argv));
    CHECK(cli.isHelpRequested());
}

TEST(ValidArgsWithDefaultPort) {
    CLIHandler cli;
    const char* argv[] = {"client", "-a", "127.0.0.1", "-i", "in.bin", "-o", "out.bin", nullptr};
    cli.parse(7, const_cast<char**>(argv));
    CHECK_EQUAL("127.0.0.1", cli.getServerAddress());
    CHECK_EQUAL(33333, cli.getServerPort());
    CHECK_EQUAL("in.bin", cli.getInputFilePath());
    CHECK_EQUAL("out.bin", cli.getOutputFilePath());
}

TEST(MissingMandatoryArgsThrows) {
    CLIHandler cli;
    const char* argv[] = {"client", "-a", "127.0.0.1", nullptr};
    CHECK_THROW(cli.parse(3, const_cast<char**>(argv)), ClientError);
}