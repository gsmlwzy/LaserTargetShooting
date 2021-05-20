#include "Arduino.h"
#include "pid.h"
#include "stdint.h"

extern int32_t cnt;
namespace MySystem
{
	extern int32_t cnt;
	extern float speed;
	extern float angle;
	extern PIDControl pid1;
	extern PIDControl pid2;
	extern float goal;

	void Init();
	// 系统级别的任务
	void InterruptFormA();
	void InterruptFormB();
	void CalStatus();
	void GeneratePWM(int32_t width);

	// 用户级别的任务
	void SpeedPidRun();
	void AnglePidRun();
}
