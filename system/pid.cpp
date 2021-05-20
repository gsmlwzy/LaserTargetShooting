#include "pid.h"

/**
  * @brief  Initializes the PIDControl instantiation.
  * @description: This should be called at least once before any other PID functions are called on the instantiation.
  * @param	
  * kp - Positive P gain constant value.
  * ki - Positive I gain constant value.
  * kd - Positive D gain constant value.
  * @retval null
  */
PIDControl::PIDControl(float kp, float ki, float kd)
: Kp(kp), Ki(ki), Kd(kd)
{

}


/**
  * @brief  PID run
  * @description: 
  * @param	
  * @retval null
  */
void PIDControl::run(float current, float target, float &out)
{
    float error, dInput;

    this->setpoint = target; // 设置目标值
    this->input = current;   // 输入当前值

    error = this->setpoint - this->input;
    iTerm += Ki * error;

    dInput = this->input - this->lastInput;
    this->output = Kp * error + iTerm - Kd * dInput;

    this->lastInput = this->input;
    out = this->output;
}

void PIDControl::clean() {
    this->input = 0;
    this->setpoint= 0;
    this->output= 0;
    this->lastInput= 0;
    this->iTerm= 0;
}
