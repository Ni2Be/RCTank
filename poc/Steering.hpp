#ifndef STEERING_H
#define STEERING_H

#include <AccelStepper.h>
#include <MultiStepper.h>

class Steering {
    public:
    AccelStepper stepperL;
    AccelStepper stepperR;

    Steering() : 
        stepperL(AccelStepper::DRIVER, 4, 7), 
        stepperR(AccelStepper::DRIVER, 12, 13)
    {}

};
#endif
