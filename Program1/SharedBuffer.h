#ifndef PROGRAMM1_SHAREDBUFFER_H
#define PROGRAMM1_SHAREDBUFFER_H


#include <vector>
#include <mutex>
#include <condition_variable>
#include <queue>

class SharedBuffer {
private:

    std::queue<std::string> data;

    std::mutex sharedLock;

    std::condition_variable cv;
public:

    SharedBuffer();

    void writeBuffer(const std::string &userInput);

    std::string readBuffer();


};


#endif //PROGRAMM1_SHAREDBUFFER_H
