#ifndef PROGRAM_TCP_H
#define PROGRAM_TCP_H


#include <ostream>
#include <iostream>
#include <unistd.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string>
#include <cstring>
#include <exception>

class TCPListener {

private:
    int portNumber;
    struct sockaddr_in remoteAddress;
    int inputSocketDescriptor;
    int clientSocketDescriptor;
    bool connected;
    bool initialized;

    void throwEx(const char* funcName);
public:
    TCPListener(int port);

    void initialize(int backlog = 1);

    void waitForConnection();

    int receive(uint8_t *data, size_t length);

    int send(const uint8_t *data, size_t length);

    bool isConnected() const;

    bool isInitialized() const;

    ~TCPListener();
};

class TCPSender {
private:
    std::string addressUrl;
    int portNumber;
    struct sockaddr_in remoteAddress;
    int outputSocketDescriptor;
    bool connected;
    bool initialized;

    void throwEx(const char* funcName);

public:
    TCPSender(std::string url, int port);

    void initialize();

    void createConnection();

    int receive(uint8_t *data, size_t len);

    int send(const uint8_t *data, size_t len);

    bool isConnected() const;

    bool isInitialized() const;

    ~TCPSender();
};

#endif //PROGRAM_TCP_H
