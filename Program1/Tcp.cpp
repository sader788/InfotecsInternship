#include "Tcp.h"


TCPListener::TCPListener(int port)
        : portNumber(port), inputSocketDescriptor(-1), clientSocketDescriptor(-1), connected(false), initialized(false) {}

void TCPListener::throwEx(const char* funcName) {
    std::string err("Error ");

    err += funcName;
    err += ": ";
    err += strerror(errno);

    throw std::runtime_error(err);
}

void TCPListener::initialize(int backlog) {

    inputSocketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (inputSocketDescriptor < 0) {
        throwEx("socket()");
    }

    sockaddr_in address{};
    bzero((char *) &address, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(portNumber);

    if (bind(inputSocketDescriptor, (struct sockaddr *) &address, sizeof(address)) < 0) {
        throwEx("bind()");
    }

    if (listen(inputSocketDescriptor, backlog) < 0) {
        throwEx("inputSocketDescriptor()");
    }


    initialized = true;
}

void TCPListener::waitForConnection() {
    if (!initialized) {
        throw std::runtime_error("Error: socket is not initialized");
    }

    socklen_t addressLength = sizeof(struct sockaddr_in);
    int oldDescriptor = clientSocketDescriptor;
    clientSocketDescriptor = accept(inputSocketDescriptor, reinterpret_cast<struct sockaddr *>(&remoteAddress),
                                    &addressLength);



    if (clientSocketDescriptor < 0) {
        clientSocketDescriptor = oldDescriptor;

        throwEx("accept()");
    }

    connected = true;
}


int TCPListener::receive(uint8_t *data, size_t length) const {
    if (!connected) {
        return -1;
    }

    return read(clientSocketDescriptor, data, length);
}


int TCPListener::send(const uint8_t *data, size_t length) const {
    if (!connected) {
        return -1;
    }
    return write(clientSocketDescriptor, &data, length);
}

bool TCPListener::isConnected() const {
    return connected;
}

bool TCPListener::isInitialized() const {
    return initialized;
}

TCPListener::~TCPListener() {
    close(inputSocketDescriptor);
}


TCPSender::TCPSender(std::string url, int port)
        : addressUrl(url),
          portNumber(port),
          outputSocketDescriptor(-1),
          connected(false),
          initialized(false) {}

void TCPSender::throwEx(const char* funcName) {
    std::string err("Error ");

    err += funcName;
    err += ": ";
    err += strerror(errno);

    throw std::runtime_error(err);
}

void TCPSender::initialize() {
    close(outputSocketDescriptor);

    outputSocketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (outputSocketDescriptor < 0) {
        throwEx("socket()");
    }

    struct timeval timeout{};
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    if (setsockopt(outputSocketDescriptor, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof timeout) < 0) {
        throwEx("setsockopt()");
    }

    initialized = true;
}

void TCPSender::createConnection() {
    sockaddr_in targetAddress{};
    bzero((char *) &targetAddress, sizeof(targetAddress));
    targetAddress.sin_family = AF_INET;
    targetAddress.sin_port = htons(portNumber);

    struct hostent *hp = gethostbyname(addressUrl.c_str());
    if (!hp) {
        throwEx("gethostbyname()");
    }

    memcpy((void *) &targetAddress.sin_addr, hp->h_addr_list[0], hp->h_length);

    if (connect(outputSocketDescriptor, reinterpret_cast<const sockaddr *>(&targetAddress),
                sizeof(struct sockaddr_in)) < 0) {
        throwEx("connect()");
    }

    connected = true;
}

int TCPSender::receive(uint8_t *data, size_t len) {
    if (!connected) {
        return -1;
    }

    int bytesNum = read(outputSocketDescriptor, data, len);

    if (bytesNum <  0) {
        initialized = false;
        connected = false;
        return -1;
    }

    return bytesNum;
}

int TCPSender::send(const uint8_t *data, size_t len) {
    if (!connected) {
        return -1;
    }

    int bytesNum = write(outputSocketDescriptor, data, len);

    if (bytesNum <  0) {
        initialized = false;
        connected = false;
        return -1;
    }

    return bytesNum;
}

bool TCPSender::isConnected() {
    return connected;
}

bool TCPSender::isInitialized() {
    return initialized;
}

TCPSender::~TCPSender() {
    close(outputSocketDescriptor);
}