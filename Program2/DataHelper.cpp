#include "DataHelper.h"

int DataHelper::numLen(int num) {
    int len = 0;

    while (num > 0) {
        num /= 10;
        len += 1;
    }

    return len;
}

