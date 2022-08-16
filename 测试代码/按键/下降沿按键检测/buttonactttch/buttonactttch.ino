#define LED 2
#define btn1 18
#define btn2 22
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(btn1,INPUT_PULLUP);
  pinMode(btn2,INPUT_PULLUP);
  pinMode(LED,OUTPUT);
  digitalWrite(LED,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
//  Serial.println(digitalRead(btn1));
//  delay(2500);
  attachInterrupt(btn1, testProgram, FALLING);
  attachInterrupt(btn2, testProgram1, FALLING);
}
void testProgram() {      
      //中断处理函数testProgram()
     if(digitalRead(btn1)==0)
     {
      digitalWrite(LED,HIGH);
     }
}
void testProgram1() {      
      //中断处理函数testProgram()
     if(digitalRead(btn2)==0)
     {
      digitalWrite(LED,LOW);
     }
}
