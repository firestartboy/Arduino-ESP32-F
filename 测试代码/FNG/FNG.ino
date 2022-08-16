#define RBIN2 12
#define RPWMB 13
#define RBIN1 14
#define RAIN2 25
#define RAIN1 26
#define RSTBY 27
#define RPWMA 33

void pinModeinit()
{
  //RightMottoPinInit
  pinMode(RSTBY,OUTPUT);
  pinMode(RPWMA,OUTPUT);
  pinMode(RPWMB,OUTPUT);
  pinMode(RAIN1,OUTPUT);
  pinMode(RAIN2,OUTPUT);
  pinMode(RBIN1,OUTPUT);
  pinMode(RBIN2,OUTPUT); 
}
void Before()
{
  digitalWrite(RSTBY,HIGH);
  digitalWrite(RPWMA,HIGH);
  digitalWrite(RPWMB,HIGH);
  digitalWrite(RAIN1,LOW);
  digitalWrite(RAIN2,HIGH);
  digitalWrite(RBIN1,HIGH);
  digitalWrite(RBIN2,LOW);
}
void Left()
{

  digitalWrite(RSTBY,HIGH);
  digitalWrite(RPWMA,HIGH);
  digitalWrite(RPWMB,HIGH);
  digitalWrite(RAIN1,LOW);
  digitalWrite(RAIN2,HIGH);
  digitalWrite(RBIN1,HIGH);
  digitalWrite(RBIN2,LOW);
}
void Right()
{
  digitalWrite(RSTBY,HIGH);
  digitalWrite(RPWMA,HIGH);
  digitalWrite(RPWMB,HIGH);
  digitalWrite(RAIN1,HIGH);
  digitalWrite(RAIN2,LOW);
  digitalWrite(RBIN1,LOW);
  digitalWrite(RBIN2,HIGH);
}

void Back()
{
  digitalWrite(RSTBY,HIGH);
  digitalWrite(RPWMA,HIGH);
  digitalWrite(RPWMB,HIGH);
  digitalWrite(RAIN1,HIGH);
  digitalWrite(RAIN2,LOW);
  digitalWrite(RBIN1,LOW);
  digitalWrite(RBIN2,HIGH);
}
//void trig()
//{
//  digitalWrite(STBY,HIGH);
//  digitalWrite(PWMA,LOW);
//  digitalWrite(PWMB,LOW);
//  digitalWrite(AIN1,HIGH);
//  digitalWrite(AIN2,LOW);
//  digitalWrite(BIN1,HIGH);
//  digitalWrite(BIN2,LOW);
//}
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
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinModeinit();
}

void loop() {
  // put your main code here, to run repeatedly:
//  Before();
//  delay(10);
  Back();
//  delay(10);
//  Left();
//  delay(10);
//    Right();
//  delay(10);
}
