#include "DataHelper.h"


bool DataHelper::isOnlyNums(std::string &str) {
    bool numChecker = true;

    for (const auto ch : str){
        if (ch < '0' || ch > '9'){
            numChecker = false;
            break;
        }
    }

    return numChecker;
}

bool DataHelper::isLenLess(std::string &str, int len)  {
    return str.length() <= len;
}

void DataHelper::formatString(std::string &str) {
    std::sort(str.begin(), str.end(), std::greater<char>());

    int i = 0;

    while(str[i] != '\0'){
        if(str[i] % 2 == 0){
            str.erase(str.begin()+i);
            str.insert(i, "RnD");
            i += 2;
        }
        i += 1;
    }
}


int DataHelper::countNumsSum(std::string &str) {
    int sum = 0;

    for (const auto ch : str){
        if (ch >= '0' && ch <= '9'){
            sum += ch - '0';
        }
    }

    return sum;
}