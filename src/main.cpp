#include "Client.hpp"
#include "ClientError.hpp"
#include <iostream>

int main(int argc, char** argv) {
    try {
        Client client;
        return client.run(argc, argv);
    } catch (const ClientError& e) {
        e.printDiagnostic();
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Standard Exception: " << e.what() << std::endl;
        return 2;
    } catch (...) {
        std::cerr << "Unknown exception caught!" << std::endl;
        return 3;
    }
}