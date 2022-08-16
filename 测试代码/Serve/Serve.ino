#define servo 5
#define Trig 15
#define Echo  4

#define RBIN2 12
#define RPWMB 13
#define RBIN1 14
#define RAIN2 25
#define RAIN1 26
#define RSTBY 27
#define RPWMA 33
#define KEY 19
int distance=0;
int left_distance=0;
int right_distance=0;
hw_timer_t *timer=NULL;//创建一个定时器结构体
void carinit()
{
  pinMode(servo,OUTPUT);
  pinMode(Trig,OUTPUT);
  pinMode(Echo,INPUT);
  pinMode(RSTBY,OUTPUT);
  pinMode(RPWMA,OUTPUT);
  pinMode(RPWMB,OUTPUT);
  pinMode(RAIN1,OUTPUT);
  pinMode(RAIN2,OUTPUT);
  pinMode(RBIN1,OUTPUT);
  pinMode(RBIN2,OUTPUT); 
//  pinMode(KEY,OUTPUT); 
}
void Before()
{
  digitalWrite(RSTBY,HIGH);
  digitalWrite(RPWMA,HIGH);
  digitalWrite(RPWMB,HIGH);
  digitalWrite(RAIN1,HIGH);
  digitalWrite(RAIN2,LOW);
  digitalWrite(RBIN1,LOW);
  digitalWrite(RBIN2,HIGH);
}
void Left()
{
  digitalWrite(RSTBY,HIGH);
  digitalWrite(RPWMA,HIGH);
  digitalWrite(RPWMB,HIGH);
  digitalWrite(RAIN1,LOW);
  digitalWrite(RAIN2,HIGH);
  digitalWrite(RBIN1,LOW);
  digitalWrite(RBIN2,HIGH);
}
void Right()
{
  digitalWrite(RSTBY,HIGH);
  digitalWrite(RPWMA,HIGH);
  digitalWrite(RPWMB,HIGH);
  digitalWrite(RAIN1,HIGH);
  digitalWrite(RAIN2,LOW);
  digitalWrite(RBIN1,HIGH);
  digitalWrite(RBIN2,LOW);
}
void Back()
{
  digitalWrite(RSTBY,HIGH);
  digitalWrite(RPWMA,HIGH);
  digitalWrite(RPWMB,HIGH);
  digitalWrite(RAIN1,LOW);
  digitalWrite(RAIN2,HIGH);
  digitalWrite(RBIN1,HIGH);
  digitalWrite(RBIN2,LOW);

}
void Stop()
{
  digitalWrite(RSTBY,HIGH);
  digitalWrite(RPWMA,HIGH);
  digitalWrite(RPWMB,HIGH);
  digitalWrite(RAIN1,LOW);
  digitalWrite(RAIN2,LOW);
  digitalWrite(RBIN1,LOW);
  digitalWrite(RBIN2,LOW);
}

int measure()
{
  digitalWrite(Trig,HIGH); 
  delayMicroseconds(20);
  digitalWrite(Trig,LOW); 
  while(digitalRead(Echo)==0);//一旦收到D7信号
  int s=micros();
  while(digitalRead(Echo)==1);
  int e=micros();
  return e-s;  
}
void check_behind()
{
    digitalWrite(servo,HIGH);
    delayMicroseconds(1500);
    digitalWrite(servo,LOW);
    delay(18);
    delayMicroseconds(500);//前
}
void check_right()
{
    digitalWrite(servo,HIGH);
    delayMicroseconds(1000);
    digitalWrite(servo,LOW);
    delay(19);//右
}
void check_left()
{
    digitalWrite(servo,HIGH);
    delayMicroseconds(2000);
    digitalWrite(servo,LOW);
    delay(18);//左
}
void IRAM_ATTR timer_event()//中断处理函数，每秒执行一次 
{
    check_left();   
    measure();
    left_distance=measure()/58;
    delay(250);
    check_right();   
    measure();
    right_distance=measure()/58;
    delay(250);
}
void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  carinit();
  digitalWrite(Trig,LOW); 
//  digitalWrite(KEY,HIGH);
//  delay(10);
//  digitalWrite(KEY,LOW);
    timer = timerBegin(0,80,true);            
    // 配置定时器 这里使用的是定时器0(一共四个0123) 
    // 80是这个定时器的分频系数 由于定时器基频是80Mhz 
    // 这里设置80 就是1Mhz 就能保证定时器1us记录一次 
    // true表面该定时器向上计数    
    timerAttachInterrupt(timer,&timer_event,true);    
    // 配置定时器的中断函数 true表示边沿触发
    timerAlarmWrite(timer,1000000000,true);        
    // 设置定时器的报警值 当计时器计数值达到1000000时触发中断                              
    // true表示重加载
    timerAlarmEnable(timer);              
    // 使能定时器报警
}
void loop() 
{
  // put your main code here, to run repeatedly:    
//    check_behind();
//    delay(500);
//    
//    check_left();
//    delay(500);
//
//    check_behind();
//    delay(500);
//
//    check_right();
//    delay(500);

//  digitalWrite(KEY,LOW);
//  delay(10);
//  digitalWrite(KEY,HIGH);
  check_behind();
  delay(50);
  measure();
  distance=measure()/58;  
//  Serial.print("distance:");
//  Serial.print(distance);
//  Serial.println("cm");
//  delay(500);
  if(distance<=25)
  {
    Stop();
    delay(300);
    timer_event();
    if(left_distance>right_distance)
    {
      Left();
      delay(600);
    }
    else if(left_distance<right_distance)
    {
      Right();
      delay(600);
    }
    else
    {
      Back();
      delay(300);
    }
  } 
  else
  {
    Before(); 
  }
} 
