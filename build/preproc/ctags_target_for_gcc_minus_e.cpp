# 1 "g:\\Arduino\\LaserTargetShooting\\motor.ino"
# 2 "g:\\Arduino\\LaserTargetShooting\\motor.ino" 2
# 3 "g:\\Arduino\\LaserTargetShooting\\motor.ino" 2


void setup()
{
 // put your setup code here, to run once:
 MySystem::Init();
 Serial.begin(115200);
 MsTimer2::set(10, MySystem::CalStatus);
 MsTimer2::start();

}


extern float out2;
int32_t cnt = 0;
void loop()
{
 // put your main code here, to run repeatedly:
 if (fabs(MySystem::goal + 45.f - MySystem::angle) <= 3.f)
 {
  if(cnt >= 100){
   MySystem::goal *= -1;
   MySystem::pid2.clean();
   cnt = 0;
  }
  cnt++;
 }
 else
 {
  cnt = 0;
 }

 Serial.print(MySystem::angle);
 // Serial.print(", ");
 // Serial.print(out2);
 Serial.print("\r\n");
 delay(10);
}
