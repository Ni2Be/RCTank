#ifndef ENGINEHPP
#define ENGINEHPP
#include "util.hpp"

class Engine
{
private:
    const int min = 125;
    const int deadZoneLow = 180;
    const int deadZoneHigh = 200;
    const int max = 255;
    const int deadZoneMid = deadZoneLow + (deadZoneHigh - deadZoneLow) / 2;
    int pwmPin;

public:
    Engine(int pwmPin) : pwmPin(pwmPin)
    {
        pinMode(pwmPin, OUTPUT); // sets the pin as output
    }

    //
    void Accelerate()
    {
    }

    // -1.0 to 1.0
    void SetSpeed(float speed)
    {
        //180 - 200 dead
        //125 - 255
        if (speed < 0.0)
        {
            int analogMotorInput = mapF(abs(speed), 0.0, 1.0, deadZoneLow, min);
            analogWrite(pwmPin, analogMotorInput);
        }
        else if (speed > 0.0)
        {
            int analogMotorInput = mapF(speed, 0.0, 1.0, deadZoneHigh, max);
            analogWrite(pwmPin, analogMotorInput);
        }
        else
        {
            analogWrite(pwmPin, deadZoneMid);
        }
    }
};
#endif
