#include <Arduino.h>
#include "Wire.h"
#include <MPU6050_light.h>

#define ENA 9
#define IN1 8
#define IN2 7
#define IN3 5
#define IN4 4
#define ENB 3

MPU6050 mpu(Wire);
unsigned long timer = 0;

void setup() {
  Serial.begin(9600);

  Wire.begin();
 
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ } // stop everything if could not connect to MPU6050
  
  Serial.println(("Calculating offsets, do not move MPU6050"));
  delay(1000);
  mpu.calcOffsets(); // gyro and accelero
  Serial.println("Done!\n");
  // Set all the motor controls pins to output pins (pinouts)  
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT); 
}

int clockwise(int speed){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, speed);  
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB,speed);
  return 0;
}

int anticlockwise(int speed){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, speed);  
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, speed);
  return 0;
}

int r_angle = 90;
int m_angle = 0;
void loop() {
  while(m_angle != (-1*r_angle))
  {
    mpu.update();
    if((millis()-timer)>1){ // print data every 10ms
      
      timer = millis();
      Serial.println(String(round(mpu.getAngleZ())));
      m_angle = round(mpu.getAngleZ());

    }      
    if(r_angle > 0)
      {
        clockwise(200);
      }
      else{
        anticlockwise(200);
      }
  }
  clockwise(0);
  Serial.println("Done");
}