int ADD_BUTTON = 18;
int MINUS_BUTTON = 22;
int BEEP=19;
int num=0;
void setup() 
{
    Serial.begin(115200u);
    pinMode(ADD_BUTTON,INPUT);
    pinMode(MINUS_BUTTON,INPUT);
    pinMode(BEEP,OUTPUT);
    digitalWrite(BEEP,LOW);
}
 
void loop() 
{  
  if(digitalRead(ADD_BUTTON)==LOW)
  {
    delay(15);
   if(digitalRead(ADD_BUTTON)==LOW)
    {
      num=num+1;
      if(3<num)
      {
        num=3;  
      } 
      Serial.println(num);
      digitalWrite(BEEP,HIGH);
      delay(1000);
      digitalWrite(BEEP,LOW);
    }
  }

//  Serial.println(digitalRead(MINUS_BUTTON));
  if(digitalRead(MINUS_BUTTON)==LOW)
  {
    delay(15);
   if(digitalRead(MINUS_BUTTON)==LOW)
    {
      num=num-1; 
      if(num<0)
      {
        num=0;  
      }
      Serial.println(num);
      digitalWrite(BEEP,HIGH);
      delay(1000);
      digitalWrite(BEEP,LOW);
    }
  }

}
