#include <Stepper.h>
#include "InputSystem.hpp"
#include "Steering.hpp"
#include "Engine.hpp"
#include "util.hpp"

  // setup interrupt on pin 2
InputSystem<2> inputPin2 = InputSystem<2>();
InputSystem<3> inputPin3 = InputSystem<3>();
Steering steering = Steering();
Engine engine = Engine(10);

bool engineSpeedWasUp = false;
bool engineSpeedWasDown = false;

void setup()
{
  Serial.begin(115200);


  steering.stepperL.setMaxSpeed(1000.0);
  steering.stepperL.setAcceleration(100.0);
  steering.stepperR.setMaxSpeed(1000.0);
  steering.stepperR.setAcceleration(100.0);

  waitForSignal();
}

void waitForSignal()
{
  while(!(engineSpeedWasDown && engineSpeedWasUp)){
    int pwm = constrain(inputPin3.getPwm(), 1000, 2000);
    float engineSpeed = mapF(pwm, 1000, 2000, -1.0, 1.0);
    
    if(engineSpeed == 1.0)
      engineSpeedWasUp = true;
    if(engineSpeed == -1.0)
      engineSpeedWasDown = true;
  }
}

void loop()
{
  //ENGINE
  // pwm 1024 - 2048
  int pwm = constrain(inputPin3.getPwm(), 1000, 2000);
  float engineSpeed = mapF(pwm, 1000, 2000, -1.0, 1.0);
  
  // dead zone
  if(engineSpeed < 0.05 && engineSpeed > -0.05)
    engineSpeed = 0.0;
  engine.SetSpeed(engineSpeed);
  Serial.println(engineSpeed);

  //STEERING
  float steeringThreshold = 0.05;
  float steeringRangeAbs = abs(inputPin2.getSteeringRange());

  if (steeringRangeAbs > steeringThreshold)
  {
    int speed = constrain(1000 * steeringRangeAbs, 100, 1000);

    if (inputPin2.getSteeringRange() > 0)
    {
      steering.stepperL.setSpeed(speed);
      steering.stepperR.setSpeed(speed);
    }
    else
    {
      steering.stepperL.setSpeed(-speed);
      steering.stepperR.setSpeed(-speed);
    }

    steering.stepperL.runSpeed();
    steering.stepperR.runSpeed();
  }
}
