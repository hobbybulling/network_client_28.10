#include "Client.hpp"
#include "CLIHandler.hpp"
#include "ConfigReader.hpp"
#include "DataReader.hpp"
#include "DataWriter.hpp"
#include "Authenticator.hpp"
#include "Communicator.hpp"

int Client::run(int argc, char** argv) {
    CLIHandler cli;
    cli.parse(argc, argv);

    if (cli.isHelpRequested()) {
        cli.printHelp();
        return 0;
    }

    ConfigReader configReader(cli.getConfigFilePath());
    configReader.readCredentials();

    DataReader dataReader(cli.getInputFilePath());
    auto vectors = dataReader.readVectors();

    Authenticator authenticator;
    std::string authMsg = authenticator.prepareAuthMsg(configReader.getLogin(), configReader.getPassword());

    Communicator communicator(cli.getServerAddress(), cli.getServerPort());
    communicator.connectToServer();
    communicator.authenticate(authMsg);

    auto results = communicator.sendAndReceiveData(vectors);
    communicator.disconnect();

    DataWriter dataWriter(cli.getOutputFilePath());
    dataWriter.writeResults(results);

    return 0;
}