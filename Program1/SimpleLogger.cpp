#include "SimpleLogger.h"

std::string SimpleLogger::logFilePath;
std::ofstream SimpleLogger::fileStream;

void SimpleLogger::initLogger(const std::string &filepath) {
    logFilePath = filepath;
    fileStream = std::ofstream(logFilePath, std::ios_base::app);

}

void SimpleLogger::log(std::string message) {
    if (message.empty()) {
        return;
    }

    std::stringstream loggerStringStream;
    loggerStringStream << "[" << DateInfo::getCurrentDate() << "] " << message;

    if (!fileStream.is_open()) {
        return;
    }

    fileStream << loggerStringStream.str() << std::endl;
}

SimpleLogger::~SimpleLogger() {
    fileStream.close();
}
