#include "DateInfo.h"

std::string DateInfo::getCurrentDate() {
    std::time_t currentTIme = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string currentTimeString;
    try {
        currentTimeString = strtok(std::ctime(&currentTIme), "\n");
    } catch (std::exception &e) {
        currentTimeString = strtok(std::ctime(nullptr), "\n");
    }
    return currentTimeString;
}
