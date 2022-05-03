#include <ESP32Servo.h>
#include "BluetoothSerial.h" 
Servo middle, left, right, claw ;  
 
char  DATA;
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
BluetoothSerial SerialBT; 
int middle_min  = 0;
int middle_max = 180;
int middle_zero = 90;
int middlePose=90;

int right_min = 40;
int right_max =
 180;
int right_zero = 90;
int rightPose=90;

int left_min = 60;
int left_max = 165;
int left_zero = 152;
int leftPose=90;

int claw_min =  60;
int claw_max = 180;
int claw_zero = 60;
int clawPose=25;

int leftfront=18;
int RightFront=26;
int leftback=17;
int RightBack=16;

ESP32PWM pwm;

void setup() 
{ 
  Serial.begin(115200);
  middle.attach(2, 1000, 2000);  
  left.attach(4, 1000, 2000);  
  right.attach(12, 1000, 2000); 
  claw.attach(19, 1000, 2000); 
  pwm.attachPin(27, 10000);//10khz
   ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	middle.setPeriodHertz(330); 
  left.setPeriodHertz(50); 
  right.setPeriodHertz(50); 
  claw.setPeriodHertz(50); 
    DATA = ' ';
  SerialBT.begin("CLAW32");
  calibration();
 pinMode(leftfront, OUTPUT);
  pinMode(RightFront, OUTPUT);
    pinMode(leftback, OUTPUT);
      pinMode(RightBack, OUTPUT);



} 
 
 void calibration(){
  middle.write(90); 
  left.write(90); 
  right.write(90); 
  claw.write(25); 
  delay(300); 
 }
 void RobotControl(){
         if (SerialBT.available()) {
      DATA = (SerialBT.read());
      Serial.print(DATA); 

      if (DATA == 'M'){
        if(middlePose < middle_max){
          middlePose= middle.read();
            middlePose= middlePose + 10;
        middle.write(middlePose);
            delay(10);

      }}
      if (DATA == 'N'){
        if(middlePose > middle_min){
          middlePose= middle.read();
          middlePose= middlePose - 10;
        middle.write(middlePose);
            delay(10);

      }}



       if (DATA == 'L'){
        if(rightPose < right_max){
            rightPose = right.read();
            rightPose= rightPose + 10;
        right.write(rightPose);
        Serial.print("rightpose = ");
        Serial.println(rightPose);
            delay(10);

      }}
      if (DATA == 'O'){
        if(rightPose > right_min){
             rightPose = right.read();
            rightPose = rightPose -10;
        right.write(rightPose);
        Serial.print("rightpose = ");
        Serial.println(rightPose);
             delay(10);

      }}
             if (DATA == 'P'){
        if(leftPose < left_max){
            leftPose = left.read();
              leftPose = leftPose + 10;
        left.write(leftPose);
        Serial.print("leftpose = ");
        Serial.println(leftPose);
            delay(10);

      }}
       if (DATA == 'R'){
        if(leftPose > left_min){
            leftPose = left.read();
              leftPose = leftPose - 10;
        left.write(leftPose);
                Serial.print("leftpose = ");
        Serial.println(leftPose);
            delay(10);

      }}
             if (DATA == 'X'){
        if(clawPose < claw_max){
            clawPose = claw.read();
            clawPose = clawPose + 10;
        claw.write(clawPose);
        Serial.print("clawpose = ");
        Serial.println(clawPose);

            delay(10);

      }}

             if (DATA == 'Y'){
        if(clawPose > claw_min){
            clawPose = claw.read();
            clawPose= clawPose - 10;
        claw.write(clawPose);
            delay(10);         

      }}

      /////motors ////
           if (DATA == 'G') {
        digitalWrite(leftback,HIGH);
        digitalWrite(RightBack,HIGH);

        //Serial.print("it is B");
      }
      if (DATA == 'S'){
       digitalWrite(RightBack,LOW); 
       digitalWrite(leftback,LOW);
       digitalWrite(leftfront,LOW);
       digitalWrite(RightFront,LOW);
      }
       if (DATA == 'R') {
        digitalWrite(leftfront,HIGH);
        Serial.print("it is R");
  
      }
      
       if (DATA == 'F') {
        digitalWrite(leftfront,HIGH);
        digitalWrite(RightFront,HIGH);

        Serial.print("it is F");

      }
    
       if (DATA == 'L') {
        digitalWrite(RightFront,HIGH);
        Serial.print("it is L");
      }

 if (DATA == 'E') {
        digitalWrite(RightFront,HIGH);
        Serial.print("it is E");

      }
       if (DATA == 'Q') {
        digitalWrite(leftfront,HIGH);
        Serial.print("it is Q");

      }
      if (DATA == 'Z') {
        digitalWrite(leftback,HIGH);
        Serial.print("it is Z");

      }
      if (DATA == 'C') {
        digitalWrite(RightBack,HIGH);
        Serial.print("it is Q");

      }

 }}

void loop() 
{ 
RobotControl();
} 
