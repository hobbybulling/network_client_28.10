#include "CLIHandler.hpp"
#include "ClientError.hpp"
#include <iostream>
#include <getopt.h>
#include <cstdlib>

CLIHandler::CLIHandler()
    : serverPort(33333), configFilePath("~/.config/vclient.conf"), helpRequested(false) {}

void CLIHandler::parse(int argc, char** argv) {
    if (argc <= 1) {
        helpRequested = true;
        return;
    }

    const struct option long_opts[] = {
        {"address", required_argument, nullptr, 'a'},
        {"port", required_argument, nullptr, 'p'},
        {"input", required_argument, nullptr, 'i'},
        {"output", required_argument, nullptr, 'o'},
        {"config", required_argument, nullptr, 'c'},
        {"help", no_argument, nullptr, 'h'},
        {nullptr, 0, nullptr, 0}
    };

    int opt;
    bool addr_set = false;
    bool input_set = false;
    bool output_set = false;

    opterr = 0;
    while ((opt = getopt_long(argc, argv, "a:p:i:o:c:h", long_opts, nullptr)) != -1) {
        switch (opt) {
            case 'a':
                serverAddress = optarg;
                addr_set = true;
                break;
            case 'p':
                serverPort = static_cast<uint16_t>(std::stoi(optarg));
                break;
            case 'i':
                inputFilePath = optarg;
                input_set = true;
                break;
            case 'o':
                outputFilePath = optarg;
                output_set = true;
                break;
            case 'c':
                configFilePath = optarg;
                break;
            case 'h':
                helpRequested = true;
                return;
            default:
                throw ClientError("CLIHandler::parse", "arg: " + std::string(argv[optind - 1]), "InterfaceError", "Unknown or invalid command line option.");
        }
    }

    if (helpRequested) {
        return;
    }

    if (!addr_set || !input_set || !output_set) {
        throw ClientError("CLIHandler::parse", "address=" + serverAddress + ", input=" + inputFilePath + ", output=" + outputFilePath, "InterfaceError", "Missing mandatory parameters (-a, -i, -o).");
    }
}

void CLIHandler::printHelp() const {
    std::cout << "Usage: client -a <address> -i <input_file> -o <output_file> [-p <port>] [-c <config_file>] [-h]\n";
    std::cout << "Options:\n";
    std::cout << "  -a, --address   Server IP address (required)\n";
    std::cout << "  -p, --port      Server port (default: 33333)\n";
    std::cout << "  -i, --input     Input binary file with vectors (required)\n";
    std::cout << "  -o, --output    Output binary file for results (required)\n";
    std::cout << "  -c, --config    Path to config file containing login and password (default: ~/.config/vclient.conf)\n";
    std::cout << "  -h, --help      Show this help message\n";
}