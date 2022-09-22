#include <iostream>
#include <thread>
#include <string>
#include <signal.h>
#include <queue>

#include "SharedBuffer.h"
#include "DataHelper.h"
#include "Tcp.h"
#include "SimpleLogger.h"


int main(int argc, char **argv) {

    uint16_t port = 25565;
    std::string address("localhost");

    if(argc > 1) {
        address = argv[1];
    }
    if(argc > 2) {
        port = atoi(argv[2]);
    }

    SimpleLogger::initLogger("logger");

    signal(SIGPIPE, SIG_IGN);

    SharedBuffer sh;

    std::thread t1([&sh]() {
        std::string input;
        while (true) {
            std::getline(std::cin, input);

            if (DataHelper::isLenLess(input, 64) && DataHelper::isOnlyNums(input)) {
                DataHelper::formatString(input);
                sh.writeBuffer(input);
            } else {
                std::cout << "data is not correct" << std::endl;
            }
        }
    });

    std::thread t2([&sh, &address, &port]() {

        std::queue<int> queryToSend;

        TCPSender client(address, port);

        try {
            client.initialize();
            client.createConnection();
        }
        catch (const std::exception &ex) {
            SimpleLogger::log(ex.what());
        }

        while (true) {

            std::string data = sh.readBuffer();

            if (data.size() != 0) {
                std::cout << data << "\n";

                queryToSend.push(DataHelper::countNumsSum(data));
            }

            while (queryToSend.size() != 0) {
                if (client.send(reinterpret_cast<const uint8_t *> (&queryToSend.front()), 4) < 0) {

                    if (!client.isInitialized())
                        client.initialize();

                    try {
                        client.createConnection();
                    }
                    catch (const std::exception &ex) {
                        SimpleLogger::log(ex.what());
                        break;
                    }
                } else {
                    queryToSend.pop();
                }
            }
        }
    });

    t1.join();
    t2.join();


    return 0;
}
