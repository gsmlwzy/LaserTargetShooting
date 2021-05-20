#ifndef __PID__H
#define __PID__H

class PIDControl
{
public:
	PIDControl(float kp, float ki, float kd);

	void run(float current, float target, float &out);
    void clean(void);
	float Kp;
	float Ki;
	float Kd;

private:
	float input;	// 当前值
	float setpoint;	// 目标值
	float output;	// 输出值
	float lastInput;	// 上次
	float iTerm;	// 积分项

};

#endif
