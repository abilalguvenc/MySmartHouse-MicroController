#include <Arduino.h>

namespace MyTime
{
    int second;
    bool isOneSecondPassed()
    {
        int new_second = millis()/1000;
        if (new_second>second)
        {
            second = new_second;
            return true;
        }
        return false;
    }
}