#ifndef PROGRAMM1_DATAHELPER_H
#define PROGRAMM1_DATAHELPER_H


#include <string>
#include <algorithm>
#include <iostream>

class DataHelper {
public:
    static bool isOnlyNums(std::string &str);
    static bool isLenLess(std::string &str, int size);
    static void formatString(std::string &str);
    static int countNumsSum(std::string &str);
};


#endif //PROGRAMM1_DATAHELPER_H
