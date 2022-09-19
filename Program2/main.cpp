#include <iostream>
#include <string>

#include "Tcp.h"
#include "DataHelper.h"
#include "SimpleLogger.h"

int main(int argc, char **argv) {

    uint16_t port = 25565;
    if (argc > 1) {
        port = atoi(argv[1]);
    }

    SimpleLogger::initLogger("logger");

    TCPListener server(port);

    try {
        server.initialize();
    }
    catch (const std::exception &ex) {
        std::cout << ex.what() << std::endl;
        SimpleLogger::log(ex.what());
        return 0;
    }

    int received;

    while (true) {

        if (!server.isConnected()) {
            try {
                server.waitForConnection();
            }
            catch (const std::exception &ex) {
                SimpleLogger::log(ex.what());
            }
        }

        if (server.isConnected() && server.receive(reinterpret_cast<uint8_t *>(&received), 4) == 4) {

            if (DataHelper::numLen(received) > 2 && (received % 32 == 0))
                std::cout << "Data recieved: " << received << std::endl;
            else
                std::cout << "Error: The received data must be greater than 2 characters and a multiple of 32"
                          << std::endl;
        }
    }

    return 0;
}
