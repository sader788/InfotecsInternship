#include "SharedBuffer.h"

SharedBuffer::SharedBuffer() {

}

void SharedBuffer::writeBuffer(const std::string &userInput) {

    sharedLock.lock();
    data.emplace(userInput);
    sharedLock.unlock();
    cv.notify_all();
}

std::string SharedBuffer::readBuffer() {

    auto const timeout = std::chrono::steady_clock::now() + std::chrono::seconds(10);
    std::string result;

    std::unique_lock<std::mutex> lock(sharedLock);

    if (cv.wait_until(lock, timeout) == std::cv_status::timeout || data.empty()) {
        return result;
        // No data
    }

    result = data.front();
    data.pop();

    return result;
}