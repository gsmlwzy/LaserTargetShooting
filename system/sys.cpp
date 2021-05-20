#include "sys.h"

int32_t MySystem::cnt = 0;
float MySystem::speed = 0.0f;
float MySystem::angle = 0.0f;
float MySystem::goal = 45.f;
PIDControl MySystem::pid1(0.038f, 0.0f, 0.1F);

// PIDControl MySystem::pid2(0.5f, 0.0f, 8.6f);
PIDControl MySystem::pid2(2.f, 0.0f, 33.5f);

void MySystem::Init(void)
{
	attachInterrupt(2, MySystem::InterruptFormB, CHANGE);
	attachInterrupt(3, MySystem::InterruptFormA, CHANGE);
	analogWrite(2, 0);
	analogWrite(3, 0);
}

void MySystem::InterruptFormA()
{
	switch (PIND & 0X03)
	{
	case 0b11:
	case 0b00:
		MySystem::cnt--;
		break;
	case 0b01:
	case 0B10:
		MySystem::cnt++;
		break;
	default:
		break;
	}
}

void MySystem::InterruptFormB()
{
	switch (PIND & 0X03)
	{
	case 0b11:
	case 0b00:
		MySystem::cnt++;
		break;
	case 0b01:
	case 0B10:
		MySystem::cnt--;
		break;
	default:
		break;
	}
}

float out2;
void MySystem::CalStatus(void)
{
	static int32_t lastcnt = 0;
	MySystem::speed = (MySystem::cnt - lastcnt) * 360.0f / 897.6f / 0.010f;
	MySystem::angle = MySystem::cnt / 897.6f * 360.f;
	lastcnt = MySystem::cnt;

	MySystem::pid2.run(MySystem::angle, MySystem::goal + 45.f, out2);
	MySystem::GeneratePWM((int32_t)out2);
}

void MySystem::GeneratePWM(int32_t delta_width)
{
	static int32_t lastwidth = 0;
	static int32_t lim = 5;
	static int32_t lim_max = 100;
	auto width = lastwidth + delta_width;

	if (width >= lim_max)
	{
		width = lim_max;
	}
	else if (width <= -lim_max)
	{
		width = -lim_max;
	}

	if (width > lim)
	{
		analogWrite(2, width);
		analogWrite(3, 0);
	}
	else if (width < -lim)
	{
		analogWrite(2, 0);
		analogWrite(3, -width);
	}
	else if (width > 5 && width <= lim)
	{
		analogWrite(2, lim);
		analogWrite(3, 0);
	}
	else if (width < -5 && width >= -lim)
	{
		analogWrite(2, 0);
		analogWrite(3, lim);
	}
	else
	{
		analogWrite(2, 0);
		analogWrite(3, 0);
	}
	lastwidth = width;
}
