#ifndef PROGRAM1_SIMPLELOGGER_H
#define PROGRAM1_SIMPLELOGGER_H

#include "DateInfo.h"

#include <sstream>
#include <string>
#include <fstream>
#include <iostream>


class SimpleLogger {
private:
    static std::string logFilePath;
    static std::ofstream fileStream;
public:
    static void initLogger(const std::string &filename);

    static void log(std::string message);

    ~SimpleLogger();
};


#endif //PROGRAM1_SIMPLELOGGER_H
