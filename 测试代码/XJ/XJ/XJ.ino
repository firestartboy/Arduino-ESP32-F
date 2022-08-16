int LXJ=32; 
int RXJ=23; 
#define RBIN2 12
#define RPWMB 13
#define RBIN1 14
#define RAIN2 25
#define RAIN1 26
#define RSTBY 27
#define RPWMA 33
#define KEY 19
void pinModeinit()
{
  pinMode(RSTBY,OUTPUT);
  pinMode(RPWMA,OUTPUT);
  pinMode(RPWMB,OUTPUT);
  pinMode(RAIN1,OUTPUT);
  pinMode(RAIN2,OUTPUT);
  pinMode(RBIN1,OUTPUT);
  pinMode(RBIN2,OUTPUT); 
  pinMode(KEY,OUTPUT); 
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
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LXJ,INPUT);
  pinMode(RXJ,INPUT);
  pinModeinit();
  digitalWrite(KEY,HIGH);
}
void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(KEY,LOW);
  delay(10);
  digitalWrite(KEY,HIGH);
//  Serial.println("LXJ:");
//  Serial.println(digitalRead(LXJ));
//  delay(500);
//  Serial.println("RXJ:");
//  Serial.println(digitalRead(RXJ));
//  delay(500);
  if(digitalRead(LXJ)==1&&digitalRead(RXJ)==0)
  {
    Serial.println("Right()");
    Right();
    delay(15);
  }
  if(digitalRead(RXJ)==1&&digitalRead(LXJ)==0)
  {
    Serial.println("Left()");
    Left();
    delay(15);
  }
  if(digitalRead(LXJ)==0 && digitalRead(RXJ)==0)
  {
    Serial.println("Before()");
    Back();
  }
  if(digitalRead(LXJ)==1 && digitalRead(RXJ)==1)
  {
    Serial.println("Stop()");
    Stop(); 
    delay(1000);
  }
}
