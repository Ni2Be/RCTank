#ifndef INPUTSYSTWM_H
#define INPUTSYSTWM_H

template<int Pin>
class InputSystem
{
private:
  const int pwmMin = 1000;
  const int pwmMax = 2000;

  volatile int pwm_value = 0;
  volatile int prev_time = 0;

  static InputSystem<Pin>* inputSystem;

  void rising()
  {
    this->prev_time = micros();
  }
  void falling()
  {
    this->pwm_value = micros() - this->prev_time;
  }

  static void interruptRisingHandle()
  {
    InputSystem::inputSystem->rising();
    attachInterrupt(digitalPinToInterrupt(Pin), interruptFallingHandle, FALLING);
  }

  static void interruptFallingHandle()
  {
    InputSystem::inputSystem->falling();
    attachInterrupt(digitalPinToInterrupt(Pin), interruptRisingHandle, RISING);
  }
public:
  InputSystem()
  {
    inputSystem = this;
    attachInterrupt(digitalPinToInterrupt(Pin), interruptRisingHandle, RISING);
  }

  int getPwm()
  {
    return pwm_value;
  }

  // Returns the current steering on a range from -1 to 1
  float getSteeringRange()
  {
    return constrain(((pwm_value - pwmMin) / (float)(pwmMax - pwmMin)) * 2.0 - 1.0, -1.0, 1.0);
  }

};

template<int Pin>
InputSystem<Pin>* InputSystem<Pin>::inputSystem = nullptr;

#endif