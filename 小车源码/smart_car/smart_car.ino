#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>  
//CarMottoDefine
#define RBIN2 12
#define RPWMB 13
#define RBIN1 14
#define RAIN2 25
#define RAIN1 26
#define RSTBY 27
#define RPWMA 33

#define LPWMA 22
#define LAIN2 23
#define LAIN1 18
#define LSTBY 5
#define LBIN1 4
#define LBIN2 19
#define LPWMB 21

#define servo 5
#define Trig 15
#define Echo  4

int LED = 2;
int btn1=18;
//int BEEP=19;
int btn2=22;
int LXJ=32; 
int RXJ=23; 
int num=0,a=0;
int flag=0;
int distance=0;
int left_distance=0;
int right_distance=0;
hw_timer_t *timer=NULL;//创建一个定时器结构体
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
  pinMode(LXJ,INPUT);
  pinMode(RXJ,INPUT);
  pinMode(btn1,INPUT_PULLUP);
  pinMode(btn2,INPUT_PULLUP);
//  pinMode(BEEP,OUTPUT);
  pinMode(LED,OUTPUT);
}
//car_dir_contorl
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
void Left()//01
{
  digitalWrite(RSTBY,HIGH);
  digitalWrite(RPWMA,HIGH);
  digitalWrite(RPWMB,HIGH);
  digitalWrite(RAIN1,LOW);
  digitalWrite(RAIN2,HIGH);
  digitalWrite(RBIN1,LOW);
  digitalWrite(RBIN2,HIGH);
}
void Right()//10
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
  digitalWrite(RAIN1,HIGH);
  digitalWrite(RAIN2,LOW);
  digitalWrite(RBIN1,LOW);
  digitalWrite(RBIN2,HIGH);
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
//BLEInit
BLEServer *pServer = NULL;
BLECharacteristic * pTxCharacteristic;
bool deviceConnected = false;
bool oldDeviceConnected = false;
uint8_t txValue = 0;

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID           "6E400001-B5A3-F393-E0A9-E50E24DCCA9E" // UART service UUID
#define CHARACTERISTIC_UUID_RX "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define CHARACTERISTIC_UUID_TX "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"


class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string rxValue = pCharacteristic->getValue();
      if (rxValue.length() > 0) {
        Serial.println("*********");
        Serial.print("Received Value: ");
 
        for (int i = 0; i < rxValue.length(); i++) {
          Serial.print(rxValue[i]);
        }
        // Do stuff based on the command received from the app
        if (rxValue.find("Q") != -1) { 
          Serial.print("behind!");
          Before();
        }
        else if (rxValue.find("H") != -1) {
          Serial.print("Turning Back!");
          Back();
        }
        else if (rxValue.find("Z") != -1) {
          Serial.print("Turning Left!");
          Left();
        }
        else if (rxValue.find("Y") != -1) {
          Serial.print("Turning Right!");
          Right();
        } 
        else if (rxValue.find("S") != -1) {
          Serial.print("Turning Stop!");
          Stop();
        } 

//        Serial.println();
//        Serial.println("*********");        
//        while(rxValue.find("EXIT") != -1)
//        {
//          delay(1000);
//          Serial.println("NOW BLE() EXIT!"); 
//          break;
//        }
//        Serial.println();
        Serial.println("*********");      
      }
    }
};
void BLEInit()
{
      // Create the BLE Device

  BLEDevice::init("ESP32 UART Test"); // Give it a name
   // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create a BLE Characteristic
  pTxCharacteristic = pService->createCharacteristic(
                    CHARACTERISTIC_UUID_TX,
                    BLECharacteristic::PROPERTY_NOTIFY
                  );
                      
  pTxCharacteristic->addDescriptor(new BLE2902());

  BLECharacteristic * pRxCharacteristic = pService->createCharacteristic(
                       CHARACTERISTIC_UUID_RX,
                      BLECharacteristic::PROPERTY_WRITE
                    );

  pRxCharacteristic->setCallbacks(new MyCallbacks());

  // Start the service
  pService->start();

  // Start advertising
  pServer->getAdvertising()->start();
  Serial.println("Waiting a client connection to notify...");
}
//function_control
void BLE()
{
    if (deviceConnected) {
      digitalWrite(LED,HIGH);
      pTxCharacteristic->setValue(&txValue, 1);
      pTxCharacteristic->notify();
      txValue++;
      delay(10); // bluetooth stack will go into congestion, if too many packets are sent
    }

    // disconnecting
    if (!deviceConnected && oldDeviceConnected) {
        delay(500); // give the bluetooth stack the chance to get things ready
        pServer->startAdvertising(); // restart advertising
        Serial.println("start advertising");
        oldDeviceConnected = deviceConnected;
        delay(1000);
        digitalWrite(LED,LOW);
    }
    // connecting
    if (deviceConnected && !oldDeviceConnected) {
    // do stuff here on connecting
        oldDeviceConnected = deviceConnected;
    }
// Serial.print("BLE():");
// Serial.println(num);
}
void XJ()
{
  Serial.println("XJ()");
  if(digitalRead(LXJ)==1&&digitalRead(RXJ)==0)
  {
    Serial.println("Right()");
    Right();
    delay(50);
  }
  if(digitalRead(RXJ)==1&&digitalRead(LXJ)==0)
  {
    Serial.println("Left()");
    Left();
    delay(50);
  }
  if(digitalRead(LXJ)==0 && digitalRead(RXJ)==0)
  {
    Serial.println("Before()");
    Before();
  }
  if(digitalRead(LXJ)==1 && digitalRead(RXJ)==1)
  {
    Serial.println("Stop()");
    Stop(); 
    delay(1000);
  }
 Serial.print("XJ():");
 Serial.println(num);
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

void timerInit()
{
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

void BZ()
{
  Serial.println("BZ()");
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
 Serial.print("BZ():");
 Serial.println(num);
}
 
void setup() {
  Serial.begin(115200);
  pinModeinit();
  attachInterrupt(btn1, testProgram, FALLING);
  attachInterrupt(btn2, testProgram1, FALLING);
  BLEInit();
  digitalWrite(LED,LOW);
  digitalWrite(Trig,LOW); 
  flag=0; 
  timerInit();
}
 
void loop() {

  if(flag==1)
  {
    if(num==0)
    {
      Stop();
    }
    if(num==1)
    {
          BLE();
    }        
    if(num==2)
    {
          XJ();
    }
    if(num==3)
    {
          BZ();
          delay(200);
    }     
  }
}
void testProgram() {      
      //中断处理函数testProgram()
  if(digitalRead(btn1)==0)
  {
    delay(50);
  if(digitalRead(btn1)==0)
  {
    num=num+1;
    
    if(3<num)
    {
      num=0; 
      Serial.print("num is reset");
    }    
    Serial.print("num:");
    Serial.println(num);
  }
  }
}
void testProgram1() {      
   //中断处理函数testProgram()
   if(digitalRead(btn2)==0)
   {
      delay(50);
     if(digitalRead(btn2)==0)
     {
        switch(flag)
        {
         case 0:
           flag=flag+1;
           Serial.print("now flag is:");
           Serial.println(flag);
           delay(50);
           break;
         case 1:
           flag=flag-1;
           Serial.print("now flag is:");
           Serial.println(flag);
           delay(50);
           break;
        }
     }
   }
}
